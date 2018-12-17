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

std::string key_text_1 = "Papa,";
std::string key_text_2 = "If you are reading this, it probably means I can't tell you the story from Andromeda myself.";
std::string key_text_3 = "I don't regret joining this mission. See me come back as a pinch of stardust.";
std::string key_text_4 = " Yours, Stella";
std::vector<string> key_texts = vector<string>{ key_text_1,key_text_2,key_text_3, key_text_4 };


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

	/* Desk (one piece) */
    objects.push_back(new Model(*this, vec3(0, -1.2, 4), zeroVec3, scale, "models/desk.obj", "models/Wood-Textures-bmp.bmp"));

	/* Desk Drawer */
	Model* drawer = new Model(*this, vec3(0, -0.3, 4), zeroVec3, scale, "models/drawer.obj", "models/Wood-Textures-bmp.bmp");
	objects.push_back(drawer);
	drawer->setAnim(Animation(drawer, vec3(0, -0.3, 3.5), 0));
    triggers.push_back(Trigger(*drawer/*model*/, vec3(0, -0.3, 4)/*position*/, 0.1/*radius*/, /*470*/2/*distance*/));

	/* Keys */
    key = new Model(*this, vec3(0, -0.3, 3), zeroVec3, scale, "models/key.obj", "models/bronze.bmp", true);
    objects.push_back(key);
    key->setText(key_texts);
    triggers.push_back(Trigger(*key/*model*/, vec3(0, -0.3, 3)/*position*/, 1/*radius*/, 2/*distance*/));
	
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
	triggers.push_back(Trigger(*door_right, vec3(-4, 0, 0), 1, 6, key));
	Model* door_left = new Model(*this, vec3(-4, 0, 0.85), zeroVec3, scale, "models/bookshelf_door.obj", "models/Wood-Textures-bmp.bmp");
	objects.push_back(door_left);
	door_left->setAnim(Animation(door_left, vec3(-4, 0, 0.55), -M_PI / 2));
	triggers.push_back(Trigger(*door_left, vec3(-4, 0, 0.85), 1, 6, key));

	/* Photo */
	photo = new Model(*this, vec3(-3.9, -0, 0), vec3(M_PI/2, M_PI / 2,0), scale, "models/photo.obj", "models/photo_single.bmp", true);
	//Model* photo_b = new Model(*this, vec3(-4, 0, 0), zeroVec3, scale, "models/Photo_Back.obj", "models/photo_back.bmp", true);
	triggers.push_back(Trigger(*photo, vec3(-3.9, -0, 0), 1, 1, key));
	objects.push_back(photo);

	/* Door */
	Model* room_door = new Model(*this, vec3(0, -2, 0), zeroVec3, scale, "models/room_door.obj", "models/Wood-Textures-bmp.bmp");
	//Model* room_door = new Model(*this, vec3(-0.8, -2, -7.2), vec3(0,M_PI/2,0), scale, "models/room_door.obj", "models/Wood-Textures-bmp.bmp");
	room_door->setAnim(Animation(room_door, vec3(-0.8, -2, -7.2), M_PI / 2));
	triggers.push_back(Trigger(*room_door, vec3(0, -2, 0), 1, 10, photo));
	objects.push_back(room_door);

    //skybox
    objects.push_back(new Skybox(*this));

    collisions.clear();
    //room
    collisions.push_back(BoxCollision2D(vec2(0, 0),vec2(5, 5), true));
    //desk
	collisions.push_back(BoxCollision2D(vec2(0, 4),vec2(1.3,0.7)));
	//shelf
	collisions.push_back(BoxCollision2D(vec2(-4, 0), vec2(0.9, 0.3)));
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

    textRenderer.init();

    glEnable(GL_DEPTH_TEST);
}

void Game::update(float deltaTime)
{
    player.update(deltaTime);

    for (auto* object: objects)
    {
        object->update(deltaTime);
    }


    if (textTimer > 0)
    {
        //printf("texttimer:%f", textTimer);
        textTimer -= deltaTime;
        for (int i = 0; i < text.size(); ++i)
        {
            textRenderer.renderText(text[i], screenWidth / 2.0f - 220, screenHeight / 2.f - i * 50, 0.5, glm::vec3(1, 1, 1));
        }
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

void Game::showText(const vector<string>& texts)
{
    text = texts;
    textTimer = 10;
}

bool Game::win()
{
    return photo->hasPickedup();
}
