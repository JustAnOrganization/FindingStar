//
//
//

#ifndef FINALPROJECT_COLLISION_H
#define FINALPROJECT_COLLISION_H

#include "Basic.h"

class BoxCollision2D
{
public:
    BoxCollision2D(vec2 location, vec2 extend, bool out = false): location(location), extend(extend), bOut(out){ }

    bool check(vec3 position);
private:
    bool bOut;
    vec2 location;
    vec2 extend;
};


#endif //FINALPROJECT_COLLISION_H
