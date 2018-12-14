//
// Created by shrimp on 2018/12/3.
//

//reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/

#ifndef FINALPROJECT_MODELIMPORTER_H
#define FINALPROJECT_MODELIMPORTER_H

#include "Basic.h"


class ModelImporter
{
public:

    static bool loadObj(const char * path, std::vector<glm::vec3> & vertices, std::vector<glm::vec2> & uvs
            , std::vector<glm::vec3> & normals);
};


#endif //FINALPROJECT_MODELIMPORTER_H
