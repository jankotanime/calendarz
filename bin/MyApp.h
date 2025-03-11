#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>
#include "Tile.h"

class MyApp : public wxApp {
  public:
  int WIDTH = 1200;
  int HEIGHT = 900;
  Tile tile = Tile(0, 0, 0);


  virtual bool OnInit();
  void OnPaint(wxPaintEvent& event);
  private:
};

#endif // MYAPP_H
