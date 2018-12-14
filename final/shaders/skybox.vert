#version 150 core

uniform mat4 WVPMat;

in vec3 inPosition;

out vec3 Position;

void main()
{
	gl_Position = WVPMat * vec4(inPosition, 1.0f);
	Position = inPosition.xyz;
}