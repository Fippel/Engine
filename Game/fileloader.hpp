#pragma once
#include "meshloader.hpp"

class FileLoader {
private:
	MeshLoader* _ml;

	static FileLoader* _instance;
	FileLoader();

public:
	~FileLoader();

	static FileLoader* getInstance();
	Model* loadModel(const char* path, bool hasModelMX);
	MeshLoader* getML();
	//loadfile() ??? Probs want this shite.
};