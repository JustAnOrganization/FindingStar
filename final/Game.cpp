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

Game::Game(int width, int height) : player(*this, M_PI/4, width / (float) height, 0.01, 70.0)
{
    screenWidth = width;
    screenHeight = height;

    objects.clear();
    //models
    objects.push_back(new Model(*this/*game*/, vec3(0, -200, 0)/*location*/, vec3(0, 0, 0)/*rotation*/, vec3(0.01, 0.01, 0.01)/*scale*/, "models/room.obj"/*model path*//*, teture path*/));

    objects.push_back(new Model(*this, vec3(500, 0, 5), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/desk.obj"));

    objects.push_back(new Model(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/bookshelf.obj"));

    Model* key = new Model(*this, vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/key.obj");
    objects.push_back(key);
    triggers.push_back(Trigger(*key/*model*/, vec3(0, 0, 0)/*position*/, 0.1/*radius*/, 0.5/*distance*/));

    //skybox
    objects.push_back(new Skybox(*this));

    collisions.clear();
    collisions.push_back(BoxCollision2D(vec2(0, 0),vec2(10, 10), true));
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

void Game::draw()
{
    for (auto* object: objects)
    {
        object->draw();
    }
}

bool Game::checkCollision(vec3 position)
{
    for (auto& collison: collisions)
    {
        if (!collison.check(position))
            return false;
    }
    return true;
}
