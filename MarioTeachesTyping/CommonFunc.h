#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include "SDL.h"
#include <SDL_Image.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

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

// enum keys {
//     SDLK_a,
//     SDLK_b,
//     SDLK_c,
//     SDLK_d,
//     SDLK_e,
//     SDLK_f,
//     SDLK_g,
//     SDLK_h,
//     SDLK_i,
//     SDLK_j,
//     SDLK_k,
//     SDLK_l,
//     SDLK_m,
//     SDLK_n,
//     SDLK_o,
//     SDLK_p,
//     SDLK_q,
//     SDLK_r,
//     SDLK_s,
//     SDLK_t,
//     SDLK_u,
//     SDLK_v,
//     SDLK_w,
//     SDLK_x,
//     SDLK_y,
//     SDLK_z 
// };


#endif