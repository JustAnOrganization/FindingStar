//
// Created by shrimp on 2018/12/3.
//

#ifndef FINALPROJECT_BASIC_H
#define FINALPROJECT_BASIC_H

#include "glad/glad.h"  //Include order can matter here
#if defined(__APPLE__) || defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_opengl.h>
//#include <SDL2_ttf-2.0.14/SDL_ttf.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#endif
#include <cstdio>
#include <math.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
using namespace glm;
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#endif //FINALPROJECT_BASIC_H
