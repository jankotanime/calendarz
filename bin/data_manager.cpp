#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <forward_list>
#include "Event.h"

struct OneEvent
{
  std::string title, dscrpt;
  int day, month, year;
};


std::forward_list<Event> scan_data() {
  std::ifstream file("data/events.csv");

  std::forward_list<Event> events;

  if (!file.is_open()) {
    std::cerr << "Nie można otworzyć pliku!" << std::endl;
  }

  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::vector<std::string> row;
    std::string cell;

    while (std::getline(ss, cell, ';')) {
      row.push_back(cell);
    }

    if (row.size() < 5) continue;

    try {
        OneEvent event = {
            row[0], row[1],
            std::stoi(row[2]),
            std::stoi(row[3]),
            std::stoi(row[4])
        };
      events.push_front(Event(event.title, event.dscrpt, event.day, event.month, event.year));
    } catch (const std::exception& e) {
      std::cerr << "Błąd konwersji danych w linii: " << line << "\n" << e.what() << "\n";
    }
  }
  file.close();

  return events;
}
