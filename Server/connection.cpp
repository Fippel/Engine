#include "connection.hpp"

Connection::Connection(SOCKET sock, CONNID id) {
	this->sock = sock; this->id = id;
}
void Connection::close() {
	//YET TO IMPLEMENT
}
SOCKET Connection::getSocket() {
	return this->sock;
}
CONNID Connection::getID() {
	return this->id;
}