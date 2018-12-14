#pragma once
#include <map>
#include <string>
#include "batch.hpp"
#include "window.hpp"



class BatchHandler {
private:

	static BatchHandler* _instance; // Singleton mode
	BatchHandler();

	 std::map<std::string, Batch*> _batches;
	 int _nrOfBatches;

	 struct Node {
		 Node() { batch = nullptr; next = nullptr; }
		 Batch* batch;
		 Node* next;
	 };

	 Node* _nodes[20];

public:
	//BatchHandler();
	static BatchHandler* getInstance();
	~BatchHandler();

	std::string addBatch(Batch* batch, std::string name, int index);
	Batch* getBatch(std::string batchName);
	void removeBatch(std::string batchName);

	void render(Window* window);
};