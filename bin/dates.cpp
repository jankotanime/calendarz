#include <chrono>
#include <wx/wx.h>
#include <iostream>

void dates(wxPaintEvent& event, wxPanel* panel) {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  
  int year = 1900 + localTime->tm_year;

  wxPaintDC dc(panel);
  
  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(10, 30, 10));
  dc.DrawText(std::to_string(year), wxPoint(400, 20));
}
