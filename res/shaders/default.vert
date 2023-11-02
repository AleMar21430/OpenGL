#version 460 core

layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iNormal;
layout (location = 2) in vec3 iColor;
layout (location = 3) in vec2 iTex;

out vec3 vertPos;
out vec3 vertNormal;
out vec3 vertColor;
out vec2 vertTexCoord;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main() {
	vertPos = vec3(model * translation * rotation * scale * vec4(iPos, 1.0f));
	vertNormal = iNormal;
	vertColor = iColor;
	vertTexCoord = mat2(0.0, -1.0, 1.0, 0.0) * iTex;
	gl_Position = camMatrix * vec4(vertPos, 1.0);
}