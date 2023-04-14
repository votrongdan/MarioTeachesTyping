#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_Image.h>
#include <string>
#include <fstream>

using namespace std;

// screen dimension constants
const int SCREEN_WIDTH = 1152;
const int SCREEN_HEIGHT = 720;

// the window'll be rendering
static SDL_Window* gWindow = NULL;

// the window renderer
static SDL_Renderer* gRenderer = NULL;

// the y coordinate of sky line 
#define SKY_LINE 480


#endif