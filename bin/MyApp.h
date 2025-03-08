#ifndef MYAPP_H
#define MYAPP_H

#include <wx/wx.h>

class MyApp : public wxApp {
  public:
  int WIDTH = 1200;
  int HEIGHT = 900;

  virtual bool OnInit();
  void OnPaint(wxPaintEvent& event);
};

#endif // MYAPP_H
