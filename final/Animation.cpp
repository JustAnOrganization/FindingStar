//
// Created by shrimp on 2018/12/13.
//

#include "Animation.h"
#include "Model.h"

bool Trigger::trigger(vec3 playerPosition, vec3 playerForward)
{
    if (!bActive) return false;
    if (prereqModel)
    {
        if (!prereqModel->hasPickedup())
        {
            return false;
        }
    }

    printf("%s dist:%f\n", model.modelPath.c_str(), glm::distance(playerPosition, position));

    //ray to sphere && distance
    if (glm::distance(playerPosition, position) > distance)
        return false;

    return true;
    playerForward = normalize(playerForward);

    float b = dot(2.0f * playerForward, (playerPosition - position));
    float c = (playerPosition - position).length() * (playerPosition - position).length() - radius * radius;
    float delta = b * b - 4 * c;
    if (delta > 1e-3)
    {
        bActive = false;
        return true;
    }
    return false;
}

Trigger::Trigger(Model &model, vec3 position, float radius, float distance, Model* prereqModel)
        : model(model), position(position), radius(radius), distance(distance), bActive(true), prereqModel(prereqModel) {}

void Animation::play()
{
    if (!bPlaying)
    {
        originTrans = model->getLocation();
        originRot = model->getRotation().y;
    }
    bPlaying = true;
}

void Animation::update(float deltaTime)
{
    if (bPlaying)
    {
        currPercent += deltaTime * 2.0f;
        if (currPercent >= 1)
        {
            currPercent = 1;
            bPlaying = false;
        }
        vec3 newLocation = originTrans*(1-currPercent)+translateTarget*currPercent; //mix(originTrans, translateTarget, currPercent);
        float newRot = originRot*(1-currPercent)+rotateTarget*currPercent;//mix(originRot, rotateTarget, currPercent);
        model->setLocation(newLocation);
        printf("%s new location:%f,%f,%f\n", model->modelPath.c_str(), newLocation.x, newLocation.y, newLocation.z);
        vec3 rot = model->getRotation();
        rot.y = newRot;
        model->setRotation(rot);
        printf("%s new rot:%f,%f,%f\n", model->modelPath.c_str(), rot.x, rot.y, rot.z);
    }
}
