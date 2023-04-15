#include "Mario.h"

Mario::Mario() {

    xPos = 144;
    yPos = 480;

    xDistance = 50;
    yDistance = 0;

    widthMario = 0;
    heightMario = 0;

    status = 0;
    
    frame = 0;

}

Mario::~Mario() {

    free();

}

int Mario::getXPos() {
    return xPos;
}

int Mario::getYPos() {
    return yPos;
}

bool Mario::loadMario(SDL_Renderer* renderer, string path) {

    bool success = true;

    if (!BaseObj::loadMedia(renderer, path.c_str())) {

        printf("Failed to load Mario texture from file! %s\n");
        success = false;

    } else {

        standClips[0].x = 4;
        standClips[0].y = 4;
        standClips[0].w = 65;
        standClips[0].h = 109;

        runClips[0].x = 4;
        runClips[0].y = 118;
        runClips[0].w = 83;
        runClips[0].h = 94;

        runClips[1].x = 92;
        runClips[1].y = 118;
        runClips[1].w = 99;
        runClips[1].h = 94;

        runClips[2].x = 196;
        runClips[2].y = 118;
        runClips[2].w = 83;
        runClips[2].h = 94;

        runClips[3].x = 284;
        runClips[3].y = 118;
        runClips[3].w = 73;
        runClips[3].h = 94;

        runClips[4].x = 362;
        runClips[4].y = 118;
        runClips[4].w = 86;
        runClips[4].h = 94;

        runClips[5].x = 453;
        runClips[5].y = 118;
        runClips[5].w = 80;
        runClips[5].h = 94;

        jumpClips[0].x;
        jumpClips[0].y;
        jumpClips[0].w;
        jumpClips[0].h;

        jumpClips[1].x;
        jumpClips[1].y;
        jumpClips[1].w;
        jumpClips[1].h;

        jumpClips[2].x;
        jumpClips[2].y;
        jumpClips[2].w;
        jumpClips[2].h;

        jumpClips[3].x;
        jumpClips[3].y;
        jumpClips[3].w;
        jumpClips[3].h;

        jumpClips[4].x;
        jumpClips[4].y;
        jumpClips[4].w;
        jumpClips[4].h;

        jumpClips[5].x;
        jumpClips[5].y;
        jumpClips[5].w;
        jumpClips[5].h;

        jumpClips[6].x;
        jumpClips[6].y;
        jumpClips[6].w;
        jumpClips[6].h;

        jumpClips[7].x;
        jumpClips[7].y;
        jumpClips[7].w;
        jumpClips[7].h;

        jumpClips[8].x;
        jumpClips[8].y;
        jumpClips[8].w;
        jumpClips[8].h;

        jumpClips[9].x;
        jumpClips[9].y;
        jumpClips[9].w;
        jumpClips[9].h;

        jumpClips[10].x;
        jumpClips[10].y;
        jumpClips[10].w;
        jumpClips[10].h;

    }

    return success;

}

void Mario::setStatus(int status) {
    
    this -> status = status;

}

int Mario::getStatus() {

    return status;

}

void Mario::run(SDL_Renderer* renderer, int x, int y, int f) {

    SDL_Rect currentClip;

    currentClip = runClips[f];

    BaseObj::render(x, y - currentClip.h, renderer, &currentClip);
    // SDL_RenderPresent( renderer );

}

void Mario::stand(SDL_Renderer* renderer, int x, int y, int f) {

    SDL_Rect currentClip;

    currentClip = standClips[f];

    BaseObj::render(x, y - currentClip.h, renderer, &currentClip);

}


// void Mario::renderMario(SDL_Renderer* renderer) {

//     // SDL_Rect currentClip = runClips[1];

//     // BaseObj::render(xPos, yPos, renderer, &currentClip);
//     run(renderer);

// }