#include "meshloader.hpp"
#include "textureloader.hpp"
#include <vector>

MeshLoader::MeshLoader() {

}

MeshLoader::~MeshLoader() {

}

Mesh * MeshLoader::processMesh(aiMesh * mesh, const aiScene * scene) {
	std::vector<Mesh::Vertex> vertices;
	std::vector<GLuint> indices;
	std::map<std::string, Texture> textures;

	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Mesh::Vertex vertex;
		glm::vec3 tempV;

		tempV.x = mesh->mVertices[i].x;
		tempV.y = mesh->mVertices[i].y;
		tempV.z = mesh->mVertices[i].z;
		vertex.pos = tempV;

		tempV.x = mesh->mNormals[i].x;
		tempV.y = mesh->mNormals[i].y;
		tempV.z = mesh->mNormals[i].z;
		vertex.normal = tempV;

		//Color?
		//aiMaterial* mtl = scene->mMaterials[mesh->mMaterialIndex];
		//aiColor4D color(0.f, 0.f, 0.f, 0.f);
		//mtl->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		//vertex.color = glm::vec4(color.r, color.g, color.b, color.a);
		//
		//int texIndex = 0;
		//aiString path;
		//mtl->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
		//if (mtl->GetTextureCount(aiTextureType_DIFFUSE) > 0)
		//	printf("\n\n %d\n\n", mtl->GetTextureCount(aiTextureType_DIFFUSE));

		//aiMaterial* mtl = scene->mMaterials[mesh->mMaterialIndex];
		//glm::vec4 c;
		//aiColor4D diffuse;
		//if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		//	c = glm::vec4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
		//vertex.color = c;

		if (mesh->mTextureCoords[0]) {
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.uv = vec;
		}
		else
			vertex.uv = glm::vec2(0.f);

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* mtl = scene->mMaterials[mesh->mMaterialIndex];

		//std::map<std::string, Texture> diffuseMaps = loadMaterialTextures(mtl, aiTextureType_DIFFUSE, "diffuseTexture");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		textures = loadMaterialTextures(mtl, aiTextureType_DIFFUSE, "diffuseTexture");

		//std::vector<Texture> specularMaps = loadMaterialTextures(mtl, aiTextureType_SPECULAR, "specularTexture");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	//return new Mesh(vertices, indices, true);
	return new Mesh(vertices, indices, textures, true);
}

void MeshLoader::processNode(aiNode* node, const aiScene* scene, Model& models) {
	//printf("NumMeshes in asScene: %u\n", scene->mNumMeshes);
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		models.meshes.push_back(processMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; i++)
		processNode(node->mChildren[i], scene, models);
}

Model MeshLoader::loadMesh(const char* path, bool hasModelMX) {
	const aiScene* scene = aiImportFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	
	if( !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode ) {
		printf("ERROR::ASSIMP::", aiGetErrorString());
		printf("\n");
	}
	Model model;
	processNode(scene->mRootNode, scene, model);

	return model;
}

std::shared_ptr<Texture> MeshLoader::loadTexture(const std::string& path) {
	return std::make_shared<Texture>(path);
}

//GLint MeshLoader::textureFromFile(const char* path, std::string directory) {
//	std::string filename = std::string(path);
//	filename = directory + '/' + filename;
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height;
//
//	//_testTexture = _textureLoader->loadTexture("assets/textures/test.jpg");
//	Texture = TextureLoader::loadTexture("assets/textures/test.jpg");
//	unsigned char* image = SOIL
//}

std::map<std::string, Texture> MeshLoader::loadMaterialTextures(aiMaterial* mtl, aiTextureType type, std::string typeName) {
	std::map<std::string, Texture> textures;
	for (GLuint i = 0; i < mtl->GetTextureCount(type); i++) {
		aiString str;
		mtl->GetTexture(type, i, &str);
		
		std::string temp;
		temp = str.C_Str();
		temp = temp.substr(temp.find_last_of("\\") + 1, temp.size());
		temp = "assets/textures/" + temp;
		

		bool skip = false;
		
		//for (unsigned int j = 0; j < model.loadedTextures.size(); j++) {
		//	if (model.loadedTextures[j].path == str) {
		//		textures.push_back(model.loadedTextures[j]);
		//		skip = true;
		//	}
		//}
		if (!skip) {
			//Mesh::Tex tex;
			//tex.id = textureFromFile(str.C_Str(), model.directory);
			//std::string tmp = "asd";// str.C_Str();
			
			if(type == aiTextureType_DIFFUSE)
				textures[typeName] = (*loadTexture(temp).get()); // KOLLA DENNANS SKITEN!!
			//tex.id = loadTexture("asd");
			//tex.type = typeName;
			//tex.path = str;
			//textures.push_back(tex);

			//model.loadedTextures.push_back(tex);
		}
	}
	return textures;
	
}

Mesh* MeshLoader::getQuad() {
	std::vector<Mesh::Vertex> vertices{
		Mesh::Vertex{ { -1, 1, 0 },{ 0, 0, -1 },{ 1, 0, 1 },{ 0, 1 } },
		Mesh::Vertex{ { 1, 1, 0 },{ 0, 0, -1 },{ 1, 0, 1 },{ 1, 1 } },
		Mesh::Vertex{ { 1, -1, 0 },{ 0, 0, -1 },{ 1, 0, 1 },{ 1, 0 } },
		Mesh::Vertex{ { -1, -1, 0 },{ 0, 0, -1 },{ 1, 0, 1 },{ 0, 0 } }
	};
	std::vector<GLuint> indices{ 0, 2, 1, 2, 0, 3 };
	return new Mesh(vertices, indices, false);
}