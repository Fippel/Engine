#include "fileloader.hpp"

FileLoader::FileLoader() {
	this->_ml = new MeshLoader();
}

FileLoader::~FileLoader() {
	delete this->_ml;
}

Model * FileLoader::loadModel(const char* path, bool hasModelMX) {
	return _ml->loadMesh(path, hasModelMX);
}
