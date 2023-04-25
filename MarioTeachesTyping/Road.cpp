#include "Road.h"

Road::~Road() {

    gGrass.free();

}

bool Road::loadGrass (SDL_Renderer* renderer, string path) {

    // initialize success flag
    bool success = true;

    if (!gGrass.loadMedia(renderer, path.c_str())) {

        printf("Failed to load grass block! %s\n");
        success = false;

    }

    return success;

}

void Road::renderRoad(SDL_Renderer* renderer, int xRoad) {

    gGrass.render(xRoad, SKY_LINE, renderer);

}

void Road::free() {

    gGrass.free();

}