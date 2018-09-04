#include "batchhandler.hpp"

BatchHandler::BatchHandler() {
	_nrOfBatches = 0;
}

BatchHandler::~BatchHandler() {
	for (std::map<std::string, Batch*>::iterator it = _batches.begin(); it!=_batches.end(); ++it) {
		this->removeBatch(it->first);
	}
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
		it->second->render(window);
	}
}
