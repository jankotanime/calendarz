#include <forward_list>
#include <iostream>
#include "Tile.h"
#include <iostream>
#include <chrono>

struct Images {
  wxStaticBitmap* back;
  wxStaticBitmap* left;
  wxStaticBitmap* right; 
};

std::string get_month(int n) {
  std::forward_list<std::string> months = {"Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec", "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien"};
  for (int i = 0; i < n; i++) {
    months.pop_front();
  }
  std::string result = months.front();
  return result;
}

Images paint_images(int width, int height, std::tm* localTime, Tile& tile, wxPanel* panel) {
  wxBitmap image_go_back("img/test.jpg", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* go_back = new wxStaticBitmap(panel, wxID_ANY, image_go_back, wxPoint(1000, 800), wxSize(40, 40));

  wxBitmap image_arrow_left("img/arrow_left.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_left = new wxStaticBitmap(panel, wxID_ANY, image_arrow_left, wxPoint(20, 20), wxSize(82, 20));

  wxBitmap image_arrow_right("img/arrow_right.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_right = new wxStaticBitmap(panel, wxID_ANY, image_arrow_right, wxPoint(1000, 20), wxSize(82, 20));

  go_back->Bind(wxEVT_LEFT_DOWN, [&tile, go_back, arrow_left, arrow_right](wxMouseEvent&) {
    tile.changeDate(0, 0, 0);
    go_back->Hide();
    arrow_left->Show();
    arrow_right->Show();
  });

  arrow_left->Bind(wxEVT_LEFT_DOWN, [localTime](wxMouseEvent&) {
    localTime->tm_mon -= 1;
    if (localTime->tm_mon < 0) {
      localTime->tm_mon = 11;
      localTime->tm_year -= 1;
    }
  });

  arrow_right->Bind(wxEVT_LEFT_DOWN, [localTime](wxMouseEvent&) {
    localTime->tm_mon += 1;
    if (localTime->tm_mon > 11) {
      localTime->tm_mon = 0;
      localTime->tm_year += 1;
    }
  });

  go_back->Hide();
  
  Images images = {go_back, arrow_left, arrow_right};
  return images;
}
