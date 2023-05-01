#include "Hand.h"

bool RightHand::loadRightHand(SDL_Renderer* renderer, string path) {

    bool success = true;

    if (!BaseObj::loadMedia(renderer, path.c_str())) {

        printf("Failed to load right hand texture from file! %s\n");
        success = false;

    }
    else {

        for (int i = 0; i < 5; i++) {

            rightHandClips[i].x = i * HAND_WIDTH;
            rightHandClips[i].y = 0;
            rightHandClips[i].w = HAND_WIDTH;
            rightHandClips[i].h = HAND_HEIGHT;

        }

    }

    return success;

}

void RightHand::renderRightHand(SDL_Renderer* renderer, char c) {

    SDL_Rect currentClip;

    switch(c) {

        case 'y': case 'h': case 'n': case 'u': case 'j': case 'm':
        currentClip = rightHandClips[1];
        break;

        case 'i': case 'k': 
        currentClip = rightHandClips[2];
        break;

        case 'o': case 'l':
        currentClip = rightHandClips[3];
        break;
        
        case 'p':
        currentClip = rightHandClips[4];
        break;

        default:
        currentClip = rightHandClips[0];
        break;

    }

    BaseObj::render(X_RIGHT_HAND, Y_RIGHT_HAND, renderer, &currentClip);

}

bool LeftHand::loadLeftHand(SDL_Renderer* renderer, string path) {

    bool success = true;

    if (!BaseObj::loadMedia(renderer, path.c_str())) {

        printf("Failed to load left hand texture from file! %s\n");
        success = false;

    }
    else {

        for (int i = 0; i < 5; i++) {

            leftHandClips[i].x = i * HAND_WIDTH;
            leftHandClips[i].y = 0;
            leftHandClips[i].w = HAND_WIDTH;
            leftHandClips[i].h = HAND_HEIGHT;

        }

    }

    return success;

}

void LeftHand::renderLeftHand(SDL_Renderer* renderer, char c) {

    SDL_Rect currentClip;

    switch (c) {

        case 't': case 'g': case 'b': case 'r': case 'f': case 'v':
        currentClip = leftHandClips[1];
        break;

        case 'e': case 'd': case 'c':
        currentClip = leftHandClips[2];
        break;

        case 'w': case 's': case 'x':
        currentClip = leftHandClips[3];
        break;

        case 'q': case 'a': case 'z':
        currentClip = leftHandClips[4];
        break;

        default:
        currentClip = leftHandClips[0];
        break;

    }

    BaseObj::render(X_LEFT_HAND, Y_LEFT_HAND, renderer, &currentClip);

}