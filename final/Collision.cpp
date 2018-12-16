//
// Created by shrimp on 2018/12/13.
//

#include "Collision.h"
#include "Basic.h"

bool BoxCollision2D::check(vec3 position)
{
    bool ans = true;
    if (position.x > location.x-extend.x && position.x < location.x+extend.x
        && position.z > location.y-extend.y && position.z < location.y+extend.y)
        ans = false;
    if (bOut)
        ans = !ans;
    return ans;
}
