#include "batch.hpp"

void Batch::_bind() {
	_pipeline->useProgram();
	for (int i = 0; i < _input.size(); i++) {
		if (_input[i]->type == 0)
			((ShaderInputint32*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 1)
			((ShaderInputuint32*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 2)
			((ShaderInputfloat*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 3)
			((ShaderInputivec2*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 4)
			((ShaderInputivec3*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 5)
			((ShaderInputivec4*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 6)
			((ShaderInputvec2*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 7)
			((ShaderInputvec3*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 8)
			((ShaderInputvec4*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 9)
			((ShaderInputmat2*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 10)
			((ShaderInputmat3*)(_input[i]))->bind(_pipeline);
		else if (_input[i]->type == 11)
			((ShaderInputmat4*)(_input[i]))->bind(_pipeline);
	}
	//
	//for (int i = 0; i < _nrOfTextures - 1; i++) 
	//	(*_FBO)[i]->bind(i);
	
	_FBO->bind();
}

Batch::Batch() {
	_pipeline = nullptr;
	_FBO = new GLFrameBuffer();
	_FBOBound = false;
	_nrOfTextures = 0;
	_textureIndices[0] = 0;
	_textureIndices[1] = 0;
	_textureIndices[2] = 0;
	_textureIndices[3] = 0;
}

Batch::~Batch() {
	if (_pipeline)
		delete _pipeline;

	delete _FBO;
}

void Batch::createPipeline(std::string vs, std::string fs, std::string gs, std::string cs) {
	if (_pipeline)
		delete _pipeline;

	_pipeline = new ShaderProgram();
	
	_pipeline->attachShader(ShaderProgram::ShaderType::VertexShader, vs);
	_pipeline->attachShader(ShaderProgram::ShaderType::FragmentShader, fs);

	if(gs != "")
		_pipeline->attachShader(ShaderProgram::ShaderType::GeometryShader, gs);
	if(cs != "")
		_pipeline->attachShader(ShaderProgram::ShaderType::ComputeShader, cs);

	_pipeline->finalize();
}

void Batch::addTexture(Texture::TextureFormat type, int width, int height) {
	if (!_FBOBound) {
		_FBOBound = true;
		_FBO->bind();
	}
	
	_FBO->addTexture(_nrOfTextures++, type, width, height);
}

void Batch::addDepthTexture(int width, int height) {
	if (!_FBOBound) {
		_FBOBound = true;
		_FBO->bind();
	}

	_FBO->addDepth(_nrOfTextures++, width, height);
}

void Batch::FBOFinalize() {
	_FBO->finalize();
	_FBOBound = false;
}

void Batch::render(Window* window) {
	_bind();
	glViewport(0, 0, window->getWidth(), window->getHeight());
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < _input.size(); i++) {
		if(_input[i]->type == 0)
			printf("id: %d, value: %d\n", _input[i]->id, *((ShaderInputint32*)(_input[i]))->value);
	}
	
	for (int i = 0; i < _models.size(); i++) {
		_pipeline->setValue(0, _models[i]->model);
		for (int j = 0; j < _models[i]->meshes.size(); j++) {
			if (_models[i]->meshes[j]->getTextures().size() > 0) {
				Texture tex = _models[i]->meshes[j]->getTextures().at("diffuseTexture");
				tex.bind(_textureIndices[0]); 
			}

			glBindVertexArray(_models[i]->meshes[j]->getVAO());
			glDrawElements(GL_TRIANGLES, _models[i]->meshes[j]->getIndices().size(), GL_UNSIGNED_INT, nullptr);
			glBindVertexArray(0);
		}
	}
}

void Batch::setTextureIndices(int diffuse, int specular, int ambient, int normalmap) {
	_textureIndices[0] = diffuse;
	_textureIndices[1] = specular;
	_textureIndices[2] = ambient;
	_textureIndices[3] = normalmap;
}

void Batch::registerModel(Model* m) {
	_models.push_back(m);
}

GLFrameBuffer* Batch::getFBO() {
	return _FBO;
}
