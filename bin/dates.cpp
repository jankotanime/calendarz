#include <chrono>
#include <wx/wx.h>
#include <iostream>

void dates(wxPaintEvent& event, std::tm* localTime, wxPanel* panel) {
  wxPaintDC dc(panel);
  
  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.SetTextForeground(wxColour(10, 30, 10));
  localTime->tm_year = localTime->tm_year+1;
  dc.DrawText(std::to_string(localTime->tm_year), wxPoint(400, 20));
}
