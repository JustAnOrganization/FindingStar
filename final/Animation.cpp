//
// Created by shrimp on 2018/12/13.
//

#include "Animation.h"

bool Trigger::trigger(vec3 playerPosition, vec3 playerForward)
{
    //ray to sphere && distance
    if (glm::distance(playerPosition, position) > distance)
        return false;

    playerForward = normalize(playerForward);

    float b = dot(2.0f * playerForward, (playerPosition - position));
    float c = (playerPosition - position).length() * (playerPosition - position).length() - radius * radius;
    float delta = b * b - 4 * c;
    if (delta > 1e-3)
    {
        return true;
    }
    return false;
}

Trigger::Trigger(Model &model, vec3 position, float radius, float distance)
        : model(model), position(position), radius(radius), distance(distance) {}
