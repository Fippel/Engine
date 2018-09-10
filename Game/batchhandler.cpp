#include "batchhandler.hpp"
#include "batch.hpp"

BatchHandler::BatchHandler() {
	_nrOfBatches = 0;
}

BatchHandler::~BatchHandler() {
	std::vector<std::string> batchnames;
	for (std::map<std::string, Batch*>::iterator it = _batches.begin(); it!=_batches.end(); ++it) {
		batchnames.push_back(it->first);
	}
	for(int i = 0; i < batchnames.size(); i++)
		removeBatch(batchnames[i]);
}

std::string BatchHandler::addBatch(Batch* batch, std::string name) {
	_batches[name] = batch;
	return name;
}

Batch* BatchHandler::getBatch(std::string batchName) {
	return _batches[batchName];
}


//IMPLEMENT MODEL REMOVAL --------------------------------------------------------------------------------------------------
void BatchHandler::removeBatch(std::string batchName) {
	_batches.erase(batchName);
}

void BatchHandler::render(Window* window) {
	for (std::map<std::string, Batch*>::iterator it = _batches.begin(); it!=_batches.end(); ++it) {
		((Batch*)(it->second))->render(window);
	}
}
