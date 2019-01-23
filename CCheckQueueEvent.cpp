#include "CCheckQueueEvent.h"

CCheckQueueEvent::CCheckQueueEvent(int winid, wxEventType commandType)
	:wxEvent(winid, commandType)
{
}

wxEvent * CCheckQueueEvent::Clone() const
{
	return new CCheckQueueEvent(this->GetId());
}
