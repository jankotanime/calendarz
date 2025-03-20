#include <forward_list>
#include <list>
#include <iostream>
#include <chrono>
#include <wx/wx.h>
#include "../../include/Tile.h"
#include "../../include/Event.h"

struct Images {
  wxStaticBitmap* back, *add_event, *left, *right; 
};

struct EventDeleteImage {
  Event* event;
  wxStaticBitmap* img;
};

std::list<EventDeleteImage> deletes;

void remove_from_data(std::forward_list<Event>);
void add_to_data(OneEvent);

void showDeleteImages(std::list<EventDeleteImage>& deletes, Tile tile) {
  int line = 0;
  for (EventDeleteImage del : deletes) {
    del.event->cancelDelEvent();
    if (del.event->getDay() == tile.getDay() && del.event->getMonth() == tile.getMonth() 
    && del.event->getYear() == tile.getYear() && del.event->getTitle() != "") {
      del.img -> Show();
      del.img -> Move(500, 160+line*60);
      line++;
    }
  }
}

void hideDeleteImages(std::list<EventDeleteImage> &deletes) {
  for (EventDeleteImage& del : deletes) {
    del.event->cancelDelEvent();
    del.img -> Hide();
  } 
}

void paint_delete_images(std::forward_list<Event>& events, Tile& tile, wxPanel* panel) {
  for (auto& del : deletes) {
    del.img->Destroy();
  }
  deletes = {};
  for (auto& event : events) {
    wxBitmap image_delete("src/img/delete.png", wxBITMAP_TYPE_JPEG);
    wxStaticBitmap* new_delete = new wxStaticBitmap(panel, wxID_ANY, image_delete, wxPoint(400, 400), wxSize(32, 32));
    deletes.push_back({&event, new_delete});
    new_delete->Bind(wxEVT_LEFT_DOWN, [&event, &events, new_delete](wxMouseEvent&) {
      event.delEvent(events);
      if (event.getDay() == 0) {
        new_delete->Hide();
      }
      remove_from_data(events);
    });

    new_delete->Bind(wxEVT_SHOW, [&event, new_delete, &tile](wxShowEvent&) {
      if (!(new_delete->IsShown())) {
        showDeleteImages(deletes, tile);
      }
    });

    new_delete->Hide();
  }
}

Images paint_images(int width, int height, std::tm* localTime, Tile& tile, std::forward_list<Event>& events, wxPanel* panel) {
  wxBitmap image_go_back("src/img/return.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* go_back = new wxStaticBitmap(panel, wxID_ANY, image_go_back, wxPoint(1100, 10), wxSize(80, 80));

  wxBitmap image_arrow_left("src/img/arrow_left.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_left = new wxStaticBitmap(panel, wxID_ANY, image_arrow_left, wxPoint(20, 20), wxSize(82, 20));

  wxBitmap image_arrow_right("src/img/arrow_right.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* arrow_right = new wxStaticBitmap(panel, wxID_ANY, image_arrow_right, wxPoint(1000, 20), wxSize(82, 20));

  wxBitmap image_add_event("src/img/add_event.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* add_event = new wxStaticBitmap(panel, wxID_ANY, image_add_event, wxPoint(620, 800), wxSize(300, 80));

  wxBitmap image_accept("src/img/accept.png", wxBITMAP_TYPE_JPEG);
  wxStaticBitmap* accept = new wxStaticBitmap(panel, wxID_ANY, image_accept, wxPoint(800, 800), wxSize(80, 80));
  
  wxTextCtrl* title = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 810), wxSize(300, 30));
  wxTextCtrl* dscrt = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 850), wxSize(700, 30));
  wxFont font(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  title->SetFont(font);
  dscrt->SetFont(font);
  
  paint_delete_images(events, tile, panel);
  
  title->Hide();
  dscrt->Hide();
  accept->Hide();
  go_back->Hide();
  add_event->Hide();

  go_back->Bind(wxEVT_SHOW, [go_back, &tile](wxShowEvent) {
    if (go_back->IsShown()) {
      showDeleteImages(deletes, tile);
    } else {
    }
  });

  go_back->Bind(wxEVT_LEFT_DOWN, [&tile, title, dscrt, accept, go_back, arrow_left, arrow_right, add_event](wxMouseEvent&) {
    title->Hide();
    dscrt->Hide();
    accept->Hide();
    go_back->Hide();
    add_event->Hide();
    arrow_left->Show();
    arrow_right->Show();
    tile.changeDate(0, 0, 0);
    hideDeleteImages(deletes);
  });

  add_event->Bind(wxEVT_LEFT_DOWN, [&tile, &events, add_event, title, dscrt, accept, panel](wxMouseEvent&) {
    title->Show();
    dscrt->Show();
    accept->Show();
    add_event->Hide();
    title->SetValue("");
    dscrt->SetValue("");
    accept->Bind(wxEVT_LEFT_DOWN, [title, dscrt, add_event, accept, &tile, &events, panel](wxMouseEvent&) {
      if (title->GetValue().ToStdString() != "" && dscrt->GetValue().ToStdString() != "") {
        Event event = Event(title->GetValue().ToStdString(), dscrt->GetValue().ToStdString(), 
        tile.getDay(), tile.getMonth(), tile.getYear());
        events.push_front(event);
        title->Hide();
        dscrt->Hide();
        accept->Hide();
        add_event->Show();
        title->SetValue("");
        dscrt->SetValue("");
        add_to_data(event.get_event_as_struct());
        paint_delete_images(events, tile, panel);
      }
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
  
  Images images = {go_back, add_event, arrow_left, arrow_right};
  return images;
}
