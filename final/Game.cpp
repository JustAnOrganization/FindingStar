//
// Created by Jia on 2018/11/11.
//

#include "Game.h"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Model.h"
#include "Utils.h"
#include "Skybox.h"

using namespace glm;

Game::Game(int width, int height) : player(*this, M_PI/4, width / (float) height, 0.01, 50.0)
{
    screenWidth = width;
    screenHeight = height;

    objects.clear();
    objects.push_back(new Model(*this, vec3(0, -2, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/room.obj"));
    objects.push_back(new Model(*this, vec3(0, -2, 5), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01)));
    objects.push_back(new Model(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/bookshelf.obj"));
    objects.push_back(new Skybox(*this));
}

Game::~Game()
{
    for (auto* object: objects)
    {
        if (object)
        {
            delete object;
        }
    }
}

void Game::initialize()
{
    for (auto* object: objects)
    {
        object->initialize();
    }

    glEnable(GL_DEPTH_TEST);
}

void Game::update(float deltaTime)
{
    player.update(deltaTime);

    for (auto* object: objects)
    {
        object->update(deltaTime);
    }
}
