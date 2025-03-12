#include <forward_list>
#include <iostream>

std::string get_month(int n) {
  std::forward_list<std::string> months = {"Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec", "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien"};
  for (int i = 0; i < n; i++) {
    months.pop_front();
  }
  std::string result = months.front();
  return result;
}
