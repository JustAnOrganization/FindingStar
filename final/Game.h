#ifndef GAME_H
#define GAME_H

#include "Basic.h"
#include "Player.h"
#include "Collision.h"

class Game;

class RenderObject
{
public:
    RenderObject(Game& game, vec3 location, vec3 rotation, vec3 scale): game(game), location(location), rotation(rotation), scale(scale)
    {
        updateMatrix();
    }
    virtual ~RenderObject()
    {
        destroy();
    }

    void updateMatrix()
    {
        worldMat = glm::scale(mat4(), scale);

        worldMat = rotate(worldMat, rotation.x, vec3(1, 0, 0));
        worldMat = rotate(worldMat, rotation.y, vec3(0, 1, 0));
        worldMat = rotate(worldMat, rotation.z, vec3(0, 0, 1));

        worldMat = translate(worldMat, location);
    }

    virtual void initialize(){};
    virtual void update(float deltaTime){};
    virtual void draw() {};
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

    void draw();

    //todo
    bool win()
    {
        return false;
    }

    bool checkCollision(vec3 position);

    Player player;
private:
    vector<RenderObject*> objects;
    vector<BoxCollision2D> collisions;

    int screenWidth;
    int screenHeight;
};

#endif //GAME_H
