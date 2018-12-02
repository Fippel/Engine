#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#define CONNID unsigned int
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <thread>



struct Connection {
private:
	SOCKET sock;
	CONNID id;
public:
	Connection(SOCKET sock, CONNID id);
	void close();
	SOCKET getSocket();
	CONNID getID();
};