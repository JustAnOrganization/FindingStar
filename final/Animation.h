//
// Created by shrimp on 2018/12/13.
//

#ifndef FINALPROJECT_ANIMATEDOBJECT_H
#define FINALPROJECT_ANIMATEDOBJECT_H

#include "Basic.h"

class Model;

//sphere trigger
struct Trigger
{
    Trigger(Model& model, vec3 position, float radius, float distance = 0.5);
    bool trigger(vec3 playerPosition, vec3 playerForward);
    Model& model;
    vec3 position;
    float radius, distance;
};

struct Animation
{
    Animation(vec3 translateTarget, vec3 rotateTarget):translateTarget(translateTarget),rotateTarget(rotateTarget) { }

    vec3 rotateTarget;
    vec3 translateTarget;

    //todo
    void update(float deltaTime);
};


#endif //FINALPROJECT_ANIMATEDOBJECT_H
