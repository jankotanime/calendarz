#include <chrono>
#include <wx/wx.h>
#include <iostream>

std::string get_month(int n);

void dates(std::tm* localTime, wxPanel* panel) {
  wxPaintDC dc(panel);

  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(10, 30, 10));
  dc.DrawText(get_month(localTime->tm_mon), wxPoint(400, 20));
  dc.DrawText(std::to_string(localTime->tm_year), wxPoint(600, 20));  
}
