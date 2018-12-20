#include "fileloader.hpp"

FileLoader* FileLoader::_instance = 0;

FileLoader::FileLoader() {
	this->_ml = new MeshLoader();
}

FileLoader::~FileLoader() {
	delete this->_ml;
}

FileLoader* FileLoader::getInstance() {
	if (!_instance)
		_instance = new FileLoader();
	return _instance;
}

Model* FileLoader::loadModel(const char* path, bool hasModelMX) {
	return _ml->loadMesh(path, hasModelMX);
}

MeshLoader* FileLoader::getML() {
	return _ml;
}