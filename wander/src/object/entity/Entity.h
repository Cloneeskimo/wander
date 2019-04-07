///////////////////////////////////////////////////////////////////
//
//  Entity.h
//  wander
//
//  Created by Jacob Oaks on 4/6/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Entity_h
#define Entity_h

// Includes

#include <string>
#include <SFML/Graphics.hpp>
#include "AnimObject.h"
#include "Text.h"
#include "Font.h"

///////////////////////////////////////////////////////////////////
// Entity Class
// Represents any entity in the game
///////////////////////////////////////////////////////////////////

class Entity : public AnimObject {
public:
    
    // Constructor
    Entity(std::string textureFileName, std::vector<FrameRow> frameRows, Font* font, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y);
    
    // Initializer
    void init(std::string name = "(Unnamed)", int health = 10, int maxHealth = 10, int level = 1);
    
    // Accessors
    std::string getName() { return this->name; } //returns entity name
    int getHealth() { return this->health; } //returns entity health
    int getMaxHealth() { return this->maxHealth; } //returns entity max health
    int getLevel() { return this->level; } //returns entity level
    
    // Other Functions
    void illustrate(sf::RenderWindow* w); //illustrate this entity
    void moveX(int dX); //move the entity by (@dX)
    void moveY(int dY); //move the entity by (@dY)
    
private:
    
    // Private Data
    Text followText;
    std::string name;
    int health, maxHealth;
    int level;
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
