///////////////////////////////////////////////////////////////////
//
//  Entity.cpp
//  wander
//
//  Created by Jacob Oaks on 4/6/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "Entity.h"

///////////////////////////////////////////////////////////////////
// Constructor
// first two and least two parameters follow those of AnimObject's
// first constructor
// also inits this entity to be generic (name, h/maxH, level)
// (@font) is the font to be used for the follow text
///////////////////////////////////////////////////////////////////

Entity::Entity(std::string textureFileName, std::vector<FrameRow> frameRows, Font* font, int startX, int startY) : AnimObject(textureFileName, frameRows, startX, startY), followText(font, "", startX, startY) {
    this->init();
    this->scale(gc::TILE_TEXTURE_SCALE, gc::TILE_TEXTURE_SCALE); //scale texture
    this->followText.setFontScale(3.0f); //scale text
}

///////////////////////////////////////////////////////////////////
// sets the basic entity settings. Parameters are self-explanatory
///////////////////////////////////////////////////////////////////

void Entity::init(std::string name, int health, int maxHealth, int level) {
    this->name = name;
    this->health = health;
    this->maxHealth = maxHealth;
    this->level = level;
    this->followText.setText(name + " (" + std::to_string(level) + ")");
    this->followText.setX(this->getX() + (this->getW() / 2) - (this->followText.getW() / 2));
    this->followText.setY(this->getY() - followText.getH() - 5);
}

///////////////////////////////////////////////////////////////////
// illustrate method
// calls Object's illustrate method and draws any other necessary
// components
///////////////////////////////////////////////////////////////////

void Entity::illustrate(sf::RenderWindow *w) {
    w->draw(this->sprite); //call super
    this->followText.illustrate(w); //illustrate follow text
}

///////////////////////////////////////////////////////////////////
// will move this entity and its following sprites horizontally
// by (@dX)
///////////////////////////////////////////////////////////////////

void Entity::moveX(int dX) {
    this->sprite.move(dX, 0);
    this->followText.moveX(dX);
}

///////////////////////////////////////////////////////////////////
// will move this entity and its following sprites vertically
// by (@dY)
///////////////////////////////////////////////////////////////////

void Entity::moveY(int dY) {
    this->sprite.move(0, dY);
    this->followText.moveY(dY);
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
