#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <forward_list>
#include <wx/wx.h>
#include <wx/timer.h>
#include "../include/MyApp.h"
#include "../include/Event.h"
#include "../include/Tile.h"

wxIMPLEMENT_APP(MyApp);

struct OneTile {
  int day, month, year; 
};

void calander_paint(int, int, const std::tm&, std::tm, Tile&, Images&, std::forward_list<Event>, wxPanel*);
void dates_change_paint(std::tm*, wxPanel*);
void edit_day_paint(int, int, Tile&, std::forward_list<Event>, wxPanel*);
Images paint_images(int, int, std::tm*, Tile&, std::forward_list<Event>&, wxPanel*);
Tile pick_tile(OneTile);

bool MyApp::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  frame -> SetBackgroundColour(wxColour(40, 45, 40));
  wxInitAllImageHandlers();

  wxPanel* panel = new wxPanel(frame);
  wxTimer* timer = new wxTimer(this);

  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  localTime->tm_year += 1900;
  const std::tm today = *localTime;

  images = paint_images(WIDTH, HEIGHT, localTime, tile, events, panel);
  
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    panel->Bind(wxEVT_LEFT_DOWN, [](wxMouseEvent& event) {});
    if (tile.getDay() != 0) {
      edit_day_paint(WIDTH, HEIGHT, tile, events, panel);
    } else {
      calander_paint(WIDTH, HEIGHT, *localTime, today, tile, images, events, panel);
      dates_change_paint(localTime, panel);
    }
  });

  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    panel->Refresh();
  }, timer->GetId());

  timer->Start(floor(1000/60)); // ? FPS
  frame->Show(true);

  return true;
}
