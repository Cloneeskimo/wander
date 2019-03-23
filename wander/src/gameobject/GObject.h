///////////////////////////////////////////////////////////////////
//
//  GObject.h
//  wander
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

//ERROR CODES USED: 0

#ifndef GameObject_h
#define GameObject_h

// Includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"

///////////////////////////////////////////////////////////////////
// GObject Class
// a generic class for any game object. contains a sprite and a position.
///////////////////////////////////////////////////////////////////

class GObject {
    
protected:
    
    // Protected Data
    sf::Sprite sprite; //object sprite
    sf::Texture texture; //texture owned by the sprite
    
public:
    
    ///////////////////////////////////////////////////////////////////
    // Constructor
    // (@textureFileName) - location & name of texture file relative to working directory
    // (@startX) - starting object x (has default value defined in Global.h)
    // (@startY) - starting object y (has default value defined in Global.h)
    ///////////////////////////////////////////////////////////////////
    
    GObject(std::string textureFileName, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y) {
        if(!this->texture.loadFromFile(textureFileName)) //attempt to load texture
            gf::error("GObject.h", "'" + textureFileName + "' could not be loaded", 0, gc::FAILURE_BY_FILEIO, true); //throw error if file could not be loaded
        this->sprite = sf::Sprite(this->texture); //initialize sprite
        this->sprite.setPosition(startX, startY); //set sprite starting position
    };
    
    // Public Functions
    void illustrate(sf::RenderWindow *w) { w->draw(this->sprite); } //illustrate method just draws the sprite
    void compute(float dT) {}; //written to be overriden by inherited classes
    void scale(float x, float y) { this->sprite.setScale(x, y); } //scale the sprite
    
    // Accessors
    int getX() { return this->sprite.getPosition().x; }
    int getY() { return this->sprite.getPosition().y; }
    sf::Vector2f getPos() { return this->sprite.getPosition(); }
    int getW() { return this->sprite.getGlobalBounds().width; }
    int getH() { return this->sprite.getGlobalBounds().height; }
    sf::Vector2i getSize() { return sf::Vector2i(this->getW(), this->getH()); }
    sf::IntRect getRect() { return sf::IntRect(this->getX(), this->getY(), this->getW(), this->getH()); }
    
    // Mutators
    void setX(int newX) { this->sprite.setPosition(newX, this->sprite.getPosition().y); }
    void setY(int newY) { this->sprite.setPosition(this->sprite.getPosition().x, newY); }
    void setPos(sf::Vector2f newPos) { this->sprite.setPosition(newPos); }
    void setPos(int newX, int newY) { this->setPos(sf::Vector2f(newX, newY)); }
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
