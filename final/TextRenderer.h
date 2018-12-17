//
// Created by shrimp on 2018/12/8.
//

#ifndef FINALPROJECT_TEXTRENDERER_H
#define FINALPROJECT_TEXTRENDERER_H

#include "Basic.h"

struct Character {
    GLuint		TextureID;
    vec2		Size;
    vec2		Bearing;
    GLuint		Advance;
};

class TextRenderer
{
public:
    void init();

    void renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color=vec3(1,1,1));

private:
    GLuint shaderProgram;
    GLuint vao, vbo;
    std::map<GLchar, Character> Characters;
};


#endif //FINALPROJECT_TEXTRENDERER_H
