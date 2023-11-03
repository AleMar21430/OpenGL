#pragma once

#include <unordered_map>
#include <unordered_set>
#include <filesystem>
#include <windows.h>
#include <stdexcept>
#include <iostream>
#include <optional>
#include <direct.h>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <variant>
#include <cstdlib>
#include <cstring>
#include <numeric>
#include <cerrno>
#include <vector>
#include <chrono>
#include <thread>
#include <future>
#include <math.h>
#include <array>
#include <tuple>
#include <any>
#include <map>
#include <set>

#include "json.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;
using json = nlohmann::json;

#undef min
#undef max

#define PI          3.141592653589793
#define TWO_PI      6.283185307179586
#define INVERTED_PI 0.318309886183791
#define DEG_RAD     0.017453292519943
#define EULER       2.718281828459045

inline string get_file_contents(const char* filename) {
	ifstream in(filename, ios::binary);
	if (in) {
		string contents;
		in.seekg(0, ios::end);
		contents.resize(in.tellg());
		in.seekg(0, ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	else {
		cout << filename << "  NOT FOUND";
	}
}

inline vector<vec2> groupFloatsVec2(vector<float> floatVec) {
	vector<vec2> vectors;
	for (int i = 0; i < floatVec.size(); i)
		vectors.push_back(vec2(floatVec[i++], floatVec[i++]));
	return vectors;
}

inline vector<vec3> groupFloatsVec3(vector<float> floatVec) {
	vector<vec3> vectors;
	for (int i = 0; i < floatVec.size(); i)
		vectors.push_back(vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
	return vectors;
}

inline vector<vec4> groupFloatsVec4(vector<float> floatVec) {
	vector<vec4> vectors;
	for (int i = 0; i < floatVec.size(); i)
		vectors.push_back(vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
	return vectors;
}