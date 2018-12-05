//
// Created by shrimp on 2018/12/3.
//

#ifndef FINALPROJECT_TABLE_H
#define FINALPROJECT_TABLE_H

#include "Utils.h"
#include "Game.h"
#include "Basic.h"

struct VertexPositionColorUv
{
public:
    VertexPositionColorUv() {}
    VertexPositionColorUv(const vec3& position, const vec3& color, const vec2& uv)
    : position(position), color(color), uv(uv) { }

    vec3 position;
    vec3 color;
    vec2 uv;
};

class VertexPositionUvNormal
{
public:
    VertexPositionUvNormal() {}
    VertexPositionUvNormal(const glm::vec3& position, const glm::vec2& uv, const glm::vec3& normal)
    : position(position), uv(uv), normal(normal) { }

    vec3 position;
    vec2 uv;
    vec3 normal;
};

class Table: public RenderObject
{
public:
    Table(Game& game, vec3 location, vec3 rotation, vec3 scale): RenderObject(game, location, rotation, scale) { }

    virtual void initialize() override;
    virtual void update(float deltaTime) override;
    virtual void destroy() override;

private:
    GLuint shaderProgram;
    GLuint vao, vbo;
    GLuint tex;
    int vertexCount;

    UnifromVariable WVPMat;
    UnifromVariable WorldMat;
    UnifromVariable LightDir;
    UnifromVariable AmbientColor;
    UnifromVariable LightColor;
    UnifromVariable CamPosition;
    UnifromVariable SpecColor;
};


#endif //FINALPROJECT_TABLE_H
