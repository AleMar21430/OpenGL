#include"Model.h"

Model::Model(const char* i_file) {
	string text = get_file_contents(i_file);
	JSON = json::parse(text);
	file = i_file;
	data = getData();
	f_traverseGLTF(0);
}

void Model::f_render(Shader& shader, Camera& camera) {
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Mesh::f_render(shader, camera, matrices[i]);
}

void Model::f_loadMesh(unsigned int indMesh) {
	unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
	unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
	unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
	unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

	vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
	vector<vec3> positions = groupFloatsVec3(posVec);
	vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
	vector<vec3> normals = groupFloatsVec3(normalVec);
	vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
	vector<vec2> texUVs = groupFloatsVec2(texVec);

	vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
	vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
	vector<Texture> textures = getTextures();

	meshes.push_back(Mesh(vertices, indices, textures));
}

void Model::f_traverseGLTF(unsigned int nextNode, mat4 matrix) {
	json node = JSON["nodes"][nextNode];
	vec3 translation = vec3(0.0f, 0.0f, 0.0f);

	if (node.find("translation") != node.end()) {
		float transValues[3];
		for (unsigned int i = 0; i < node["translation"].size(); i++)
			transValues[i] = (node["translation"][i]);
		translation = make_vec3(transValues);
	}
	quat rotation = quat(1.0f, 0.0f, 0.0f, 0.0f);

	if (node.find("rotation") != node.end()) {
		float rotValues[4] = {
			node["rotation"][3],
			node["rotation"][0],
			node["rotation"][1],
			node["rotation"][2]
		};
		rotation = make_quat(rotValues);
	}
	vec3 scale = vec3(1.0f, 1.0f, 1.0f);

	if (node.find("scale") != node.end()) {
		float scaleValues[3];
		for (unsigned int i = 0; i < node["scale"].size(); i++)
			scaleValues[i] = (node["scale"][i]);
		scale = make_vec3(scaleValues);
	}
	mat4 matNode = mat4(1.0f);

	if (node.find("matrix") != node.end()) {
		float matValues[16];
		for (unsigned int i = 0; i < node["matrix"].size(); i++)
			matValues[i] = (node["matrix"][i]);
		matNode = make_mat4(matValues);
	}
	mat4 trans = mat4(1.0f);
	mat4 rot = mat4(1.0f);
	mat4 sca = mat4(1.0f);

	trans = translate(trans, translation);
	rot = mat4_cast(rotation);
	sca = glm::scale(sca, scale);

	mat4 matNextNode = matrix * matNode * trans * rot * sca;

	if (node.find("mesh") != node.end()) {
		positions.push_back(translation);
		rotations.push_back(rotation);
		scales.push_back(scale);
		matrices.push_back(matNextNode);

		f_loadMesh(node["mesh"]);
	}

	if (node.find("children") != node.end()) {
		for (unsigned int i = 0; i < node["children"].size(); i++)
			f_traverseGLTF(node["children"][i], matNextNode);
	}
}

vector<unsigned char> Model::getData() {
	string bytesText;
	string uri = JSON["buffers"][0]["uri"];

	string fileStr = string(file);
	string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);
	bytesText = get_file_contents((fileDirectory + uri).c_str());

	vector<unsigned char> data(bytesText.begin(), bytesText.end());
	return data;
}

vector<float> Model::getFloats(json accessor) {
	vector<float> floatVec;

	unsigned int buffViewInd = accessor.value("bufferView", 1);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	string type = accessor["type"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];

	unsigned int numPerVert;
	if (type == "SCALAR") numPerVert = 1;
	else if (type == "VEC2") numPerVert = 2;
	else if (type == "VEC3") numPerVert = 3;
	else if (type == "VEC4") numPerVert = 4;
	else throw invalid_argument("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)");

	unsigned int beginningOfData = byteOffset + accByteOffset;
	unsigned int lengthOfData = count * 4 * numPerVert;
	for (unsigned int i = beginningOfData; i < beginningOfData + lengthOfData; i) {
		unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
		float value;
		memcpy(&value, bytes, sizeof(float));
		floatVec.push_back(value);
	}

	return floatVec;
}

vector<GLuint> Model::getIndices(json accessor) {
	vector<GLuint> indices;

	unsigned int buffViewInd = accessor.value("bufferView", 0);
	unsigned int count = accessor["count"];
	unsigned int accByteOffset = accessor.value("byteOffset", 0);
	unsigned int componentType = accessor["componentType"];

	json bufferView = JSON["bufferViews"][buffViewInd];
	unsigned int byteOffset = bufferView["byteOffset"];
	unsigned int beginningOfData = byteOffset + accByteOffset;
	if (componentType == 5125) {
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i) {
			unsigned char bytes[] = { data[i++], data[i++], data[i++], data[i++] };
			unsigned int value;
			memcpy(&value, bytes, sizeof(unsigned int));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5123) {
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			unsigned short value;
			memcpy(&value, bytes, sizeof(unsigned short));
			indices.push_back((GLuint)value);
		}
	}
	else if (componentType == 5122) {
		for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
			unsigned char bytes[] = { data[i++], data[i++] };
			short value;
			memcpy(&value, bytes, sizeof(short));
			indices.push_back((GLuint)value);
		}
	}
	return indices;
}

vector<Texture> Model::getTextures() {
	vector<Texture> textures;
	string fileStr = string(file);
	string fileDirectory = fileStr.substr(0, fileStr.find_last_of('/') + 1);

	for (unsigned int i = 0; i < JSON["images"].size(); i++) {
		string texPath = JSON["images"][i]["uri"];
		bool skip = false;
		for (unsigned int j = 0; j < texture_names.size(); j++) {
			if (texture_names[j] == texPath) {
				textures.push_back(textures[j]);
				skip = true;
				break;
			}
		}

		if (!skip) {
			if (texPath.find("baseColor") != string::npos || texPath.find("diffuse") != string::npos) {
				Texture diffuse = Texture((fileDirectory + texPath).c_str(), "diffuse", textures.size());
				textures.push_back(diffuse);
				textures.push_back(diffuse);
				texture_names.push_back(texPath);
			}
			else if (texPath.find("metallicRoughness") != string::npos || texPath.find("specular") != string::npos) {
				Texture specular = Texture((fileDirectory + texPath).c_str(), "specular", textures.size());
				textures.push_back(specular);
				textures.push_back(specular);
				texture_names.push_back(texPath);
			}
		}
	}
	return textures;
}

vector<Vertex> Model::assembleVertices(vector<vec3> positions, vector<vec3> normals, vector<vec2> texUVs) {
	vector<Vertex> vertices;
	for (int i = 0; i < positions.size(); i++) {
		vertices.push_back (
			Vertex {
				positions[i],
				normals[i],
				vec3(1.0f, 1.0f, 1.0f),
				texUVs[i]
			}
		);
	}
	return vertices;
}