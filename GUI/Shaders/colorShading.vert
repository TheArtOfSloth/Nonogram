#version 130
//The vertex shader handles the shading for each vertex of the polygon.
in vec2 vertexPos;

void main() {
	gl_Position.xy = vertexPos;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
}