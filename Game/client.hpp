#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>

class Client {
private:
	SOCKET _tcpSocket = INVALID_SOCKET;
	struct addrinfo* _result = NULL, *ptr = NULL, hints;

public:
	Client();
	~Client();
	void initialize(std::string ip, int port);
};