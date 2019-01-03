// -*- c++ -*-
#ifndef __FMSLOGO_H_
#define __FMSLOGO_H_

#include "logocore.h" // for MAX_BUFFER_SIZE

class CMainFrame;
class wxFileName;
struct NODE;

///////////////////////////////////////////////////////////////
// Constants
const int DEFAULT_COMMANDER_HEIGHT = 150;
const int MIN_COMMANDER_HEIGHT     = 110;
const int DEFAULT_SPLITTER_WIDTH   = 5;

///////////////////////////////////////////////////////////////
// Global Variables

extern int  BitMapWidth;
extern int  BitMapHeight;

extern bool bFixed;
extern class wxString edit_editexit; // editor callback instruction list

///////////////////////////////////////////////////////////////
// Functions
void single_step_box(NODE * the_line);
wxString promptuser(const wchar_t *prompt);

#ifdef FMSLOGO_WXWIDGETS

#include "wx/app.h"

///////////////////////////////////////////////////////////////
// Classes
class CFmsLogo : public wxApp
{
public:
    CFmsLogo();

    static CMainFrame * GetMainFrame();

    virtual bool OnInit();
    virtual int  OnExit();

    void OnIdle(wxIdleEvent & Event);

private:
    void ProcessCommandLine();
	void LoadLocalizedStringFile();

    DECLARE_NO_COPY_CLASS(CFmsLogo)
    DECLARE_EVENT_TABLE();
    
private:
    bool hasLoadedFileToLoad;
    bool hasRunStartup;
};

#endif // FMSLOGO_WXWIDGETS

#endif // __FMSLOGO_H_
