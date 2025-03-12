#include <wx/wx.h>
#include <iostream>
#include <math.h>
#include <chrono>
#include <ctime>
#include "Tile.h"

std::string get_month(int n);

void edit_day_paint(wxPaintEvent& event, int width, int height, Tile& tile, wxPanel* panel) {
  int x_border = 20;
  int y_border = 80;
  int x_border_end = width-25;
  int y_border_end = height-5;

  wxPaintDC dc(panel);
  wxPoint screenPos = wxGetMousePosition();
  wxPoint localPos = panel->ScreenToClient(screenPos);

  dc.SetTextForeground(wxColour(20, 40, 20));
  dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.DrawText(std::to_string(tile.getDay()), wxPoint(40, 100));
  dc.DrawText(get_month(tile.getMonth()), wxPoint(90, 100));
  dc.DrawText(std::to_string(tile.getYear()), wxPoint(270, 100));

  dc.SetTextForeground(wxColour(100, 100, 100));
  dc.SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
  dc.DrawText(std::to_string(localPos.x), wxPoint(5, 5));
  dc.DrawText(std::to_string(localPos.y), wxPoint(50, 5));

  wxBitmap testimg("img/test.jpg", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* test = new wxStaticBitmap(panel, wxID_ANY, testimg, wxPoint(1000, 800), wxSize(40, 40));
  test->Bind(wxEVT_LEFT_DOWN, [&tile](wxMouseEvent& event) {
    tile.changeDate(0, 0, 0);
  });

  dc.SetPen(wxPen(wxColour(20, 40, 20), 5));
  dc.DrawLine(x_border, y_border, x_border_end, y_border);
  dc.DrawLine(x_border, y_border, x_border, y_border_end);
  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
}