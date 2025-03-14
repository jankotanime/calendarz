#include "Event.h"
#include <wx/wx.h>
#include "MyApp.h"
#include <iostream>
#include <math.h>

Event::Event(std::string t, std::string dr, int d, int m, int y) : title(t), dscrpt(dr), day(d), month(m), year(y) {
  std::cout << "event" << std::endl;
};

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

OneEvent Event::get_event_as_struct() {
  return {this->title, this->dscrpt, this->day, this->month, this->year};
}
