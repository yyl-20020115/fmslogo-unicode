#include "wx/scrolwin.h"
#include "logocore.h" // for FLONUM //FIXED by YILIN: changed to ""(previously <>)

class wxClientDC;
class wxMemoryDC;
class wxBitMap;

class CScreen : public wxScrolled<wxWindow>
{
public:
    CScreen(wxWindow* parent, int width, int height);
    virtual ~CScreen();

    wxClientDC & GetScreenDeviceContext();
    wxMemoryDC & GetMemoryDeviceContext();
    wxMemoryDC & GetBackBufferDeviceContext();

    void AdjustScrollPositionToZoomFactor(FLONUM NewZoomFactor);

private:
    // event handlers
    void OnKeyDown(wxKeyEvent& Event);
    void OnKeyUp(wxKeyEvent& Event);
    void OnChar(wxKeyEvent& Event);
    void OnRightMouseButtonDown(wxMouseEvent& Event);
    void OnRightMouseButtonUp(wxMouseEvent& Event);
    void OnLeftMouseButtonDown(wxMouseEvent& Event);
    void OnLeftMouseButtonUp(wxMouseEvent& Event);
    void OnMouseMove(wxMouseEvent& Event);
    void OnScroll(wxScrollWinEvent & Event);
    void OnPaint(wxPaintEvent& PaintEvent);
    void OnSize(wxSizeEvent& Event);

    // helper functions
    void ScrollToRatio();

    // member variables
    wxClientDC * m_ScreenDeviceContext;
    wxMemoryDC * m_MemoryDeviceContext;
    wxBitmap   * m_MemoryBitmap;
    wxMemoryDC * m_BackBufferDeviceContext;
    wxBitmap   * m_BackBuffer;

    double       m_XScrollRatio;
    double       m_YScrollRatio;

    DECLARE_NO_COPY_CLASS(CScreen)
    DECLARE_EVENT_TABLE();
};
