#version 460 core

out vec4 fragColor;

in vec3 vertPos;
in vec3 vertNormal;
in vec3 vertColor;
in vec2 vertTexCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec3 camPos;

void main() {
	fragColor = texture(diffuse0, vertTexCoord);
}