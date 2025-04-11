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
int diffTimeToTommorow();

bool NotificationService::OnInit() {
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "", wxDefaultPosition, wxSize(300, 360), wxNO_BORDER);
  wxTimer* timer = new wxTimer(this);
  
  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    checkEvents(frame);
    timer->StartOnce(diffTimeToTommorow()*1000);
  }, timer->GetId());
  timer->StartOnce(diffTimeToTommorow()*1000);
  checkEvents(frame);
  return true;
}

void NotificationService::checkEvents(wxFrame* frame) {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  localTime->tm_year += 1900;
  std::forward_list<Event> events = scan_data();
  int i = 0;
  for (Event event : events) {
    if (event.getDay() == localTime->tm_mday && event.getMonth() == localTime->tm_mon && event.getYear() == localTime->tm_year) {
      OnEvent(event.getTitle(), event.getDscrpt(), frame, i);
    }
    i++;
  }
  if (i != 0) {
    frame->Show(true);
  }
}

void NotificationService::OnEvent(std::string title, std::string dscrpt, wxFrame* frame, int i) {
  wxTimer* timer = new wxTimer(this);
  
  wxPanel* panel = new wxPanel(frame, wxID_ANY);
  panel->SetSize(300, 60);
  panel->SetPosition({0, i*60});
  panel->Bind(wxEVT_PAINT, [=](wxPaintEvent& event) {
    wxPaintDC dc(panel);
    dc.SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.SetTextForeground(wxColour(10, 30, 10));
    dc.DrawText(title, wxPoint(5, 5));
    dc.SetFont(wxFont(15, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    dc.DrawText(dscrpt, wxPoint(5, 30));  
  });

  Bind(wxEVT_TIMER, [=](wxTimerEvent& event) {
    panel->Destroy();
    frame->Hide();
  }, timer->GetId());
  timer->StartOnce(5000);
}
