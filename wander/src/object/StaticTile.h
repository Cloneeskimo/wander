///////////////////////////////////////////////////////////////////
//
//  StaticTile.h
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef StaticTile_h
#define StaticTile_h

// Includes

#include "AnimObject.h"
#include "Global.h"

///////////////////////////////////////////////////////////////////
// StaticTile Class
// used for an individual tile without animations and without movement
///////////////////////////////////////////////////////////////////

class StaticTile : public Object {
public:
    
    // Constructor
    StaticTile(std::string textureFileName, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y);
    
    // Accessors
    int getMapX() { return this->getX() * gc::TILE_SIZE; }
    int getMapY() { return this->getY() * gc::TILE_SIZE; }
    
    // Mutators
    void modularize(char modularization);
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
