//
// Created by shrimp on 2018/12/3.
//

#include "Model.h"
#include "Utils.h"
#include "ModelImporter.h"
#include "Game.h"
#include "Animation.h"

void Model::initialize()
{
    RenderObject::initialize();

    shaderProgram = Utils::InitShader("./shaders/blinnPhong.vert", "./shaders/blinnPhong.frag");

    std::vector<glm::vec3> verts;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    ModelImporter::loadObj(modelPath.c_str(), verts, uvs, normals);
    vector<VertexPositionUvNormal> vertices;
    for (int i = 0; i < verts.size(); ++i)
    {
        vertices.push_back(VertexPositionUvNormal(verts[i], uvs[i], normals[i]));
    }
    cout << "model vertex size:" << verts.size() << endl;

    // Create the vertex and index buffers
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    vertexCount = vertices.size();
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexPositionColorUv) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Load the texture
    SDL_Surface* surface = SDL_LoadBMP(texPath.c_str());
    if (surface==NULL){
        printf("Error: \"%s\"\n",SDL_GetError());
        return;
    }
    glGenTextures(1, &tex);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

    //Load the texture into memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_BGR,GL_UNSIGNED_BYTE,surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D); //Mip maps the texture

    //What to do outside 0-1 range
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    GLfloat largest_supported_anisotropic;
//    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_supported_anisotropic);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_supported_anisotropic);

    SDL_FreeSurface(surface);
    //// End Allocate Texture ///////

    // Create VAO
    glGenVertexArrays(1, &vao); //Create a VAO
    glBindVertexArray(vao); //Bind the above created VAO to the current context

    //setup shader layout
    GLint posAttrib = glGetAttribLocation(shaderProgram, "inPosition");
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUvNormal), (void*)0);
    glEnableVertexAttribArray(posAttrib);

    GLint uvAttrib = glGetAttribLocation(shaderProgram, "inUV");
    glVertexAttribPointer(uvAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUvNormal), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(uvAttrib);

    GLint normalAttrib = glGetAttribLocation(shaderProgram, "inNormal");
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(VertexPositionUvNormal), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(normalAttrib);

    WVPMat.init(shaderProgram, "WVPMat");
    WorldMat.init(shaderProgram, "WorldMat");
    LightDir.init(shaderProgram, "LightDir");
    AmbientColor.init(shaderProgram, "AmbientColor");
    LightColor.init(shaderProgram, "LightColor");
    CamPosition.init(shaderProgram, "CamPosition");
    SpecColor.init(shaderProgram, "SpecColor");
}

void Model::update(float deltaTime)
{
    RenderObject::update(deltaTime);

    anim.update(deltaTime);
}

void Model::destroy()
{
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &tex);

    RenderObject::destroy();
}

void Model::draw()
{
    RenderObject::draw();

    if (!bShow)
        return;

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    mat4 wvp = game.player.viewProjectionMat() * worldMat;
    WVPMat << wvp;
    WorldMat << worldMat;
    LightDir << vec3(0.5, -1, 0.1);
    AmbientColor << vec3(0.6, 0.6, 0.6);
    LightColor << vec3();
    CamPosition << game.player.playerPosition;
    SpecColor << vec4(1, 1, 1, 5);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);

//    glEnable(GL_CULL_FACE);
//    glFrontFace(GL_CCW);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

void Model::triggered()
{
    if (bCanPickup)
    {
        pickup();
    }
    if (bHasAnim)
    {
        anim.play();
    }
    if (bHasText)
    {
        game.showText(text);
    }
}

Model::Model(Game &game, vec3 location, vec3 rotation, vec3 scale, string modelPath, string texPath, bool bCanPickup)
        : anim(this), RenderObject(game, location, rotation, scale), modelPath(modelPath), texPath(texPath), bCanPickup(bCanPickup)
        , bHasAnim(false), bHasText(false) { }

void Model::pickup()
{
    bPickedup = true;
    static Model* currModel = nullptr;
    //curr pick up model disappear
    if (currModel)
    {
        currModel->bShow = false;
    }
    currModel = this;
}

void Model::setAnim(const Animation& anim)
{
    bHasAnim = true;
    this->anim = anim;
}

void Model::setText(std::vector<string> &text)
{
    bHasText = true;
    this->text = text;
}
