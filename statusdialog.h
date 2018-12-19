// -*- c++ -*-

#include <wx/dialog.h>

class wxStaticText;

class CStatusDialog : public wxDialog
{
public:
    CStatusDialog(wxWindow *Parent);
    void PopulateAllFields();

    void SetPenContact(bool PenIsUp);
    void SetPenWidth(int PenWidth);
    void SetPenStyle(const wchar_t * PenStyle);
    void SetTurtleHeading(double Heading);
    void SetTurtlePitch(double Pitch);
    void SetTurtleRoll(double Roll);
    void SetTurtlePosition(double X, double Y, double Z);
    void SetTurtleId(int TurtleId);
    void SetTurtleVisibility(bool IsShown);
    void SetPenColor(int Red, int Green, int Blue);
    void SetScreenColor(int Red, int Green, int Blue);
    void SetFloodColor(int Red, int Green, int Blue);
    void SetCalls(long long TotalCalls);
    void SetPeakMemory(int TotalNodes);
    void SetVectors(int TotalVectors);
    void SetPolygons(int TotalPolygons);

private:
    void OnClose(wxCloseEvent& event);

    wxStaticText * m_PenContact;
    wxStaticText * m_PenWidth;
    wxStaticText * m_PenStyle;

    wxStaticText * m_TurtleHeading;
    wxStaticText * m_TurtlePitch;
    wxStaticText * m_TurtleRoll;

    wxStaticText * m_TurtlePosition;
    wxStaticText * m_TurtleId;
    wxStaticText * m_TurtleVisibility;

    wxStaticText * m_PenColor;
    wxStaticText * m_FloodColor;
    wxStaticText * m_ScreenColor;

    wxStaticText * m_TotalCalls;
    wxStaticText * m_PeakMemory;
    wxStaticText * m_TotalVectors;
    wxStaticText * m_TotalPolygons;

    DECLARE_EVENT_TABLE();
};
