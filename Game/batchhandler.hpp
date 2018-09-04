#pragma once
#include "batch.hpp"
#include "window.hpp"
#include <map>

class BatchHandler {
private:
	 std::map<std::string, Batch*> _batches;
	 int _nrOfBatches;
public:
	BatchHandler();
	~BatchHandler();

	std::string addBatch(Batch* batch, std::string name);
	Batch* getBatch(std::string batchName);
	void removeBatch(std::string batchName);

	void render(Window* window);
};