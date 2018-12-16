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
#include "Animation.h"

using namespace glm;

Game::Game(int width, int height) : player(*this, M_PI/4, width / (float) height, 0.01, 70.0)
{
    screenWidth = width;
    screenHeight = height;

    const vec3 scale(0.01, 0.01, 0.01);

    objects.clear();
    //models

	/* Room ( 9 objects) */
    //objects.push_back(new Model(*this/*game*/, vec3(0, -2, 0)/*location*/, zeroVec3/*rotation*/, scale/*scale*/, "models/room.obj"/*model path*/,"models/wall_paper_3.bmp" /*teture path*/));
	objects.push_back(new Model(*this/*game*/, vec3(0, -2, 0)/*location*/, zeroVec3/*rotation*/, scale/*scale*/, 
		"models/Room/Cube.obj"/*model path*/, "models/wall_paper_3.bmp" /*teture path*/));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Wall_1.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Wall_2.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Wall_3.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Wall_4.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Floor.obj", "models/Wood-Textures-bmp.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Pic_1.obj", "models/star_map_2.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Pic_2.obj", "models/star_map_3.bmp"));
	//objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Wall_1.obj", "models/wall_paper_3.bmp"));
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/Room/Window.obj", "models/Wood-Textures-bmp.bmp"));
	
	/* Door */
	objects.push_back(new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/room_door.obj", "models/Wood-Textures-bmp.bmp")); 

	/* Desk (one piece) */
    objects.push_back(new Model(*this, vec3(0, -1.2, 4), zeroVec3, scale, "models/desk.obj", "models/Wood-Textures-bmp.bmp"));

	/* Desk Drawer */
	Model* drawer = new Model(*this, vec3(0, -0.3, 4), zeroVec3, scale, "models/drawer.obj", "models/Wood-Textures-bmp.bmp");
	objects.push_back(drawer);
	drawer->setAnim(Animation(drawer, vec3(0, -0.3, 3.5), 0));
    triggers.push_back(Trigger(*drawer/*model*/, vec3(0, 0, 4)/*position*/, 0.1/*radius*/, /*470*/2/*distance*/));

	/* Keys */
    Model* key = new Model(*this, vec3(0, -0.3, 4), zeroVec3, scale, "models/key.obj", "models/bronze.bmp", true);
    objects.push_back(key);
    triggers.push_back(Trigger(*key/*model*/, vec3(0, -0.3, 4)/*position*/, 1/*radius*/, 2/*distance*/));
	
	/* Shelf */
    objects.push_back(new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/BookShelf/Shelf_Body.obj", "models/Wood-Textures-bmp.bmp"));
	objects.push_back(new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/BookShelf/Stack_Top.obj", "models/orange.bmp"));
	objects.push_back(new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/BookShelf/Stack_Middle.obj", "models/green.bmp"));
	objects.push_back(new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/BookShelf/Stack_Bottom.obj", "models/red.bmp"));
	objects.push_back(new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/BookShelf/Lock.obj", "models/bronze.bmp"));

	/* Shelf doors */
	Model* door_right = new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/bookshelf_door.obj", "models/Wood-Textures-bmp.bmp");
	objects.push_back(door_right);
	door_right->setAnim(Animation(door_right, vec3(-3, 0, -0.55), M_PI / 2));
	door_right->setCondition(key->bPickedup);
	triggers.push_back(Trigger(*door_right, vec3(-4, 0, 0), 1, 6));
	Model* door_left = new Model(*this, vec3(-4, 0, 0.85), zeroVec3, scale, "models/bookshelf_door.obj", "models/Wood-Textures-bmp.bmp");
	objects.push_back(door_left);
	door_left->setAnim(Animation(door_left, vec3(-4, 0, 0.55), -M_PI / 2));
	door_left->setCondition(key->bPickedup);
	triggers.push_back(Trigger(*door_left, vec3(-4, 0, 0.85), 1, 6));
		

	/* Photo */
	Model* photo_f = new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/Photo_Front.obj", "models/blur_astro.bmp", true);
	Model* photo_b = new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/Photo_Back.obj", "models/photo_back.bmp", true);

    //skybox
    objects.push_back(new Skybox(*this));

    collisions.clear();
    //room
    collisions.push_back(BoxCollision2D(vec2(0, 0),vec2(5, 5), true));
    //desk
    //collisions.push_back(BoxCollision2D(vec2(),vec2()));
    //todo
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
