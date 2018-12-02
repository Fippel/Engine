#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_PORT "10101"
#include "server.hpp"
#define DEFAULT_BUFLEN 512

void slisten(SOCKET listenSocket, SOCKET* target) {

	*target = accept(listenSocket, NULL, NULL);
	if (*target == INVALID_SOCKET) {
		printf("accept failed %d\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
	}


}

Server::Server() {
	

}

Server::~Server() {

}

int Server::initialize(int port) {
	WSADATA wsaData;

	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
	}
	

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &_result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	this->_lSocket = INVALID_SOCKET;

	_lSocket = socket(_result->ai_family, _result->ai_socktype, _result->ai_protocol);
	if (_lSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(_result);
		WSACleanup();
		return 1;
	}


	//Setup TCP LISTENING SOCKET
	iResult = bind(_lSocket, _result->ai_addr, (int)_result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(_result);
		closesocket(_lSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(_result);


	if (listen(_lSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(_lSocket);
		WSACleanup();
	}

	//LISTEN FOR NEW CONNECTIONS

	this->_tmpSock = INVALID_SOCKET;
	_listenThread = new std::thread(slisten, _lSocket, &(this->_tmpSock));

	return 0;
}

CONNID Server::serverlisten() {
	if (this->_tmpSock == INVALID_SOCKET || _listenThread->joinable() != true)
		return 0;

	_listenThread->join();
	unsigned long iMode = 1;
	
	int iResult = ioctlsocket(this->_tmpSock, FIONBIO, &iMode);
	if (iResult != NO_ERROR) {
		printf("ioctlsocket failed with error %ld\n", iResult);
	}

	CONNID id = this->_generateID();
	printf("New TCP connection to server with ID: %d\n", id);
	_conns.push_back(new Connection(this->_tmpSock, id));

	this->_tmpSock = INVALID_SOCKET;
	delete _listenThread;
	_listenThread = new std::thread(slisten, _lSocket, &(this->_tmpSock));

	return id;
}

void Server::serverRcv() {

	char recvbuf[DEFAULT_BUFLEN];
	int iResult, iSendResult;
	int recvbuflen = DEFAULT_BUFLEN;

	for (int i = 0; i < this->_conns.size(); i++) {
		int iResult = recv(_conns[i]->getSocket(), recvbuf, recvbuflen, 0);
		if (iResult > 0) {
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(_conns[i]->getSocket(), recvbuf, iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed: %d\n", WSAGetLastError());
				closesocket(_conns[i]->getSocket());
				WSACleanup();
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0) {
			printf("TCP Connection with ID: %d closing...\n", _conns[i]->getID());
			_conns[i]->close();
			delete _conns[i];
			std::vector<Connection*>::iterator it = _conns.begin();
			it += i;
			_conns.erase(it);
			//std::iterator<Connection*>
		}
		else {
			int error = WSAGetLastError();
			if (error != WSAEWOULDBLOCK) {
				printf("recv failed: %d\n", error);
				closesocket(_conns[i]->getSocket());
				WSACleanup();
			}
		}
	}
}
