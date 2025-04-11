#include <iostream>
#include <forward_list>
#include <chrono>
#include "../include/Tile.h"
#include "../include/Event.h"

struct OneTile {
  int day, month, year; 
};

struct Images {
  wxStaticBitmap* back, *add_event, *left, *right; 
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

int first_day_of_month(int year, int month) {
  std::tm tmDate = {};
  tmDate.tm_year = year;
  tmDate.tm_mon = month;
  tmDate.tm_mday = 1;

  std::time_t t_date = std::mktime(&tmDate);
  
  if (tmDate.tm_wday == 0) {
    return 6;
  } 
  if (tmDate.tm_wday == 1) {
    return 7;
  }
  return tmDate.tm_wday - 1;
}

int event_day(std::forward_list<Event> events, int d, int m, int y) {
  int result = 0;
  for (auto& event : events) {
    if (event.getDay() == d && event.getMonth() == m && event.getYear() == y) {
      result++;
      if (result >= 3) {
        break;
      } 
    }
  }
  return result;
}

void pick_day_handler(Tile& tile, Images images, int draw_day, int month, int year) {
  tile.changeDate(draw_day, month, year);
  images.back->Show();
  images.add_event->Show();
  images.left->Hide();
  images.right->Hide();
};

#include <wx/stdpaths.h>
#include <wx/filename.h>

wxString GetImagePath(const wxString& filename) {
  wxString basePath = wxStandardPaths::Get().GetExecutablePath();
  wxFileName path(basePath);
  path.RemoveLastDir();
  path.AppendDir("src");
  path.AppendDir("img");
  path.SetFullName(filename);
  return path.GetFullPath();
}

wxString GetDataPath() {
  wxString basePath = wxStandardPaths::Get().GetExecutablePath();
  wxFileName path(basePath);
  path.RemoveLastDir();
  path.AppendDir("src");
  path.AppendDir("data");
  path.SetFullName("events.csv");
  return path.GetFullPath();
}

int diffTimeToTommorow() {
  auto now = std::chrono::system_clock::now();
  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm* localTime = std::localtime(&time);
  std::tm localTimeC = *localTime;
  localTimeC.tm_mday+=1;
  localTimeC.tm_hour=0;
  localTimeC.tm_min=0;
  localTimeC.tm_sec=0;
  int result = floor(std::difftime(std::mktime(&localTimeC), std::mktime(localTime)));
  return result;
}