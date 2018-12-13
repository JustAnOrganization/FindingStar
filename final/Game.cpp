//
// Created by Jia on 2018/11/11.
//

#include "Game.h"
#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Model.h"

using namespace glm;

Game::Game(int width, int height) : player(*this, M_PI/4, width / (float) height, 1.0, 15.0)
{
    screenWidth = width;
    screenHeight = height;

    objects.clear();
<<<<<<< HEAD

    objects.push_back(new Model(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/room.obj"));
    //objects.push_back(new Model(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01)));
    objects.push_back(new Model(*this, vec3(0, 0, 5), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01)));
=======
    objects.push_back(new Table(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0)));
    objects.push_back(new Table(*this, vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 0, 0)));
>>>>>>> parent of b6d26a5... Revert "Merge branch 'master' of https://github.com/JustAnOrganization/FindingStar"
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
