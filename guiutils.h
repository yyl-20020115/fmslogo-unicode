// -*- c++ -*-
#include <stddef.h>

class wxMenu;
class wxMenuBar;
class wxTopLevelWindow;

struct MENUITEM 
{
    const wchar_t *  MenuText;
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
    const wchar_t *      ChildMenuText,
    const MENUITEM *  ChildMenuItems,
    size_t            ChildMenuItemsLength
    );
