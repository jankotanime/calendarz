#include <iostream>
#include <thread>
#include <functional>
#include <chrono>
#include <forward_list>
#include <wx/wx.h>
#include <wx/timer.h>
#include "../include/NotificationService.hpp"
#include "../include/Event.h"

wxIMPLEMENT_APP(NotificationService);
std::forward_list<Event> scan_data();

bool NotificationService::OnInit() {
  wxTimer* timer = new wxTimer(this);
  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    checkEvents();
  }, timer->GetId());
  timer->Start(1000 * 60 * 60);
  checkEvents();
  return true;
}



void NotificationService::checkEvents() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  localTime->tm_year += 1900;
  std::forward_list<Event> events = scan_data();
  for (Event event : events) {
    if (event.getDay() == localTime->tm_mday && event.getMonth() == localTime->tm_mon && event.getYear() == localTime->tm_year) {
      OnEvent(event.getTitle(), event.getDscrpt());
    }
  }
}

void NotificationService::OnEvent(std::string title, std::string description) {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxSize(250, 60), wxNO_BORDER);
  wxTimer* timer = new wxTimer(this);
  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    frame->Destroy();
  }, timer->GetId());
  timer->Start(2000);

  // frame->SetTransparent(0);
  
  wxPanel* panel = new wxPanel(frame, wxID_ANY);
  panel->SetSize(100, 100);
  panel->Move(100, 100);
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    wxPaintDC dc(panel);
    dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.SetTextForeground(wxColour(10, 30, 10));
    dc.DrawText(title, wxPoint(5, 5));
    dc.SetFont(wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText(description, wxPoint(5, 30));  
    panel->Refresh();
  });
  frame->Show(true);
}
