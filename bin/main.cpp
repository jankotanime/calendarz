#include <wx/wx.h>
#include "MyApp.h"
#include "Tile.h"
#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <wx/timer.h>
#include "Event.h"
#include <forward_list>

wxIMPLEMENT_APP(MyApp);

struct OneTile {
  int day, month, year; 
};

void frames_paint(int width, int height, const std::tm& localTime, std::tm today, Tile& tile, Images& images, std::forward_list<Event>, wxPanel* panel);
void dates(std::tm* localTime, wxPanel* panel);
void edit_day_paint(int width, int height, Tile& tile, std::forward_list<Event>, wxPanel* panel);
Images paint_images(int width, int height, std::tm* localTime, Tile& tile, std::forward_list<Event>&, wxPanel* panel);
Tile pick_tile(OneTile);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(50, 60, 50));
  wxInitAllImageHandlers();

  wxPanel* panel = new wxPanel(frame);
  wxTimer* timer = new wxTimer(this);

  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  localTime->tm_year += 1900;
  const std::tm today = *localTime;

  images = paint_images(WIDTH, HEIGHT, localTime, tile, events, panel);
  
  // ? Changeable date 
  // std::tm tmDate = {};
  // tmDate.tm_year = 2026 - 1900;
  // tmDate.tm_mon = 2 - 1;
  // tmDate.tm_mday = 24;
  // std::time_t time = std::mktime(&tmDate);
  // std::tm* localTime = std::localtime(&time);
  
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    if (tile.getDay() != 0) {
      edit_day_paint(WIDTH, HEIGHT, tile, events, panel);
    } else {
      frames_paint(WIDTH, HEIGHT, *localTime, today, tile, images, events, panel);
      dates(localTime, panel);
    }
  });

  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    panel->Refresh();
  }, timer->GetId());

  timer->Start(floor(1000/60));
  frame->Show(true);

  return true;
}
