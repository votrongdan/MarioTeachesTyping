#ifndef HAND_H
#define HAND_H

#include "CommonFunc.h"
#include "BaseObj.h"

#define X_RIGHT_HAND 710
#define Y_RIGHT_HAND 560

#define X_LEFT_HAND 300
#define Y_LEFT_HAND 560

#define HAND_WIDTH 140
#define HAND_HEIGHT 150

class RightHand : public BaseObj {
    public:

        RightHand() {;}
        ~RightHand() {;}

        bool loadRightHand(SDL_Renderer* renderer, string path);

        void renderRightHand(SDL_Renderer* renderer, char c);

    private: 

        SDL_Rect rightHandClips[5];

};

class LeftHand : public BaseObj {
    public:

        LeftHand() {;}
        ~LeftHand() {;}

        bool loadLeftHand(SDL_Renderer* renderer, string path);

        void renderLeftHand(SDL_Renderer* renderer, char c);

    private:

        SDL_Rect leftHandClips[5];

};

#endif