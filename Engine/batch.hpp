#pragma once

#include "shaderprogram.hpp"
#include "mesh.hpp"
#include "glframebuffer.hpp"
#include "window.hpp"
#include <vector>

struct GLFrameIndex {
	GLFrameBuffer* buffer;
	std::vector<bool> isDepth;
	std::vector<int> texturePos;
	std::vector<int> bindPos;
};

class Batch {
private:
	int _currID = 0;
	ShaderProgram* _pipeline;
	std::vector<Model*> _models;
	GLFrameBuffer* _outputFBO;
	unsigned int _nrOfTextures;
	bool _FBOBound;
	int _textureIndices[4];

	

	std::vector<GLFrameIndex> _inputFBO;
	

	struct ShaderInput {
		int id;
		int type;
		virtual void bind(ShaderProgram* sp) {}
	};

	std::vector<ShaderInput*> _input;

	struct ShaderInputint32 : ShaderInput { int32_t* value; ShaderInputint32(int id, int32_t* v) { this->id = id; value = v; type = 0; }  virtual void bind(ShaderProgram* sp) { sp->setValue(id, int32_t(*value)); } };
	struct ShaderInputuint32 : ShaderInput {uint32_t* value; ShaderInputuint32(int id, uint32_t* v) { this->id = id; value = v;type = 1; }virtual void bind(ShaderProgram* sp) {sp->setValue(id, *value);}};
	struct ShaderInputfloat : ShaderInput { float* value; ShaderInputfloat(int id, float* v) { this->id = id; value = v; type = 2; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputivec2 : ShaderInput { glm::ivec2* value; ShaderInputivec2(int id, glm::ivec2* v) { this->id = id; value = v; type = 3; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputivec3 : ShaderInput { glm::ivec3* value; ShaderInputivec3(int id, glm::ivec3* v) { this->id = id; value = v; type = 4; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputivec4 : ShaderInput { glm::ivec4* value; ShaderInputivec4(int id, glm::ivec4* v) { this->id = id; value = v; type = 5; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputvec2 : ShaderInput { glm::vec2* value; ShaderInputvec2(int id, glm::vec2* v) { this->id = id; value = v; type = 6; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputvec3 : ShaderInput { glm::vec3* value; ShaderInputvec3(int id, glm::vec3* v) { this->id = id; value = v; type = 7; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputvec4 : ShaderInput { glm::vec4* value; ShaderInputvec4(int id, glm::vec4* v) { this->id = id; value = v; type = 8; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputmat2 : ShaderInput { glm::mat2* value; ShaderInputmat2(int id, glm::mat2* v) { this->id = id; value = v; type = 9; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputmat3 : ShaderInput { glm::mat3* value; ShaderInputmat3(int id, glm::mat3* v) { this->id = id; value = v; type = 10; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, *value); } };
	struct ShaderInputmat4 : ShaderInput { glm::mat4* value; ShaderInputmat4(int id, glm::mat4* v) { this->id = id; value = v; type = 11; }virtual void bind(ShaderProgram* sp) { sp->setValue(id, glm::mat4(*value)); } };


	void _bind();
public:
	Batch();
	~Batch();
	bool clearFlag = true;
	void createPipeline(std::string vs, std::string fs, std::string gs = "", std::string cs = "");
	void addTexture(Texture::TextureFormat type, int width, int height);
	void addDepthTexture(int width, int height);
	void FBOFinalize();
	void addFBOInput(GLFrameIndex frameIndex);
	void render(Window* window);
	void setTextureIndices(int diffuse, int specular, int ambient, int normalmap);
	void registerModel(Model* m);
	void removeModel(Model* m);
	GLFrameBuffer* getFBO();
	void addInput(int id, int32_t* value) { _input.push_back(new ShaderInputint32(id, value)); }
	void addInput(int id, uint32_t* value) { _input.push_back(new ShaderInputuint32(id, value)); }
	void addInput(int id, float* value) { _input.push_back(new ShaderInputfloat(id, value)); }
	void addInput(int id, glm::ivec2* value) { _input.push_back(new ShaderInputivec2(id, value)); }
	void addInput(int id, glm::ivec3* value) { _input.push_back(new ShaderInputivec3(id, value)); }
	void addInput(int id, glm::ivec4* value) { _input.push_back(new ShaderInputivec4(id, value)); }
	void addInput(int id, glm::vec2* value) { _input.push_back(new ShaderInputvec2(id, value)); }
	void addInput(int id, glm::vec3* value) { _input.push_back(new ShaderInputvec3(id, value)); }
	void addInput(int id, glm::vec4* value) { _input.push_back(new ShaderInputvec4(id, value)); }
	void addInput(int id, glm::mat2* value) { _input.push_back(new ShaderInputmat2(id, value)); }
	void addInput(int id, glm::mat3* value) { _input.push_back(new ShaderInputmat3(id, value)); }
	void addInput(int id, glm::mat4* value) { _input.push_back(new ShaderInputmat4(id, value)); }

	
};


