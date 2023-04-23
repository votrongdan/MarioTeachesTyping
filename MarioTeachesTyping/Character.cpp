#include "Character.h"

Character::Character() {

    c = '\0';
    isExist = false;

}

void Character::createChar() {

    c = ('a' + rand() % 26);

}

char Character::getChar() {

    return c;

}

Turtle::Turtle() {

    xPos = 0;
    yPos = 0;

}

Turtle::~Turtle() {

    BaseObj::free();

}

Tile::Tile() {

    xPos = 0;
    yPos = 0;

}

Tile::~Tile() {

    BaseObj::free();

}

