//
// Created by shrimp on 2018/12/13.
//

#ifndef FINALPROJECT_SKYBOX_H
#define FINALPROJECT_SKYBOX_H


#include "Game.h"
#include "Utils.h"

class Skybox: public RenderObject
{
public:
    Skybox(Game& game)
    : RenderObject(game, vec3(0, 0, 0), vec3(0, 0, 0), vec3(20, 20, 20)) { }

    virtual void initialize() override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void destroy() override;

private:
    void loadCubemap();

    GLuint shaderProgram;
    GLuint vao, vbo;
    GLuint tex;
    int vertexCount;

    UnifromVariable WVPMat;
};


#endif //FINALPROJECT_SKYBOX_H
