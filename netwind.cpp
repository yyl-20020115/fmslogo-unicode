// Copyright (C) 1995 by the Regents of the University of California
// Copyright (C) 1995 by George Mills
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
#include <wx/string.h>
#include <wx/msgdlg.h>
#include "netwind.h"
    #include "logoeventqueue.h"

    #include "init.h"
    #include "messagebox.h"
    #include "graphics.h"
    #include "argumentutils.h"
    #include "stringprintednode.h"
    #include "logodata.h"
    #include "logorc.h"
    #include "lists.h"
    #include "eval.h"
    #include "logomath.h"
    #include "parse.h"
    #include "screenwindow.h"
//    #include "debugheap.h"
    #include "localizedstrings.h"
#endif
#ifndef _WINDOWS
#include <sys/errno.h>
#include <unistd.h>
#endif
#include "FMSLogo.h"
/////////////////////////////////////////////////////////////////////////////////////
// Manifest Constants

const int MAX_PENDING_CONNECTS = 4;  // The backlog allowed for listen()

/////////////////////////////////////////////////////////////////////////////////////
// Global Variables

CClientNetworkConnection g_ClientConnection;
CServerNetworkConnection g_ServerConnection;

static int network_dns_sync = 0;

static bool network_is_started = false;
CNetworkConnectionEvent::CNetworkConnectionEvent(int winid, wxEventType commandType)
	:wxEvent(winid, commandType)
{
}

wxEvent * CNetworkConnectionEvent::Clone() const
{
	return new CNetworkConnectionEvent(this->GetId());
}
/////////////////////////////////////////////////////////////////////////////////////
// Helper Functions

// converts winsock errorcode to string
wxString GetLastErrorString(int error_arg)
{
    int error;

    if (error_arg != 0)
    {
        error = error_arg;
    }
    else
    {
#ifdef _WINDOWS
        error = WSAGetLastError();
#else
        error =errno;
#endif
    }

    switch (error)
    {
#ifdef _WINDOWS
    case WSAENAMETOOLONG:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNAMETOOLONG");
         
    case WSANOTINITIALISED:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTINITIALIZED");

    case WSASYSNOTREADY:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKSYSTEMNOTREADY");

    case WSAVERNOTSUPPORTED:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKVERSIONNOTSUPPORTED");

    case WSAESHUTDOWN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKSENDAFTERSHUTDOWN");

    case WSAEINTR:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKINTERRUPTED");

    case WSAHOST_NOT_FOUND:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDAUTH");

    case WSATRY_AGAIN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKHOSTNOTFOUNDNONAUTH");

    case WSANO_RECOVERY:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTRECOVERABLE");

    case WSANO_DATA:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNODATA");

    case WSAEBADF:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKBADFILENUMBER");
           
    case WSAEWOULDBLOCK:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKWOULDBLOCK");

    case WSAEINPROGRESS:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOWINPROGRESS");

    case WSAEALREADY:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYINPROGRESS");

    case WSAEFAULT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKBADADDRESS");

    case WSAEDESTADDRREQ:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNEEDDESTADDRESS");

    case WSAEMSGSIZE:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKMESSAGETOOLONG");

    case WSAEPFNOSUPPORT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKPFNOTSUPPORTED");
           
    case WSAENOTEMPTY:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKDIRNOTEMPTY");

    case WSAEPROCLIM:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKAPPLIMITREACHED");

    case WSAEDQUOT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKDISKQUOTA");

    case WSAEINVAL:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKINVALIDARGUMENTS");

    case WSAEMFILE:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKTOOMANYFILES");

    case WSAEACCES:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKACCESSDENIED");
         
    case WSAENOTSOCK:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTASOCKET");

    case WSAEADDRNOTAVAIL:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKADDRNOTAVAILABLE");

    case WSAEADDRINUSE:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKADDRINUSE");

    case WSAEAFNOSUPPORT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKAFNOTSUPPORTED");

    case WSAESOCKTNOSUPPORT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKTYPENOTSUPPORTED");
         
    case WSAEPROTONOSUPPORT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKPROTONOTSUPPORTED");

    case WSAENOBUFS:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOBUFFER");

    case WSAETIMEDOUT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKTIMEDOUT");

    case WSAEISCONN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYCONNECTED");

    case WSAENOTCONN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTCONNECTED");

    case WSAENOPROTOOPT:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKBADPROTOOPT");

    case WSAECONNRESET:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKCONNECTIONRESET");

    case WSAECONNABORTED:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKCONNECTIONABORT");

    case WSAENETDOWN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKISDOWN");

    case WSAENETRESET:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKRESET");

    case WSAECONNREFUSED:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKCONNECTIONREFUSED");

    case WSAEHOSTDOWN:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKHOSTISDOWN");
         
    case WSAEHOSTUNREACH:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKHOSTISUNREACHABLE");
          
    case WSAEPROTOTYPE:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKBADPROTOTYPE");
         
    case WSAEOPNOTSUPP:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKBADOPNOTSUPPORTED");

    case WSAENETUNREACH:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKUNREACHABLE");

    case WSAETOOMANYREFS:
        return GetResourceString(L"LOCALIZED_ERROR_NETWORKTOOMANYREFS");
#endif
    default:
        {
			//FIXED
			return wxString::Format(GetResourceString(L"LOCALIZED_UNKNOWN") + L" %d", error);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// private class CNetworkConnection::CCarryOverBuffer

CNetworkConnection::CCarryOverBuffer::CCarryOverBuffer() :
    m_Buffer(NULL),
    m_BufferSize(0),
    m_BytesOfData(0)
{
}

void CNetworkConnection::CCarryOverBuffer::ReleaseBuffer()
{
	if (m_Buffer != 0) {
		free(m_Buffer);
		m_Buffer = 0;

		m_BytesOfData = 0;
		m_BufferSize = 0;
	}
}

void CNetworkConnection::CCarryOverBuffer::Append(
    const char * AppendBuffer,
    int          AppendBufferLength
    )
{
    if (m_BufferSize < m_BytesOfData + AppendBufferLength + 1)
    {
        // there isn't enough room on the buffer.  Grow it.

        m_BufferSize += AppendBufferLength + 1; // leave room for NUL

        m_Buffer = (char*) realloc(m_Buffer, m_BufferSize);
    }

    memcpy(m_Buffer + m_BytesOfData, AppendBuffer, AppendBufferLength);

    m_BytesOfData += AppendBufferLength;

    // always keep m_Buffer NUL-terminated
    m_Buffer[m_BytesOfData] = '\0';
}

void CNetworkConnection::CCarryOverBuffer::ShiftLeft( int ShiftAmount)
{
    assert(0 <= ShiftAmount);
    assert(ShiftAmount <= m_BytesOfData);

    // shift the buffer such that it begins at "begin"
    memmove(m_Buffer, m_Buffer + ShiftAmount, m_BytesOfData - ShiftAmount);
   
    m_BytesOfData -= ShiftAmount;
}

/////////////////////////////////////////////////////////////////////////////////////
// class CNetworkConnection

CNetworkConnection::CNetworkConnection() :
    m_Socket(0),
    m_IsConnected(false),
    m_IsBusy(false),
    m_IsEnabled(false),
    m_OnReceiveReady(),
    m_OnSendReady(),
    m_ReceiveValue()
{
}

CNetworkConnection::~CNetworkConnection()
{
	if (this->m_Socket != 0) {
		this->m_Socket->Destroy();
		this->m_Socket = 0;
	}
}

void CNetworkConnection::SetLastPacketReceived(const wxString& LastPacket)
{
    this->m_ReceiveValue = LastPacket;
}

NODE* CNetworkConnection::GetLastPacketReceived() const
{
    if (m_ReceiveValue.length()==0)
    {
        return NIL;
    }
    else
    {
        NODE* targ = make_strnode(m_ReceiveValue);
        NODE* val = parser(targ, false);
        return val;
    }
}

bool CNetworkConnection::IsEnabled() const
{
    return m_IsEnabled;
}

void CNetworkConnection::Disable()
{
    if (this->IsEnabled())
    {
		this->m_IsEnabled    = false;
		this->m_IsConnected  = false;
		this->m_IsBusy       = false;

		this->m_ReceiveValue.clear();
		this->m_Socket->Close();
		this->m_Socket->Destroy();
        this->m_Socket = 0;
    }
}

void CNetworkConnection::Enable(
    const wxString&    OnSendReady,
    const wxString&   OnReceiveReady
    )
{
	this->m_OnSendReady = OnSendReady;
	this->m_OnReceiveReady = OnReceiveReady;
}

bool CNetworkConnection::SendValue(const char * Data)
{
	wxSocketBase* ws = this->GetWorkerSocket();

    if (ws!=0 && m_IsConnected && !m_IsBusy)
    {
		ws->Write(Data, strlen(Data) + 1);
        // send the data
		wxSocketError status = ws->LastError();
		if (status != wxSOCKET_NOERROR)
        {
            if (status != wxSOCKET_WOULDBLOCK)
            {
                ShowMessageAndStop(L"send(socket)", GetLastErrorString(ws->LastError()));
                return false;
            }
            // Don't send anymore until we receive confirmation
            // that the remote side received the data.
            m_IsBusy = true;
            return false;
        }
    }
    else
    {
        return false;
    }

    return true;
}

bool CNetworkConnection::SendValue(const wxString & Data)
{
	return this->SendValue((const char*)(Data.ToUTF8()));
}

void CNetworkConnection::AsyncReceive()
{
	wxSocketBase* ws = this->GetWorkerSocket();

	if (ws != 0) {
		char buffer[MAX_PACKET_SIZE + 1] = { 0 };

		ws->Read(buffer, sizeof(buffer) - 1);

		// read the data from the buffer
		wxSocketError status = ws->LastError();
		if (status != wxSOCKET_NOERROR)
		{
			if (status != wxSOCKET_WOULDBLOCK)
			{
				wxMessageBox(
					GetLastErrorString(status),
					L"recv(socket)",
					wxOK);
				// err_logo(STOP_ERROR,NIL);
			}
		}
		else
		{
			// we received some data.

			// We have some data left from the last time we were called.
			// Append this buffer to the end of the network receive buffer. 

			// TODO: Don't Append the data to the carry-over buffer if there is none.
			//       We should be able to use buffer, instead.
			m_CarryOverData.Append(buffer, status);

			// now queue up a separate message for each packet
			size_t begin = 0;
			size_t end = strlen(m_CarryOverData.m_Buffer);

			while ((int)end < m_CarryOverData.m_BytesOfData)
			{
				callthing * callevent = callthing::CreateNetworkReceiveReadyEvent(
					this,
					m_OnReceiveReady,
				    wxString::FromUTF8(m_CarryOverData.m_Buffer + begin));

				calllists.insert(callevent);

				this->PostCheckQueue();

				begin = end + 1;
				end = begin + strlen(m_CarryOverData.m_Buffer + begin);
			}

			// shift the buffer such that it begins at "begin"
			m_CarryOverData.ShiftLeft((int)begin);
		}
	}
}

void CNetworkConnection::AsyncClose()
{
    // send any data in the carry-over buffer upwards
    if (m_CarryOverData.m_BytesOfData != 0)
    {
        callthing *callevent = callthing::CreateNetworkReceiveReadyEvent(
            this,
            m_OnReceiveReady,
            wxString::FromUTF8(m_CarryOverData.m_Buffer));

        calllists.insert(callevent);

		this->PostCheckQueue();

    }

    m_CarryOverData.ReleaseBuffer();

    m_IsConnected = false;
}

void CNetworkConnection::PostCheckQueue()
{
//#ifdef _WINDOWS
//    PostMessage(GetMainWindow(), WM_CHECKQUEUE, 0, 0);
//#endif
	wxQueueEvent(wxTheApp->GetTopWindow(), new CNetworkConnectionEvent(WM_CHECKQUEUE));
}

void CNetworkConnection::Shutdown()
{
	this->Disable();
	this->m_OnSendReady.clear();
	this->m_OnReceiveReady.clear();
	this->SetLastPacketReceived(wxString());
	this->m_CarryOverData.ReleaseBuffer();
}

void CNetworkConnection::PostOnSendReadyEvent()
{
    // we don't distinguish between all event types
    callthing *callevent = callthing::CreateNoYieldFunctionEvent(m_OnSendReady);

    calllists.insert(callevent);

	this->PostCheckQueue();
}

wxSocketBase * CNetworkConnection::GetWorkerSocket()
{
	return this->m_Socket;
}

CClientNetworkConnection::CClientNetworkConnection()
	: m_RemotePort(0)
	, m_RemoteHostName()
{
}

CClientNetworkConnection::~CClientNetworkConnection()
{
}

void CClientNetworkConnection::Enable(
    const wxString& OnSendReady,
    const wxString& OnReceiveReady,
    unsigned int RemotePort,
    const wxString& RemoteHostName
    )
{
    CNetworkConnection::Enable(OnSendReady, OnReceiveReady);
    if (NOT_THROWING)
    {
		this->m_Socket = new wxSocketClient();

		if (this->m_Socket != 0) 
		{
			// get sockets
			if (!this->m_Socket->Ok())
			{
				this->m_Socket->Destroy();
				this->m_Socket = 0;
				ShowMessageAndStop(L"socket()", GetLastErrorString(this->m_Socket->LastError()));
				return;
			}
		}

		wxIPV4address addr;
		if (!addr.Hostname(RemoteHostName))
		{

		}
		if (!addr.Service(RemotePort))
		{

		}

		if (!((wxSocketClient*)this->m_Socket)->Connect(addr, false))
		{

		}
		wxSocketError status = this->m_Socket->LastError();

		if (status != wxSOCKET_NOERROR)
		{
			if (status != wxSOCKET_WOULDBLOCK)
			{
				wxMessageBox(
					GetLastErrorString(0),
					L"connect(sendsock)",
					wxOK);
				return;

				// err_logo(STOP_ERROR,NIL);
			}
		}
		this->m_RemotePort = RemotePort;
		this->m_IsEnabled = true;

        if (network_dns_sync == 1)
        {

        }
        else
        {
            // The rest of the connection will be set up when the GetHostByName
            // callback is invoked, after m_HostEntry is filled in.
        }
    }
}

int CClientNetworkConnection::OnEvent(wxEvtHandler & handler, wxSocketEvent & event)
{
	if (!IsEnabled())
	{
		// The network client side has been shut down.
		// This message must have been delayed.
				// This must be a delayed event coming in after shutdown.
		wxMessageBox(
			GetResourceString(L"LOCALIZED_ERROR_NETWORKSHUTDOWN"),
			GetResourceString(L"LOCALIZED_ERROR_NETWORK"),
			wxOK);

		return 0;
	}

	wxSocketBase * sock = event.GetSocket();
	if (sock == this->GetWorkerSocket()) {
		switch (event.GetSocketEvent())
		{
		case wxSOCKET_CONNECTION:
		{
			this->m_IsConnected = true;

			break;
		}
		case wxSOCKET_INPUT:
		{
			this->AsyncReceive();
			break;
		}
		case wxSOCKET_LOST:
		{
			this->AsyncClose();
			break;
		}
		case wxSOCKET_OUTPUT:
			// allow another frame to go out.
			this->m_IsBusy = false;
			break;
		}
	}
	this->PostOnSendReadyEvent();
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
// CServerNetworkConnection class

CServerNetworkConnection::CServerNetworkConnection()
	: m_Worker(0)
	, m_ServerPort(0)
{
}

CServerNetworkConnection::~CServerNetworkConnection()
{
	if (this->m_Worker != 0) {
		this->m_Worker->Destroy();
		this->m_Worker = 0;
	}
}

void CServerNetworkConnection::Enable(
    const wchar_t *    OnSendReady,
    const wchar_t *    OnReceiveReady,
    unsigned int    ServerPort
    )
{
    CNetworkConnection::Enable(OnSendReady, OnReceiveReady);

	if (NOT_THROWING)
	{
		wxIPV4address addr;
		if (!addr.Service(ServerPort))
		{
			//
		}

		this->m_Socket = new wxSocketServer(addr);
		if (!this->m_Socket->Ok())
		{
			this->m_Socket->Destroy();
			this->m_Socket = 0;
			return;
		}

		this->m_ServerPort = ServerPort;
		this->m_Socket->SetEventHandler(*wxTheApp->GetTopWindow(), EVT_SOCKET_SERVER_ACCEPT);
		this->m_Socket->SetNotify(wxSOCKET_CONNECTION_FLAG);
		this->m_Socket->Notify(true);

        // watch for when connect happens
        this->m_IsEnabled = true;

        // queue this event
		this->PostOnSendReadyEvent();

    }
}

// Call this to handle a WM_NETWORK_LISTENRECEIVEACK message.
int CServerNetworkConnection::OnAccept(wxEvtHandler& handler, wxSocketEvent & event)
{
    if (!IsEnabled())
    {
        // The server-side is not initialized.
        // This must be a delayed event coming in after shutdown.
        return 0;
    }
	if (this->m_Socket != 0) {

		wxSocketBase * sock = ((wxSocketServer*)this->m_Socket)->Accept(false);
		if (!sock->IsOk())
		{
			wxMessageBox(
				GetLastErrorString(0),
				L"accept(receivesock)",
				wxOK);
			sock->Destroy();
			sock = 0;

			// err_logo(STOP_ERROR,NIL);
			return 0;
		}
		sock->SetEventHandler(handler, EVT_SOCKET_SERVER_INPUT);
		sock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
		sock->Notify(true);

		if (this->m_Worker != 0) {
			this->m_Worker->Destroy();
			this->m_Worker = 0;
		}
		this->m_Worker = sock;
		this->m_IsConnected = true;

		// all other events just queue the event
		this->PostOnSendReadyEvent();
	}
    return 0;
}

int CServerNetworkConnection::OnInputOutput(wxEvtHandler& handler, wxSocketEvent & event)
{
	wxSocketBase * sock = event.GetSocket();
	if (sock == this->GetWorkerSocket()) 
	{
		switch (event.GetSocketEvent())
		{
			case wxSOCKET_INPUT:
			{
				this->AsyncReceive();
				break;
			}
			case wxSOCKET_OUTPUT:
			{
				this->m_IsBusy = false;
				break;
			}
			case wxSOCKET_LOST:
			{
				this->AsyncClose();
				break;
			}
		}
	}
	return 0;
}

wxSocketBase * CServerNetworkConnection::GetWorkerSocket()
{
	return this->m_Worker;
}

// startup network
NODE *lnetstartup(NODE *args)
{
    // check if already started
    if (network_is_started)
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORK"),
            GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYSTARTED"));
        return Unbound;
    }

    if (args != NIL)
    {
        network_dns_sync = int_arg(args);
    }

    network_is_started = true;
    return Unbound;
}

// put everything back to original state
NODE *lnetshutdown(NODE *)
{
    // cleanup receive
    g_ServerConnection.Shutdown();

    // cleanup send
    g_ClientConnection.Shutdown();

    // cleanup library
    if (network_is_started)
    {
        // There seems to be a race condition with WSAAsyncGetHostByName
        // in that WSACleanup() won't always cancel the callback.
        // As a result, it could still attempt to write into the
        // m_HostEntry.Entry field after it has been freed.
        //
        // This is not a problem for the current implementation, since it
        // statically allocates the memory and never frees it.
        // However, it could be a problem if g_ServerConnection and
        // g_ClientConnection were dynamically allocated.

        network_is_started = false;
    }

    network_dns_sync = 0;
    return Unbound;
}

// enable receiving
NODE *lnetaccepton(NODE *args)
{
    // check sanity
    if (!network_is_started)
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORK"), 
            GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTSTARTED"));
        return Unbound;
    }

    if (g_ServerConnection.IsEnabled())
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORKRECEIVE"), 
            GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYON"));
        return Unbound;
    }

    // get args (socket and callback)
    int port = getint(nonnegative_int_arg(args));

	wxString networksend = cnv_strnode_string(cdr(args));

    wxString networkreceive = cnv_strnode_string(cdr(cdr(args)));

    if (NOT_THROWING)
    {
        g_ServerConnection.Enable(networksend, networkreceive, port);
    }

    if (NOT_THROWING)
    {
        return Truex.GetNode();
    }

    return Unbound;
}

NODE *lnetacceptoff(NODE *)
{
    // tell handler not to do anything with messages for network receive
    if (g_ServerConnection.IsEnabled())
    {
        g_ServerConnection.Disable();
    }
    else
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORKRECEIVE"), 
            GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYOFF"));
    }

    return Unbound;
}

NODE *lnetacceptreceivevalue(NODE *)
{
    // return current network value
    if (g_ServerConnection.IsEnabled())
    {
        return g_ServerConnection.GetLastPacketReceived();
    }

    return Unbound;
}

NODE *lnetconnectreceivevalue(NODE *)
{
    // return current network value
    if (g_ClientConnection.IsEnabled())
    {
        return g_ClientConnection.GetLastPacketReceived();
    }

    return Unbound;
}

NODE *lnetconnecton(NODE *args)
{
    // sanity check first
    if (!network_is_started)
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORK"), 
            GetResourceString(L"LOCALIZED_ERROR_NETWORKNOTSTARTED"));
        return Unbound;
    }

    if (g_ClientConnection.IsEnabled())
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORKSEND"), 
            GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYON"));
        return Unbound;
    }

    // get args (remotemachinename, socket, callback)
    CStringPrintedNode remotehostname(car(args));

    int remote_port = getint(nonnegative_int_arg(cdr(args)));

	wxString networksend = cnv_strnode_string(cdr(cdr(args)));

	wxString networkreceive= cnv_strnode_string(cdr(cdr(cdr(args))));

    if (NOT_THROWING)
    {
        g_ClientConnection.Enable(
            networksend,
            networkreceive,
            remote_port,
            remotehostname);
    }

    if (NOT_THROWING)
    {
        return Truex.GetNode();
    }

    return Unbound;
}

NODE *lnetconnectoff(NODE *)
{
    // tell handler not to do anything with messages for network send
    if (g_ClientConnection.IsEnabled())
    {
        g_ClientConnection.Disable();
    }
    else
    {
        ShowMessageAndStop(
            GetResourceString(L"LOCALIZED_ERROR_NETWORKSEND") ,
            GetResourceString(L"LOCALIZED_ERROR_NETWORKALREADYOFF"));
    }

    return Unbound;
}

NODE *lnetconnectsendvalue(NODE *args)
{
    // get args (data)
    CStringPrintedNode data(car(args));

    if (NOT_THROWING)
    {
        // try to send data
        bool isOk = g_ClientConnection.SendValue(data);
        return true_or_false(isOk);
    }

    return Unbound;
}

NODE *lnetacceptsendvalue(NODE *args)
{
    // get args (data)
    CStringPrintedNode data(car(args));

    if (NOT_THROWING)
    {
        // try to send data
        bool isOk = g_ServerConnection.SendValue(data);
        return true_or_false(isOk);
    }

    return Unbound;
}
