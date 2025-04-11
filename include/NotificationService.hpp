#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <wx/wx.h>
#include <iostream>
#include <forward_list>
#include "Event.h"

std::forward_list<Event> scan_data();

class NotificationService : public wxApp {
  private:
  wxTimer timer;
  public:
  int WIDTH = 1200;
  int HEIGHT = 900;
  std::forward_list<Event> events = scan_data();
  virtual bool OnInit();
  void OnEvent(std::string, std::string, wxFrame*);
  void checkEvents();
};

#endif
