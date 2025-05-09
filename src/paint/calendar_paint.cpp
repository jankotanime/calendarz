#include <wx/wx.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>
#include <forward_list>
#include "../../include/Tile.h"
#include "../../include/Event.h"

struct OneTile {
  int day, month, year; 
};
struct Images {
  wxStaticBitmap* back, *add_event, *left, *right; 
};

int first_day_of_month(int, int);

int event_day(std::forward_list<Event>, int, int, int);

void pick_day_handler(Tile&, Images, int, int, int);

void calander_paint(int width, int height, const std::tm& localTime, std::tm today, Tile& tile, Images& images, std::forward_list<Event> events, wxPanel* panel) {
  OneTile clicked_tile = {0, 0, 0};
  std::tm localTimeCopy = localTime;
  localTimeCopy.tm_year + 1900;

  int year = localTimeCopy.tm_year;
  int month = localTimeCopy.tm_mon;
  int day = localTimeCopy.tm_mday;
  int week_day = localTimeCopy.tm_wday;
  int first_day = first_day_of_month(year, month);
  
  std::tm last_month = localTimeCopy;
  last_month.tm_mday = 0;
  last_month.tm_hour = 0;
  last_month.tm_min = 0;
  last_month.tm_sec = 0;
  std::mktime(&last_month);

  std::tm next_month = localTimeCopy;
  next_month.tm_mon += 1;
  std::tm time = localTimeCopy;
  
  int days = floor(std::difftime(std::mktime(&next_month), std::mktime(&time))/86400.0);
  next_month.tm_mday = 1;
  
  int x_border = 20;
  int y_border = 80;
  int x_border_end = width-25;
  int y_border_end = height-5;

  wxPaintDC dc(panel);
  wxPoint screenPos = wxGetMousePosition();
  wxPoint localPos = panel->ScreenToClient(screenPos);

  dc.SetBrush(wxBrush(wxColour(140, 145, 140)));
  dc.DrawRectangle(x_border, y_border, x_border_end-x_border, y_border_end-y_border);
  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(120, 125, 120));

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 6; j++) {
      dc.SetPen(wxPen(wxColour(30, 35, 30), 5));
      int x = floor((width - x_border * 2) / 7.0) * i + x_border;
      int y = floor((height - y_border) / 6.0) * j + y_border;
      int xEnd = x + floor(width / 7.0);
      int yEnd = y + floor(height / 6.0);
      // Draw cell
      dc.DrawLine(x, y, xEnd-10, y);
      dc.DrawLine(x, y, x, yEnd-15);
      int draw_day;
      
      if (first_day > 3) {
        draw_day = (i + j * 7 - first_day + 2);
      } else {
        draw_day = (i + j * 7 - first_day - 5);
      }
      // Hover
      if (draw_day == day && year == today.tm_year && month == today.tm_mon) {
        // Painting for today
        if (localPos.x > x && localPos.x < xEnd-10 && localPos.y > y && localPos.y < yEnd-15) {
          dc.SetBrush(wxBrush(wxColour(200, 205, 200)));
          panel->Bind(wxEVT_LEFT_DOWN, [&tile, images, draw_day, month, year] (wxMouseEvent& event) {
            pick_day_handler(tile, images, draw_day, month, year);
          });
        } else {
          dc.SetBrush(wxBrush(wxColour(180, 185, 180)));
        }
        dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));  
        dc.DrawText(std::to_string(day), wxPoint(x+10, y+10));
      } else {
        if (days < draw_day) {
          // Painting for days in next month
          dc.SetTextForeground(wxColour(100, 100, 100));
          dc.DrawText(std::to_string(draw_day - days), wxPoint(x+10, y+10));
        } else if (draw_day < 1) {
          // Painting for days in last month
          dc.SetTextForeground(wxColour(100, 100, 100));
          dc.DrawText(std::to_string(last_month.tm_mday+draw_day), wxPoint(x+10, y+10));
        } else {
          // Painting for days in picked month
          if (localPos.x > x && localPos.x < xEnd-10 && localPos.y > y && localPos.y < yEnd-15) {
            panel->Bind(wxEVT_LEFT_DOWN, [&tile, images, draw_day, month, year] (wxMouseEvent& event) {
              pick_day_handler(tile, images, draw_day, month, year);
            });
            dc.SetBrush(wxBrush(wxColour(155, 160, 155)));
            dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));
          }
          dc.SetTextForeground(wxColour(30, 35, 30));
          dc.DrawText(std::to_string(draw_day), wxPoint(x+10, y+10));
        }
      }
      // Painting info about event
      int events_amount = event_day(events, draw_day, month, year);
      if (events_amount != 0) {
        dc.SetPen(wxPen(wxColour(160, 80, 80), 5));
        for (int i = 0; i < events_amount; i++) {
          dc.DrawLine(x+10, y+50+i*10, x+30, y+50+i*10);
        }
      }
    }
  }

  dc.SetPen(wxPen(wxColour(30, 35, 30), 5));
  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
}
