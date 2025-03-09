#include <wx/wx.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>

int first_day_of_month(int year, int month) {
  std::tm tmDate = {};
  tmDate.tm_year = year - 1900;
  tmDate.tm_mon = month - 1;
  tmDate.tm_mday = 1;
  std::mktime(&tmDate);
  return tmDate.tm_wday;
}

void frames_paint(wxPaintEvent& event, int width, int height, wxPanel* panel) {
  // auto now = std::chrono::system_clock::now();
  // std::time_t time = std::chrono::system_clock::to_time_t(now);
  // std::tm* localTime = std::localtime(&time);
  std::tm tmDate = {};
  tmDate.tm_year = 2025 - 1900;
  tmDate.tm_mon = 3 - 1;
  tmDate.tm_mday = 13;
  std::time_t time = std::mktime(&tmDate);
  std::tm* localTime = std::localtime(&time);
  
  int year = 1900 + localTime->tm_year;
  int month = 1 + localTime->tm_mon;
  int day = localTime->tm_mday;
  int week_day = localTime->tm_wday;
  
  int last_month = localTime->tm_mon;
  int next_month = 2 + localTime->tm_mon;
  int first_day = first_day_of_month(year, month);

  std::cout << week_day << "," << first_day << std::endl;

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
      if (j-1 == (day/7) && (i+1)%7 == week_day && i != 6) {
        dc.SetBrush(wxBrush(wxColour(180, 200, 180)));
        dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0));  
        dc.DrawText(std::to_string(day), wxPoint(x+10, y+10));
      } else if (j == (day/7) && (i+1)%7 == week_day && i == 6) {
        dc.SetBrush(wxBrush(wxColour(180, 200, 180)));
        dc.DrawRectangle(x, y, floor((width - x_border * 2) / 7.0), floor((height - y_border) / 6.0)); 
        dc.DrawText(std::to_string(day), wxPoint(x+10, y+10));
      } else {
        dc.DrawText(std::to_string(i - 3 + first_day + (j - 1) * 7), wxPoint(x+10, y+10));
      }
    }
  }
  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
  
  dc.DrawLine(1, 1, 100, 100);
}