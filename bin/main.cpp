#include <wx/wx.h>
#include "MyApp.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include <chrono>


// Definicja aplikacji
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(50, 60, 50));

  wxPanel* panel = new wxPanel(frame);
  
  new Tile(WIDTH, HEIGHT, panel);

  panel->Refresh();
  frame->Show(true);

  return true;
}
