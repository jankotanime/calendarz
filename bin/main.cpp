#include <wx/wx.h>
#include "MyApp.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

wxIMPLEMENT_APP(MyApp);

void frames_paint(wxPaintEvent& event, int width, int height, std::tm localTime, wxPanel* panel);
void dates(wxPaintEvent& event, std::tm* localTime, wxPanel* panel);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(50, 60, 50));

  wxPanel* panel = new wxPanel(frame);

  // auto now = std::chrono::system_clock::now();
  // std::time_t time = std::chrono::system_clock::to_time_t(now);
  // std::tm* localTime = std::localtime(&time);
  
  // ? Changeable date 
  std::tm tmDate = {};
  tmDate.tm_year = 2026 - 1900;
  tmDate.tm_mon = 2 - 1;
  tmDate.tm_mday = 24;
  std::time_t time = std::mktime(&tmDate);
  std::tm localTime = *std::localtime(&time);
  std::tm* xddd = std::localtime(&time);

  
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    frames_paint(event, WIDTH, HEIGHT, localTime, panel);
    dates(event, xddd, panel);
  });
  

  frame->Show(true);

  return true;
}
