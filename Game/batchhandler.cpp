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

	std::vector<Node*> vec;
	for (int i = 0; i < 20; i++) {
		Node* next = _nodes[i];

		while (next != nullptr) {
			vec.push_back(next);
			next = next->next;
		}
	}

	for (int i = 0; i < vec.size(); i++)
		delete vec[i];

}

std::string BatchHandler::addBatch(Batch* batch, std::string name, int index) {
	_batches[name] = batch;

	//Node* next = _nodes[index];
	//while (next != nullptr)
	//	next = next->next;
	//
	//next = new Node();
	//next->batch = batch;

	Node** next = &_nodes[index];
	while (*next != nullptr)
		next = &((*next)->next);
	
	*next = new Node();
	(*next)->batch = batch;

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
	Node* next;
	for(int i = 0; i < 20; i++) {
		next = _nodes[i];
		while (next != nullptr) {
			next->batch->render(window);
			next = next->next;
		}
	}


	//for (std::map<std::string, Batch*>::iterator it = _batches.begin(); it!=_batches.end(); ++it) {
	//	((Batch*)(it->second))->render(window);
	//}
}
