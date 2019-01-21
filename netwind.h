// -*- c++ -*-
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

#ifndef __NETWND_H_
#define __NETWND_H_
#include <wx/socket.h>
#include <wx/event.h>
#ifdef _WINDOWS
#include <windows.h>
#include <winsock.h>
#else
#include <sys/socket.h>
#include <netdb.h>
#ifndef HWND
#define HWND void*
#endif
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef LONG
#define LONG long
#endif
#ifndef MAXGETHOSTSTRUCT
#define MAXGETHOSTSTRUCT 1024
#endif
#ifndef HOSTENT
#define HOSTENT hostent
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif

#endif

#define EVT_SOCKET_SERVER_ACCEPT	8192
#define EVT_SOCKET_SERVER_INPUT		8193
#define EVT_SOCKET_CLIENT			8194

struct NODE;

class CNetworkConnectionEvent :public wxEvent
{
public:
	CNetworkConnectionEvent(int winid = 0, wxEventType commandType = wxEVT_NULL);
	virtual wxEvent *Clone() const;
};
// Abstract base class for network connections
class CNetworkConnection 
{
public:
    bool IsEnabled() const;
    void Disable();

    NODE * GetLastPacketReceived() const;
    void SetLastPacketReceived(const wxString& LastPacket);

    void Shutdown();

	bool SendValue(const wxString& Data);

protected:
	CNetworkConnection(); // enforce abstract class
	~CNetworkConnection(); // enforce abstract class
	
    void Enable(
        const wxString&    OnSendReady,
        const wxString&    OnReceiveReady
        );

    // private helper functions
    void AsyncReceive();

    void AsyncClose();

	void PostCheckQueue();

    void PostOnSendReadyEvent();

	virtual wxSocketBase* GetWorkerSocket();
	bool SendValue(const char * Data);

    // private member variables
    wxSocketBase* m_Socket;       // socket for the connection
    bool   m_IsConnected;  // socket is connected
    bool   m_IsBusy;       // socket is too busy to send
    bool   m_IsEnabled;    // if message processing is enabled for this socket

	wxString m_OnReceiveReady;  // Buffer for receive callback
	wxString m_OnSendReady;     // Buffer for send    callback
    wxString m_ReceiveValue;    // pointer to the last packet received


    // Private helper class for buffering (carrying over) network
    // data from  one "receive" call to another.
    class CCarryOverBuffer 
    {
    public:
        CCarryOverBuffer();

        void ReleaseBuffer();

        void Append(const char * AppendBuffer, int AppendBufferLength);
        void ShiftLeft(int ShiftAmount);

		char * m_Buffer;
        int    m_BufferSize;
        int    m_BytesOfData;
    };

    CCarryOverBuffer m_CarryOverData;  // a buffer for carrying over partial packets 
                                       // from one recv() call to the next.
};

// Class for client network connections
class CClientNetworkConnection : public CNetworkConnection
{
private:

    unsigned int m_RemotePort;
	wxString m_RemoteHostName;

public:
    CClientNetworkConnection();
	~CClientNetworkConnection();

    void
    Enable(
        const wxString&    OnSendReady,
        const wxString&    OnReceiveReady,
        unsigned int    RemotePort,
        const wxString&    RemoteHostName
        );

    int OnEvent(wxEvtHandler& handler, wxSocketEvent & event);

};


// Class for server network connections
class CServerNetworkConnection : public CNetworkConnection
{
public:
	CServerNetworkConnection();
	~CServerNetworkConnection();
public:
    void Enable(
        const wchar_t *    OnSendReady,
        const wchar_t *    OnReceiveReady,
        unsigned int    ServerPort
        );
	
    int OnAccept(wxEvtHandler& handler, wxSocketEvent & event);
	int OnInputOutput(wxEvtHandler& handler, wxSocketEvent & event);

protected:
	virtual wxSocketBase* GetWorkerSocket();

	wxSocketBase* m_Worker;

	unsigned int m_ServerPort;

};

// function declarations
extern NODE *lnetaccepton(NODE *args);
extern NODE *lnetacceptoff(NODE *arg);
extern NODE *lnetacceptsendvalue(NODE *args);
extern NODE *lnetacceptreceivevalue(NODE *arg);
extern NODE *lnetconnecton(NODE *args);
extern NODE *lnetconnectoff(NODE *arg);
extern NODE *lnetconnectsendvalue(NODE *args);
extern NODE *lnetconnectreceivevalue(NODE *arg);
extern NODE *lnetstartup(NODE *args);
extern NODE *lnetshutdown(NODE *arg);

// global variables
extern CClientNetworkConnection g_ClientConnection;
extern CServerNetworkConnection g_ServerConnection;

#endif // __NETWND_H_
