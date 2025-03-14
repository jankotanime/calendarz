#ifndef EVENT_H
#define EVENT_H

#include <wx/wx.h>
#include <iostream>

class Event {
  private:
  std::string title;
  std::string dscrpt;
  int day;
  int month;
  int year;
  public:
  Event(std::string title, std::string dscrpt, int day, int month, int year);
  std::string getTitle();
  std::string getDscrpt();
  int getDay();
  int getMonth();
  int getYear();
  void fillDscrpt(std::string t, std::string d);
};

#endif
