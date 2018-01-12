#version 130
//The fragment shader handles shading of pixels within each polygon.
in vec2 fragmentPos;
in vec4 fragmentColor;
out vec4 color;
void main() {
	color = fragmentColor;
}