#pragma once
#include "meshloader.hpp"

class FileLoader {
private:
	MeshLoader* _ml;
public:
	FileLoader();
	~FileLoader();

	Model* loadModel(const char* path, bool hasModelMX);
	MeshLoader* getML();
	//loadfile() ??? Probs want this shite.
};