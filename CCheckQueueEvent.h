#ifndef __UCCHECKQUEUEEVENT_H__
#define __UCCHECKQUEUEEVENT_H__

#define EVT_SOCKET_SERVER_ACCEPT	8192
#define EVT_SOCKET_SERVER_INPUT		8193
#define EVT_SOCKET_CLIENT			8194

#include <wx/event.h>
#include "logorc.h"
class CCheckQueueEvent :public wxEvent
{
public:
	CCheckQueueEvent(int winid = 0, wxEventType commandType = wxEVT_NULL);
	virtual wxEvent *Clone() const;
};
#endif
