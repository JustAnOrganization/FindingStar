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

	/* Room ( 9 objects) */
    //objects.push_back(new Model(*this/*game*/, vec3(0, -200, 0)/*location*/, vec3(0, 0, 0)/*rotation*/, vec3(0.01, 0.01, 0.01)/*scale*/, "models/room.obj"/*model path*/,"models/wall_paper_3.bmp" /*teture path*/));
	objects.push_back(new Model(*this/*game*/, vec3(0, -200, 0)/*location*/, vec3(0, 0, 0)/*rotation*/, vec3(0.01, 0.01, 0.01)/*scale*/, 
		"models/Room/Cube.obj"/*model path*/, "models/wall_paper_3.bmp" /*teture path*/));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Wall_1.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Wall_2.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Wall_3.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Wall_4.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Floor.obj", "models/Wood-Textures-bmp.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Pic_1.obj", "models/star_map_2.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Pic_2.obj", "models/star_map_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Wall_1.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -200, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/Room/Window.obj", "models//Wood-Textures-bmp.bmp"));
	
	/* Desk (one piece) */
    objects.push_back(new Model(*this, vec3(0, -120, 450), vec3(0, M_PI/2, 0), vec3(0.01, 0.01, 0.01), "models/desk.obj", "models/Wood-Textures-bmp.bmp"));

	/* Desk Drawer */
	objects.push_back(new Model(*this, vec3(0, -120, 450), vec3(0, M_PI / 2, 0), vec3(0.01, 0.01, 0.01), "models/drawer.obj", "models/Wood-Textures-bmp.bmp"));

	/* Shelf */
    objects.push_back(new Model(*this, vec3(-450, 0, 0), vec3(0, M_PI/2, 0), vec3(0.01, 0.01, 0.01), "models/BookShelf/Shelf_Body.obj", "models/Wood-Textures-bmp.bmp"));
	objects.push_back(new Model(*this, vec3(-450, 0, 0), vec3(0, M_PI / 2, 0), vec3(0.01, 0.01, 0.01), "models/BookShelf/Stack_Top.obj", "models/orange.bmp"));
	objects.push_back(new Model(*this, vec3(-450, 0, 0), vec3(0, M_PI / 2, 0), vec3(0.01, 0.01, 0.01), "models/BookShelf/Stack_Middle.obj", "models/green.bmp"));
	objects.push_back(new Model(*this, vec3(-450, 0, 0), vec3(0, M_PI / 2, 0), vec3(0.01, 0.01, 0.01), "models/BookShelf/Stack_Bottom.obj", "models/red.bmp"));
	objects.push_back(new Model(*this, vec3(-450, 0, 0), vec3(0, M_PI / 2, 0), vec3(0.01, 0.01, 0.01), "models/BookShelf/Lock.obj", "models/bronze.bmp"));

	/* Keys */
    Model* key = new Model(*this, vec3(400, -30, 0), vec3(0, 0, 0), vec3(0.01, 0.01, 0.01), "models/key.obj", "models/bronze.bmp");
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
