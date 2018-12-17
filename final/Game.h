#ifndef GAME_H
#define GAME_H

#include "Basic.h"
#include "Player.h"
#include "Collision.h"
#include "Animation.h"
#include "TextRenderer.h"

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

    void setLocation(vec3 newLocation)
    {
        location = newLocation;
        updateMatrix();
    }
    vec3 getLocation()
    {
        return location;
    }
    vec3 getRotation()
    {
        return rotation;
    }
    void setRotation(vec3 newRot)
    {
        rotation = newRot;
        updateMatrix();
    }
    vec3 getForward()
    {
        mat4 rotMat = mat4();
        rotMat = rotate(rotMat, rotation.x, vec3(1, 0, 0));
        rotMat = rotate(rotMat, rotation.y, vec3(0, 1, 0));
        rotMat = rotate(rotMat, rotation.z, vec3(0, 0, 1));
        return vec3(vec4(0,0,1,0)*rotMat);
    }
    vec3 getScale()
    {
        return scale;
    }
    void setScale(vec3 newScale)
    {
        scale = newScale;
        updateMatrix();
    }

    void updateMatrix()
    {
        worldMat = translate(mat4(), location);

        worldMat = rotate(worldMat, rotation.x, vec3(1, 0, 0));
        worldMat = rotate(worldMat, rotation.y, vec3(0, 1, 0));
        worldMat = rotate(worldMat, rotation.z, vec3(0, 0, 1));

        worldMat = glm::scale(worldMat, scale);
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
    friend class Player;
public:
    Game(int width, int height);

    virtual ~Game();

    void initialize();

    void update(float deltaTime);

    void draw();

	void showText(const vector<string>& texts);

    bool win();

    bool checkCollision(vec3 position);

    Player player;
private:
    vector<RenderObject*> objects;
    vector<BoxCollision2D> collisions;
    vector<Trigger> triggers;

    TextRenderer textRenderer;
    vector<string> text;
    float textTimer;

    int screenWidth;
    int screenHeight;
    Model* key;
    Model* photo;
};

#endif //GAME_H
