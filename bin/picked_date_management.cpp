#include <wx/wx.h>
#include "Tile.h"
#include <iostream>

struct OneTile {
  int day, month, year; 
};

void pick_tile(OneTile newTile) {
  Tile tile = Tile(newTile.day, newTile.month, newTile.year);
}