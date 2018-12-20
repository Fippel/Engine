#pragma comment(lib, "Ws2_32.lib")
#include "client.hpp"

#define DEFAULT_PORT "4586"

Client::Client() {
	
}

Client::~Client() {
}

void Client::initialize(std::string ip, int port) {
	//struct addrinfo* _result = NULL, *ptr = NULL, hints;

	WSADATA wsadata;
	int iResult;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		//return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;


	LPCSTR pcstrip = PCSTR(ip.c_str());
	iResult = getaddrinfo("192.168.0.52", "4586", &hints, &_result); // argv??? kan va skumt
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		//return;
	}

	ptr = _result;

	_tcpSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

	if (_tcpSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(_result);
		WSACleanup();
		//return;
	}

	iResult = connect(_tcpSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(_tcpSocket);
		_tcpSocket = INVALID_SOCKET;
		printf("%ld", WSAGetLastError());
	}

	freeaddrinfo(_result);

	if (_tcpSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		//return 1;
	}
}
