#version 430 core

in vec4 geomColor;
in vec2 geomTexPosition;
in vec2 geomCentre;
in vec2 geomBounds;

out vec4 fColor;

void main() {
	fColor = (1 - pow(2*length((geomCentre - gl_FragCoord.xy)/geomBounds), 2))*geomColor;
}
