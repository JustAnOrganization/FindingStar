#version 150 core

uniform samplerCube Texture;

in vec3 Position;

out vec4 Color;

void main()
{
    Color = texture(Texture, Position);
}