#include <iostream>
#include <math.h>
#include <wx/wx.h>
#include "../../include/Event.h"
#include "../../include/MyApp.h"

Event::Event(std::string t, std::string dr, int d, int m, int y) 
: title(t), dscrpt(dr), day(d), month(m), year(y), del(0) {};

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

void Event::delEvent() {
  if (this->del == 1) {
    this->del = 2;
  } else {
    this->del = 1;
  }
}

int Event::wantToDel() {
  return this->del;
}

OneEvent Event::get_event_as_struct() {
  return {this->title, this->dscrpt, this->day, this->month, this->year, this->del};
}
