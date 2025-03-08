#include <wx/wx.h>
#include "MyApp.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

wxIMPLEMENT_APP(MyApp);

void frames_paint(wxPaintEvent& event, int width, int height, wxPanel* panel);
void dates(wxPaintEvent& event, wxPanel* panel);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(50, 60, 50));

  wxPanel* panel = new wxPanel(frame);
  
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    frames_paint(event, WIDTH, HEIGHT, panel);
    dates(event, panel);
  });
  

  frame->Show(true);

  return true;
}
