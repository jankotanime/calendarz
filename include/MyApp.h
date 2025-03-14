#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>
#include <iostream>
#include <forward_list>
#include "Tile.h"
#include "Event.h"

struct Images {
  wxStaticBitmap* back, *add_event, *left, *right; 
};

std::forward_list<Event> scan_data();

class MyApp : public wxApp {
  private:
  wxTimer timer;
  public:
  int WIDTH = 1200;
  int HEIGHT = 900;
  Tile tile = Tile(0, 0, 0);
  Images images;
  std::forward_list<Event> events = scan_data();


  virtual bool OnInit();
  void OnPaint(wxPaintEvent& event);
  private:
};

#endif // MYAPP_H
