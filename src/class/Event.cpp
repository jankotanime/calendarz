#include <iostream>
#include <math.h>
#include <wx/wx.h>
#include "forward_list"
#include "../../include/Event.h"
#include "../../include/MyApp.h"

void remove_from_data(std::forward_list<Event>);

Event::Event(std::string t, std::string dr, int d, int m, int y) 
: title(t), dscrpt(dr), day(d), month(m), year(y), del(false) {};

std::string Event::getTitle() {
  return this->title;
}

std::string Event::getDscrpt() {
  return this->dscrpt;
}

int Event::getDay() {
  return this->day;
}

int Event::getMonth() {
  return this->month;
}

int Event::getYear() {
  return this->year;
}

void Event::fillDscrpt(std::string t, std::string d) {
  this->title = t;
  this->dscrpt = d;
}

void Event::delEvent(std::forward_list<Event> events) {
  if (this->del == true) {
    this->day = 0;
    this->month = 0;
    this->year = 0;
    remove_from_data(events);
  } else {
    this->del = true;
  }
}

void Event::cancelDelEvent() {
  this->del = false;
}

bool Event::wantToDel() {
  return this->del;
}

OneEvent Event::get_event_as_struct() {
  return {this->title, this->dscrpt, this->day, this->month, this->year, this->del};
}
