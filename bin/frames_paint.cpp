#include <wx/wx.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>

int first_day_of_month(int year, int month) {
  std::tm tmDate = {};
  tmDate.tm_year = year;
  tmDate.tm_mon = month;
  tmDate.tm_mday = 1;

  std::time_t t_date = std::mktime(&tmDate);
  
  if (tmDate.tm_wday == 0) {
    return 6;
  } 
  if (tmDate.tm_wday == 1) {
    return 7;
  }
  return tmDate.tm_wday - 1;
}

void frames_paint(wxPaintEvent& event, int width, int height, const std::tm& localTime, std::tm today, wxPanel* panel) {
  std::tm localTimeCopy = localTime;
  localTimeCopy.tm_year + 1900;

  int year = localTimeCopy.tm_year;
  int month = localTimeCopy.tm_mon;
  int day = localTimeCopy.tm_mday;
  int week_day = localTimeCopy.tm_wday;
  
  int first_day = first_day_of_month(year, month);
  
  std::tm last_month = localTimeCopy;
  last_month.tm_mday = 1;
  last_month.tm_mday -= 1;
  std::mktime(&last_month);
  int mday = last_month.tm_mday;

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

  dc.SetBrush(wxBrush(wxColour(140, 160, 140)));
  dc.DrawRectangle(x_border, y_border, x_border_end-x_border, y_border_end-y_border);

  dc.SetPen(wxPen(wxColour(30, 40, 30), 5));
  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(10, 30, 10));

  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 6; j++) {
      int x = floor((width - x_border * 2) / 7.0) * i + x_border;
      int y = floor((height - y_border) / 6.0) * j + y_border;
      int xEnd = x + floor(width / 7.0);
      int yEnd = y + floor(height / 6.0);
      dc.DrawLine(x, y, xEnd-10, y);
      dc.DrawLine(x, y, x, yEnd-15);
      int draw_day;
      
      if (first_day > 3) {
        draw_day = (i + j * 7 - first_day + 2);
      } else {
        draw_day = (i + j * 7 - first_day - 5);
      }
      if (draw_day == day && year == today.tm_year && month == today.tm_mon) {
        if (localPos.x > x && localPos.x < xEnd-10 && localPos.y > y && localPos.y < yEnd-15) {
          dc.SetBrush(wxBrush(wxColour(200, 220, 200))); 
        } else {
          dc.SetBrush(wxBrush(wxColour(180, 200, 180)));
        }
        dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));  
        dc.DrawText(std::to_string(day), wxPoint(x+10, y+10)); 
      } else {
        if (localPos.x > x && localPos.x < xEnd-10 && localPos.y > y && localPos.y < yEnd-15) {
          dc.SetBrush(wxBrush(wxColour(155, 175, 155)));
          dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));  
        }
        if (days < draw_day) {
          dc.SetTextForeground(wxColour(100, 100, 100));
          dc.DrawText(std::to_string(draw_day - days), wxPoint(x+10, y+10));
        } else if (draw_day < 1) {
          dc.SetTextForeground(wxColour(100, 100, 100));
          dc.DrawText(std::to_string(last_month.tm_mday+draw_day), wxPoint(x+10, y+10));
        } else {
          dc.SetTextForeground(wxColour(10, 30, 10));
          dc.DrawText(std::to_string(draw_day), wxPoint(x+10, y+10));
        }
      }
    }
  }

  dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
  dc.SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.DrawText(std::to_string(localPos.x), wxPoint(5, 5));
  dc.DrawText(std::to_string(localPos.y), wxPoint(50, 5));

  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
}