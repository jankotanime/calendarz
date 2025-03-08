#include <wx/wx.h>
#include "MyApp.h"

void MyApp::OnPaint(wxPaintEvent& event) {
    wxPanel* panel = dynamic_cast<wxPanel*>(event.GetEventObject());
    wxPaintDC dc(panel);

    dc.SetPen(wxPen(wxColour(100, 100, 100), 5));
    dc.DrawLine(100, 50, 100, 350);
}
