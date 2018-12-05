#ifndef GAME_H
#define GAME_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "glm/glm.hpp"
#include "glad/glad.h"
#include "Player.h"

using namespace std;
using namespace glm;

class Game;

class RenderObject
{
public:
    RenderObject(Game& game, vec3 location, vec3 rotation, vec3 scale): game(game), rotation(rotation), scale(scale)
    {
        setLocation(location);
    }
    virtual ~RenderObject()
    {
        destroy();
    }

    void setLocation(const vec3& location)
    {
        this->location = location;
        worldMat = translate(mat4(), location);
    }

    virtual void initialize(){};
    virtual void update(float deltaTime){};
    virtual void destroy(){};

protected:
    vec3 location, rotation, scale;
    Game& game;
    glm::mat4 worldMat;
};

class Game
{
public:
    Game(int width, int height);

    virtual ~Game();

    void initialize();

    void update(float deltaTime);

    Player player;
private:
    vector<RenderObject*> objects;
    int screenWidth;
    int screenHeight;
};

#endif //GAME_H
