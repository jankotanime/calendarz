#ifndef TILE_H
#define TILE_H

#include <wx/wx.h>
#include <iostream>

class Tile {
  private:
  int day;
  int month;
  int year;
  public:
  Tile(int day, int month, int year);
  void myDate();
  int getDay();
  int getMonth();
  int getYear();
  void changeDate(int d, int m, int y);
};

#endif
