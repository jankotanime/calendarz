#include <forward_list>
#include <iostream>
#include "Tile.h"
#include <iostream>
#include <chrono>
#include "Event.h"

struct Images {
  wxStaticBitmap* back, *add_event, *left, *right; 
};

std::string get_month(int n) {
  std::forward_list<std::string> months = {"Styczen", "Luty", "Marzec", "Kwiecien", "Maj", "Czerwiec", "Lipiec", "Sierpien", "Wrzesien", "Pazdziernik", "Listopad", "Grudzien"};
  for (int i = 0; i < n; i++) {
    months.pop_front();
  }
  std::string result = months.front();
  return result;
}

Images paint_images(int width, int height, std::tm* localTime, Tile& tile, std::forward_list<Event>& events, wxPanel* panel) {
  wxBitmap image_go_back("img/return.jpg", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* go_back = new wxStaticBitmap(panel, wxID_ANY, image_go_back, wxPoint(1000, 800), wxSize(40, 40));

  wxBitmap image_arrow_left("img/arrow_left.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_left = new wxStaticBitmap(panel, wxID_ANY, image_arrow_left, wxPoint(20, 20), wxSize(82, 20));

  wxBitmap image_arrow_right("img/arrow_right.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_right = new wxStaticBitmap(panel, wxID_ANY, image_arrow_right, wxPoint(1000, 20), wxSize(82, 20));

  wxBitmap image_add_event("img/add_event.jpg", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* add_event = new wxStaticBitmap(panel, wxID_ANY, image_add_event, wxPoint(1000, 20), wxSize(40, 40));

  wxBitmap image_accept("img/accept.jpg", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* accept = new wxStaticBitmap(panel, wxID_ANY, image_accept, wxPoint(800, 400), wxSize(40, 40));
  
  wxTextCtrl* title = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 20), wxSize(100, 30));
  wxTextCtrl* dscrt = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 60), wxSize(400, 30));
  
  title->Hide();
  dscrt->Hide();
  accept->Hide();

  go_back->Bind(wxEVT_LEFT_DOWN, [&tile, title, dscrt, accept, go_back, arrow_left, arrow_right, add_event](wxMouseEvent&) {
    tile.changeDate(0, 0, 0);
    go_back->Hide();
    add_event->Hide();
    title->Hide();
    dscrt->Hide();
    accept->Hide();
    arrow_left->Show();
    arrow_right->Show();
  });


  add_event->Bind(wxEVT_LEFT_DOWN, [&tile, &events, title, dscrt, accept, panel](wxMouseEvent&) {
    accept->Show();
    title->Show();
    dscrt->Show();
    title->SetValue("");
    dscrt->SetValue("");
    accept->Bind(wxEVT_LEFT_DOWN, [title, dscrt, accept, &tile, &events](wxMouseEvent&) {
      Event event = Event(title->GetValue().ToStdString(), dscrt->GetValue().ToStdString(), tile.getDay(), tile.getMonth(), tile.getYear());
      events.push_front(event);
      title->SetValue("");
      dscrt->SetValue("");
      title->Hide();
      dscrt->Hide();
      accept->Hide();
    });
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
  add_event->Hide();
  
  Images images = {go_back, add_event, arrow_left, arrow_right};
  return images;
}
