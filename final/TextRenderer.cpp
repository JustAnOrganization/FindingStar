//
// Created by shrimp on 2018/12/8.
//
//reference: https://learnopengl.com/In-Practice/Text-Rendering
#include "TextRenderer.h"
#include "Utils.h"

void TextRenderer::init()
{
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("font/veteran_typewriter.ttf", 35);
    SDL_Color color = { 255, 0, 0 };
    SDL_Surface *face = NULL;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    for (GLubyte c = 1; c < 128; c++)
    {
        string tmp(1, (char)c);

        face = TTF_RenderText_Blended(font, tmp.c_str(), color);

        int mode;
        if (face->format->BytesPerPixel == 3)
        { // RGB 24bit
            mode = GL_RGB;
        } else if (face->format->BytesPerPixel == 4)
        { // RGBA 32bit
            mode = GL_RGBA;
        } else
        {
            SDL_FreeSurface(face);
            printf("font surface type error\n");
            return;
        }

        GLuint texture = 0;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexImage2D(GL_TEXTURE_2D, 0, mode, face->w, face->h, 0, mode, GL_UNSIGNED_BYTE, face->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int minx, maxx, miny, maxy, advance;
        if (TTF_GlyphMetrics(font, *(tmp.c_str()), &minx, &maxx, &miny, &maxy, &advance) == -1)
        {
            printf("%s\n", TTF_GetError());
        }

        Character character = {
                texture,
                vec2(face->w, face->h),
                vec2(minx, maxy),
                (GLuint)advance
        };
        Characters.insert(std::pair<GLchar, Character>(char(c), character));
    }

    shaderProgram = Utils::InitShader("./shaders/font.vert", "./shaders/font.frag");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), 0.0f, static_cast<GLfloat>(600));
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::renderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color)
{
    glUseProgram(shaderProgram);
    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);

    //glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y;//- (ch.Size.y - ch.Bearing.y) * scale;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };
        // Render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // Update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // Render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph
        x += ch.Advance * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);
}
