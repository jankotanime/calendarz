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
  tmDate = *std::localtime(&t_date);
  if (tmDate.tm_wday == 0) {
    return 6;
  } 
  if (tmDate.tm_wday == 1) {
    return 7;
  }
  return tmDate.tm_wday - 1;
}

void frames_paint(wxPaintEvent& event, int width, int height, wxPanel* panel) {
  // auto now = std::chrono::system_clock::now();
  // std::time_t time = std::chrono::system_clock::to_time_t(now);
  // std::tm* localTime = std::localtime(&time);
  
  // ? Changeable date 
  std::tm tmDate = {};
  tmDate.tm_year = 2028 - 1900;
  tmDate.tm_mon = 9 - 1;
  tmDate.tm_mday = 28;
  std::time_t time = std::mktime(&tmDate);
  std::tm* localTime = std::localtime(&time);

  int year = 1900 + localTime->tm_year;
  int month = localTime->tm_mon;
  int day = localTime->tm_mday;
  int week_day = localTime->tm_wday;
  
  int first_day = first_day_of_month(year, month);

  std::time_t last_month_t = time;
  std::tm last_month = *std::localtime(&last_month_t);
  last_month.tm_mday = 1;
  last_month.tm_mday -= 1;
  last_month_t = std::mktime(&last_month);
  int mday = last_month.tm_mday;

  std::time_t next_month_t = time;
  std::tm next_month = *std::localtime(&next_month_t);
  next_month.tm_mon += 1;
  next_month_t = std::mktime(&next_month);

  int days = floor(std::difftime(next_month_t, time)/86400.0);
  next_month.tm_mday = 1;

  int x_border = 20;
  int y_border = 80;
  int x_border_end = width-25;
  int y_border_end = height-5;

  wxPaintDC dc(panel);

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

      if (draw_day == day) {
        dc.SetBrush(wxBrush(wxColour(180, 200, 180)));
        dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));  
        dc.DrawText(std::to_string(day), wxPoint(x+10, y+10));
      } else {
        if (days < draw_day) {
          dc.DrawText(std::to_string(draw_day - days), wxPoint(x+10, y+10));
        } else if (draw_day < 1) {
          dc.DrawText(std::to_string(last_month.tm_mday+draw_day), wxPoint(x+10, y+10));
        } else {
          dc.DrawText(std::to_string(draw_day), wxPoint(x+10, y+10));
        }
      }
    }
  }
  std::cout << first_day << "," << month << std::endl;
  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
}