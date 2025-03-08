#include "Tile.h"
#include <wx/wx.h>
#include "MyApp.h"
#include <iostream>
#include <math.h>

Tile::Tile(int width, int height, wxPanel* panel) : width(width), height(height), m_panel(panel) {
  m_panel->Bind(wxEVT_PAINT, &Tile::paint, this);
};

void Tile::paint(wxPaintEvent& event) {
  int x_border = 20;
  int y_border = 70;
  int x_border_end = width-20;
  int y_border_end = height-20;
  wxPaintDC dc(m_panel);
  dc.SetPen(wxPen(wxColour(30, 40, 30), 5));
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 6; j++) {
      int x = floor((width-x_border*2) / 7.0)*i+x_border;
      int y = floor((height-(y_border+35)) / 6.0)*j+y_border;
      int xEnd = x + floor(width / 7.0);
      int yEnd = y + floor(height / 6.0);
      dc.DrawLine(x, y, xEnd, y);
      dc.DrawLine(x, y, x, yEnd);
    }
  }
  dc.DrawLine(x_border, y_border_end, x_border_end, y_border_end);
  dc.DrawLine(x_border_end, y_border, x_border_end, y_border_end);
}
