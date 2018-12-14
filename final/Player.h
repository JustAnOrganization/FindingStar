//
// Created by shrimp on 2018/12/3.
//

#ifndef FINALPROJECT_CAMERA_H
#define FINALPROJECT_CAMERA_H

#include "Basic.h"

class Game;
class Item;

class Player
{
public:
    Player(Game& game, float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
    :game(game), fov(fieldOfView), aspectRatio(aspectRatio), nearPlane(nearPlane), farPlane(farPlane),
     isJumping(false),playerPosition(0, 0, -3), direction(0, 0, 1), right(-1, 0 ,0), pitchAngle(0)
     {
         projectMat = perspective(fov, aspectRatio, nearPlane, farPlane);
     }

    void processEvent(SDL_Event& windowEvent, float deltaTime);
    void update(float deltaTime);

    glm::mat4 viewProjectionMat() const
    {
        return projectMat * viewMat;
    }

    //todo
    void pickup(Item* item);

    vec3 playerPosition;
    vec3 direction, right;
private:
    bool isJumping;
    float jumpVelocity;

    glm::mat4 viewMat;
    glm::mat4 projectMat;
    float pitchAngle;

    float fov;
    float aspectRatio;
    float nearPlane;
    float farPlane;
    Game& game;

    //carried items
    std::vector<Item*> items;
};


#endif //FINALPROJECT_CAMERA_H
