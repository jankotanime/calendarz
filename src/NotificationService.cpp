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
  int time_int = 1000 * 60 * 60;
  std::chrono::milliseconds timespan(time_int);
  while (true) {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time);
    localTime->tm_year += 1900;
    checkEvents(*localTime);
    std::this_thread::sleep_for(timespan);
  }
  return true;
}

void NotificationService::checkEvents(const std::tm& localTime) {
  std::forward_list<Event> events = scan_data();
  for (Event event : events) {
    if (event.getDay() == localTime.tm_mday && event.getMonth() == localTime.tm_mon && event.getYear() == localTime.tm_year) {
      OnEvent(event.getTitle(), event.getDscrpt());
    }
  }
}

void NotificationService::OnEvent(std::string title, std::string description) {
  std::cout << "test" << std::endl;
  wxFrame* frame = new wxFrame(nullptr, wxID_ANY, "Calendarz", wxDefaultPosition, wxSize(WIDTH, HEIGHT));
  wxPoint position(100, 100);
  frame->Move(position);
  frame -> SetBackgroundColour(wxColour(50, 60, 50));
}
