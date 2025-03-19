#ifndef EVENT_H
#define EVENT_H

#include <wx/wx.h>
#include <iostream>

struct OneEvent {
  std::string title, dscrpt;
  int day, month, year;
  bool del;
};

class Event {
  private:
  std::string title;
  std::string dscrpt;
  int day;
  int month;
  int year;
  bool del;
  public:
  Event(std::string title, std::string dscrpt, int day, int month, int year);
  std::string getTitle();
  std::string getDscrpt();
  int getDay();
  int getMonth();
  int getYear();
  void fillDscrpt(std::string t, std::string d);
  void delEvent();
  void cancelDelEvent();
  bool wantToDel();
  OneEvent get_event_as_struct();
};

#endif
