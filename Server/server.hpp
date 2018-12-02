#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <thread>
#include "connection.hpp"
#include <vector>


class Server {
private:
	SOCKET _tmpSock = INVALID_SOCKET;
	SOCKET _lSocket = INVALID_SOCKET;
	struct addrinfo* _result = NULL, *ptr = NULL, hints;
	std::thread* _listenThread = nullptr;


	CONNID _currentID = 1;	// JUST NU KAN VI BARA SUPPORTA 4 miljoner connections per run av servern, men det är antagligen inte ett problem, CONNID = 0 är error code
							//dessutom tror jag att den loopar sen så om inte den första jäveln e kvar äre chill, men detta är ez att fixa sen
	CONNID _generateID() {
		return _currentID++;
	}




	std::vector<Connection*> _conns;
public:
	Server();
	~Server();

	int initialize(int port);
	CONNID serverlisten();
	void serverRcv();
};

