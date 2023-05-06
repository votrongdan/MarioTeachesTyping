#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include "SDL.h"
#include <SDL_Image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <SDL_ttf.h>

using namespace std;

// screen dimension constants
const int SCREEN_WIDTH = 1152;
const int SCREEN_HEIGHT = 720;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

// the window'll be rendering
static SDL_Window* gWindow = NULL;

// the window renderer
static SDL_Renderer* gRenderer = NULL;

// Globally used font
static TTF_Font* gFont = NULL;

// game font
static TTF_Font* gameFont = NULL;

// the y coordinate of sky line 
#define SKY_LINE 480

#define MAX_THREAT 40

#endif