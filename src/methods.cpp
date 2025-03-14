#include <iostream>
#include <forward_list>
#include <chrono>
#include "../include/Tile.h"
#include "../include/Event.h"

struct OneTile {
  int day, month, year; 
};

void pick_tile(OneTile newTile) {
  Tile tile = Tile(newTile.day, newTile.month, newTile.year);
}

std::string get_month(int n) {
  std::forward_list<std::string> months = {"Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec", "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien"};
  for (int i = 0; i < n; i++) {
    months.pop_front();
  }
  std::string result = months.front();
  return result;
}
