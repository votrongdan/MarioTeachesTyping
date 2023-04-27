#include "Mario.h"

Mario::Mario() {

    xPos = 0;
    yPos = 480;

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

        jumpClips[0].x = 4;
        jumpClips[0].y = 315;
        jumpClips[0].w = 73;
        jumpClips[0].h = 130;

        jumpClips[1].x = 82;
        jumpClips[1].y = 315;
        jumpClips[1].w = 93;
        jumpClips[1].h = 130;

        jumpClips[2].x = 181;
        jumpClips[2].y = 315;
        jumpClips[2].w = 93;
        jumpClips[2].h = 130;

        jumpClips[3].x = 279;
        jumpClips[3].y = 315;
        jumpClips[3].w = 93;
        jumpClips[3].h = 130;

        jumpClips[4].x = 378;
        jumpClips[4].y = 315;
        jumpClips[4].w = 93;
        jumpClips[4].h = 130;

        jumpClips[5].x = 476;
        jumpClips[5].y = 315;
        jumpClips[5].w = 91;
        jumpClips[5].h = 130;

        jumpClips[6].x = 572;
        jumpClips[6].y = 315;
        jumpClips[6].w = 88;
        jumpClips[6].h = 130;

        jumpClips[7].x = 665;
        jumpClips[7].y = 315;
        jumpClips[7].w = 81;
        jumpClips[7].h = 130;

        jumpClips[8].x = 751;
        jumpClips[8].y = 315;
        jumpClips[8].w = 83;
        jumpClips[8].h = 130;

        jumpClips[9].x = 839;
        jumpClips[9].y = 315;
        jumpClips[9].w = 99;
        jumpClips[9].h = 130;

        jumpClips[10].x = 943;
        jumpClips[10].y = 315;
        jumpClips[10].w = 83;
        jumpClips[10].h = 130;

    }

    return success;

}

void Mario::setStatus(int status) {
    
    this -> status = status;

}

int Mario::getStatus() {

    return status;

}

void Mario::jump(SDL_Renderer* renderer) {

    SDL_Rect currentClip;

    currentClip = jumpClips[frame / 25];

    BaseObj::render(xPos, yPos - currentClip.h, renderer, &currentClip);

    if (frame < 125) {
        yPos -= 1;
    } else if (frame > 150) {
        yPos += 1;
    }

    frame++;

    if (frame == 275) {
        status == 0;
        return;
    }

}

void Mario::run(SDL_Renderer* renderer) {

    SDL_Rect currentClip;

    currentClip = runClips[frame / 6];

    BaseObj::render(xPos, yPos - currentClip.h, renderer, &currentClip);
    
    xPos += 10;

    frame++;

    if (frame == 36) frame = 0;
}

void Mario::stand(SDL_Renderer* renderer) {

    SDL_Rect currentClip;

    currentClip = standClips[0];

    BaseObj::render(xPos, yPos - currentClip.h, renderer, &currentClip);

}


// void Mario::renderMario(SDL_Renderer* renderer) {

//     // SDL_Rect currentClip = runClips[1];

//     // BaseObj::render(xPos, yPos, renderer, &currentClip);
//     run(renderer);

// }