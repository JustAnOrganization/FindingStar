//
// Created by shrimp on 2018/12/13.
//

#ifndef FINALPROJECT_ANIMATEDOBJECT_H
#define FINALPROJECT_ANIMATEDOBJECT_H

#include "Model.h"

//sphere trigger
struct Trigger
{
    Trigger(vec3 position, vec3 radius): position(position), radius(radius) {}
    bool trigger(vec3 playerPosition, vec3 playerForward)
    {
        //ray to sphere && distance
        if (distance(playerPosition, position) > 0.5)
            return false;
        //todo

    }
    vec3 position;
    vec3 radius;
};

struct Animation
{
    vec3 rotateTarget;
    vec3 translateTarget;

    void update(float deltaTime);
};

class AnimatedObject: public Model
{
public:
    AnimatedObject(Game& game, vec3 location, vec3 rotation, vec3 scale, std::string modelPath="models/desk.obj"
    , std::string texPath="textures/wood.bmp")
    : Model(game, location, rotation, scale, modelPath, texPath)
    {
    }

    virtual void initialize() override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;
    virtual void destroy() override;

private:
    Animation anim;
    bool trigger = false;

};


#endif //FINALPROJECT_ANIMATEDOBJECT_H
