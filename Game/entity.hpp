#pragma once
#include <string>
#include "batchhandler.hpp"

struct EntityHandler;

class Entity {
private:
	std::string _name;
	unsigned int _index;
	EntityHandler* _eh;
	BatchHandler* _bh;
	//--------------------

	//std::vector<Component> comps;
public:
	Entity(std::string name);
	~Entity();
	void setup(unsigned int index, EntityHandler* eh, BatchHandler* bh);
	std::string getName();
	EntityHandler* getEH();
	BatchHandler* getBH();



};