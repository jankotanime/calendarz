#ifndef TILE_H
#define TILE_H

#include <wx/wx.h>
#include <iostream>

class Tile {
  public:
  Tile(int width, int height, wxPanel* panel);
  void paint(wxPaintEvent& event);
private:
  int width;
  int height;
  wxPanel* m_panel;
};

#endif
