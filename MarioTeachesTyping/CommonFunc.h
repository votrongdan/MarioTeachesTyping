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

// dimension of tile
#define TILE_SIZE 48;

// number of tile on width
#define MAX_X 1200;
// number of tile on height
#define MAX_Y 15;

typedef struct Map {

    // location of tile 
    int x;
    int y;

    // index of tile
    int maxX;
    int maxY;

    // status of tile
    int tiles[MAX_Y][MAX_X];

    string fileName;

};


#endif