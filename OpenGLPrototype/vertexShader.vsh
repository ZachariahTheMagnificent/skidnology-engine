#version 460
in layout(location = 0) vec3 position; //location=0 selects the arbitrary attribute slot that we defined earlier
in layout(location = 1) vec3 vertexColor;
out vec3 vertColor;

uniform mat4 transformationMatrix;

void main() {
	vec4 v = vec4(position, 1.0);
	gl_Position = transformationMatrix * v;
	vertColor = vertexColor;
}