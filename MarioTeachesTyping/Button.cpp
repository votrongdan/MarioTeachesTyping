#include "Button.h"

Button::Button() {

    position.x = 0;
    position.y = 0;

    currentButtonSprite = MOUSE_OUT;

    up = false;

}

void Button::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Button::handleEvent(SDL_Event* e) {

    // if mouse event happened
    if (e -> type == SDL_MOUSEMOTION || e -> type == SDL_MOUSEBUTTONDOWN || e -> type == SDL_MOUSEBUTTONUP) {

        // check if mouse is in button
        bool inside = true;

        // get mouse position
        int x, y;
        SDL_GetMouseState(&x, &y);

        // if mouse is left of the button
        if (x < position.x) {
            inside = false;
        }

        // if mouse is right of the button
        else if (x > position.x + 200) {
            inside = false;
        }

        // if mouse is above the button
        else if (y < position.y) {
            inside = false;
        }

        // if mouse is below the button
        else if (y > position.y + 49) {
            inside = false;
        }

        // mouse is outside the button
        if (inside == false) {
            currentButtonSprite = MOUSE_OUT;
        }

        // mouse is inside the button
        else {
            
            switch (e -> type)
            {
            case SDL_MOUSEBUTTONUP:
                up = true;
                break;
            
            default:
                currentButtonSprite = MOUSE_OVER_MOTION;
                break;
            }
        }

    }

}

bool Button::isUp() {
    return up;
}

void Button::renderButton(SDL_Renderer* renderer) {

    BaseObj::render(position.x, position.y, renderer, &spriteClips[currentButtonSprite]);

}

bool Button::loadButton(SDL_Renderer* renderer, string path) {

    bool success = true;

    if (!BaseObj::loadMedia(renderer, path.c_str())) {

        printf("Failed to load button from file %s\n");
        success = false;

    } 
    else {

        for (int i = 0; i < 2; i++) {
            spriteClips[i].x = 0;
            spriteClips[i].y = i * 49;
            spriteClips[i].w = 200;
            spriteClips[i].h = 49;
        }

    }

    return success;

}