#ifndef BUTTON_H
#define BUTTON_H

#include "CommonFunc.h"
#include "BaseObj.h"

#define MOUSE_OUT 0
#define MOUSE_OVER_MOTION 1


class Button : public BaseObj{

    public:

        // initializes internal variables
        Button();

        // set top left position
        void setPosition(int x, int y);

        // handles mouse event
        void handleEvent(SDL_Event* e); 

        bool isUp();

        void renderButton(SDL_Renderer* renderer);

        bool loadButton(SDL_Renderer* renderer, string path);

    private:

        SDL_Point position;

        int currentButtonSprite;

        bool up;

        SDL_Rect spriteClips[2];

};

#endif