#include "server.hpp"
int main() {
	Server s;
	s.initialize(0);
	while (true) {
		s.serverlisten();
		s.serverRcv();
		//printf("f");
	}
	return 0;
}