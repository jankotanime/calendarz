#include <iostream>
#include <math.h>
#include <wx/wx.h>
#include "../../include/Tile.h"
#include "../../include/MyApp.h"

Tile::Tile(int d, int m, int y) : day(d), month(m), year(y) {};

void Tile::myDate() {
  std::cout << this->day << std::endl;
}

int Tile::getDay() {
  return this->day;
}

int Tile::getMonth() {
  return this->month;
}

int Tile::getYear() {
  return this->year;
}

void Tile::changeDate(int d, int m, int y) {
  this->day = d;
  this->month = m;
  this->year = y;
}
