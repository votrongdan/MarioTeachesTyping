#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <string>

using namespace std;

// screen dimention constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// the window'll be rendering
static SDL_Window* gWindow = NULL;

// the window renderer
static SDL_Renderer* gRenderer = NULL;


#endif