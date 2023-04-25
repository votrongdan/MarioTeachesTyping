#ifndef CHARACTER_H
#define CHARACTER_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Character {

    public:

        Character();

        // random a character
        void createChar();

        // get character
        char getChar();
        
        // random a threat
        void createThreat();

        // get Threat
        int getThreat();

        // render a character
        void renderCharacter(SDL_Renderer* renderer);

    private:

        // initialize character
        char c;
        
        // initialize threat
        int threat;

        // initialize x condinate of character
        int xPos;

        // // initialize turtle
        // Turtle gTurtle;

        // // initialize tile
        // Tile gTile;

};

class Turtle : public BaseObj {

    public:

        Turtle();
        ~Turtle();

        void renderTurtle(SDL_Renderer* renderer, int x);
    
    private:

        const int yPos = 384;

};

class Tile : public BaseObj {

    public:

        Tile();
        ~Tile();

        void renderTile(SDL_Renderer* renderer, int x);
    
    private:

        const int yPos = 184;

};

#endif