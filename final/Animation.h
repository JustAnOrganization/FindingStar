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
    //typedef std::function<bool()> Condition;

    Trigger(Model& model, vec3 position, float radius, float distance = 0.5, Model* prereqModel = nullptr);
    bool trigger(vec3 playerPosition, vec3 playerForward);
    Model& model;
    vec3 position;
    float radius, distance;
    bool bActive;
    Model* prereqModel;
};

struct Animation
{
    Animation(Model* model): model(model) { }
    Animation(Model* model,vec3 translateTarget, float rotateY):model(model), translateTarget(translateTarget),rotateTarget(rotateY) { }

    float rotateTarget;
    vec3 translateTarget;

    void play();
    void update(float deltaTime);
private:
    Model* model;
    bool bPlaying = false;
    float originRot;
    vec3 originTrans;
    float currPercent=0;
};


#endif //FINALPROJECT_ANIMATEDOBJECT_H
