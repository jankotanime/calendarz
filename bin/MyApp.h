#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>
#include "Tile.h"

struct Images {
  wxStaticBitmap* back, *left, *right; 
};

class MyApp : public wxApp {
  private:
  wxTimer timer;
  public:
  int WIDTH = 1200;
  int HEIGHT = 900;
  Tile tile = Tile(0, 0, 0);
  Images images;

  virtual bool OnInit();
  void OnPaint(wxPaintEvent& event);
  private:
};

#endif // MYAPP_H
