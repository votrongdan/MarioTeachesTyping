#include "Character.h"

Character::Character() {

    c = '\0';
    isExist = false;
    order = -1;

}

void Character::createChar() {

    c = ('a' + rand() % 26);

}

char Character::getChar() {

    return c;

}

void Character::renderCharacter(int order) {



}

Turtle::Turtle() {


}

Turtle::~Turtle() {

    BaseObj::free();

}

Tile::Tile() {

}

Tile::~Tile() {

    BaseObj::free();

}

