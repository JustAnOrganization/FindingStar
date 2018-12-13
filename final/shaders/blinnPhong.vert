#version 150 core

uniform mat4 WVPMat;
uniform mat4 WorldMat;
uniform vec3 LightDir;

in vec3 inPosition;
in vec2 inUV;
in vec3 inNormal;

out vec2 UV;
out vec3 Normal;
out vec3 LightDirOp;
out vec3 Position;

void main()
{
	gl_Position = WVPMat * vec4(inPosition, 1.0f);
	UV = inUV;
	Normal = (WorldMat * vec4(inNormal, 0.0f)).xyz;
	LightDirOp = -normalize(LightDir);
	Position = (WorldMat * vec4(inPosition, 1.0f)).xyz;
}