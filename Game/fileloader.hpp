#pragma once
#include "meshloader.hpp"

class FileLoader {
private:
	MeshLoader* _ml;
public:
	FileLoader();
	~FileLoader();

	Model* loadModel(const char* path, bool hasModelMX);
	//loadfile() ??? Probs want this shite.
};