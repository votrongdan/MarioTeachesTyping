#ifndef CHARACTER_H
#define CHARACTER_H

#include "CommonFunc.h"
#include "BaseObj.h"

class Character : public BaseObj {

    public:

        Character();

        void createChar();

        char getChar();

        void renderCharacter();

    private:

        char c;
        
        bool isExist;


};

class Turtle : public Character {

    public:

        Turtle();
        ~Turtle();
    
    private:

        int xPos;
        int yPos;


};

class Tile : public Character {

    public:

        Tile();
        ~Tile();
    
    private:

        int xPos;
        int yPos;


};

#endif