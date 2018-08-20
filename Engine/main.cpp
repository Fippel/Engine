#include <stdio.h>
#include "engine.hpp"

int main(int argcc, char* argv[]) {
	printf("Booting up engine!\n");

	return Engine::getInstance()->run();
}