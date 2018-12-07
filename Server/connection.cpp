#include "connection.hpp"

Connection::Connection(SOCKET sock, sockaddr addr, CONNID id) {
	this->sock = sock; this->id = id;
	this->addr = addr;
}
void Connection::close() {
	//YET TO IMPLEMENT
}
SOCKET* Connection::getSocket() {
	return &this->sock;
}
CONNID Connection::getID() {
	return this->id;
}

sockaddr* Connection::getAddr() {
	return &addr;
}