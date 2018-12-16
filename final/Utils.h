//
// Created by shrimp on 2018/12/4.
//

#ifndef FINALPROJECT_SHADERLOADER_H
#define FINALPROJECT_SHADERLOADER_H

#include "Basic.h"

const vec3 zeroVec3(0, 0, 0);

#define DEBUG_ON false

class UnifromVariable
{
public:
    UnifromVariable() { }

    void init(GLint shaderProgram, const std::string& name);

    UnifromVariable& operator<<(const glm::mat4& value);
    UnifromVariable& operator<<(const glm::vec4& value);
    UnifromVariable& operator<<(const glm::vec3& value);
    UnifromVariable& operator<<(const glm::vec2& value);
    UnifromVariable& operator<<(float value);
    UnifromVariable& operator<<(int value);
private:
    GLint location;
    std::string name;
};

class Utils
{
public:
    // Create a GLSL program object from vertex and fragment shader files
    static GLuint InitShader(const char* vShaderFileName, const char* fShaderFileName);

private:

    // Create a NULL-terminated string by reading the provided file
    static char* readShaderSource(const char* shaderFile);
};


#endif //FINALPROJECT_SHADERLOADER_H
