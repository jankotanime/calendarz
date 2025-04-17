#include <iostream>
#include <chrono>
#include <wx/wx.h>

std::string get_month(int);

void dates_change_paint(std::tm* localTime, wxPanel* panel) {
  wxPaintDC dc(panel);

  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(120, 125, 120));
  dc.DrawText(get_month(localTime->tm_mon), wxPoint(400, 20));
  dc.DrawText(std::to_string(localTime->tm_year), wxPoint(600, 20));  
}
