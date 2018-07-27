#version 460
out vec4 newColor;
in vec3 vertColor; //the compiler knows this is coming from the vertex shader and searches for this string in the vertex shader source code

void main(){
	newColor = vec4(vertColor, 1.0);
}