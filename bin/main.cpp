#include <wx/wx.h>
#include "MyApp.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

wxIMPLEMENT_APP(MyApp);

void frames_paint(wxPaintEvent& event, int width, int height, const std::tm& localTime, std::tm today, wxPanel* panel);
void dates(wxPaintEvent& event, std::tm* localTime, wxPanel* panel);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(50, 60, 50));
  wxInitAllImageHandlers();

  wxPanel* panel = new wxPanel(frame);

  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  localTime->tm_year += 1900;
  const std::tm today = *localTime;

  
  // ? Changeable date 
  // std::tm tmDate = {};
  // tmDate.tm_year = 2026 - 1900;
  // tmDate.tm_mon = 2 - 1;
  // tmDate.tm_mday = 24;
  // std::time_t time = std::mktime(&tmDate);
  // std::tm* localTime = std::localtime(&time);
  
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    frames_paint(event, WIDTH, HEIGHT, *localTime, today, panel);
    dates(event, localTime, panel);
  });

  frame->Show(true);

  return true;
}
