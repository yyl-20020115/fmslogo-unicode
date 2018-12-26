#ifndef __GUIUTILS_H__
#define __GUIUTILS_H__
// -*- c++ -*-
#include <stddef.h>
#include <wx/string.h>

class wxMenu;
class wxMenuBar;
class wxTopLevelWindow;

struct MENUITEM 
{
	const wxString&  MenuText;
    int           MenuId;
};

void
SetFmsLogoIcon(
    wxTopLevelWindow & TopLevelWindow
    );

void
FillMenu(
    wxMenu *          Menu,
    const MENUITEM *  MenuItems,
    size_t            MenuItemsLength
    );

void
AppendChildMenu(
    wxMenuBar *       MainMenu,
    const wxString&      ChildMenuText,
    const MENUITEM *  ChildMenuItems,
    size_t            ChildMenuItemsLength
    );
#endif
