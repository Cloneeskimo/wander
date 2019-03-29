///////////////////////////////////////////////////////////////////
//
//  StaticTile.cpp
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "StaticTile.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@textureFileName) file directory for tile texture
// (@startX) starting x IN TERMS OF TILES, NOT PIXELS
// (@startY) starting y IN TERMS OF TILES, NOT PIXELs
///////////////////////////////////////////////////////////////////

StaticTile::StaticTile(std::string textureFileName, int startX, int startY) : Object(textureFileName, startX * gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE, startY * gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE) {
    this->scale(gc::TILE_TEXTURE_SCALE, gc::TILE_TEXTURE_SCALE);
}

///////////////////////////////////////////////////////////////////
// will modularize this tile (conform it to its surroundins)
// using the byte (@modularization). Use the byte constants within
// the oto namespace for creation of (@modularization)
///////////////////////////////////////////////////////////////////

void StaticTile::modularize(char modularization) {
    
    //Pre-Calculations
    oto::checkOpaqueTile(); //make sure opaque tile is initialized
    
    //LEFT
    if ((modularization & oto::LEFT) == 0) { //left
        this->texture.update(oto::opaqueColumn);
        if ((modularization & oto::TOP) == 0) //top-left corner
            this->texture.update(oto::opaqueCorner);
    }
    
    //RIGHT
    if ((modularization & oto::RIGHT) == 0) { //right
        this->texture.update(oto::opaqueColumn, oto::getModOffsetConstant(), 0);
        if ((modularization & oto::BOTTOM) == 0) //bottom-right corner
            this->texture.update(oto::opaqueCorner, oto::getModCornerOffsetConstant(), oto::getModCornerOffsetConstant());
    }
    
    //TOP
    if ((modularization & oto::TOP) == 0) { //top
        this->texture.update(oto::opaqueRow);
        if((modularization & oto::RIGHT) == 0) //top-right corner
            this->texture.update(oto::opaqueCorner, oto::getModCornerOffsetConstant(), 0);
    }

    //BOTTOM
    if ((modularization & oto::BOTTOM) == 0) { //bottom
        this->texture.update(oto::opaqueRow, 0, oto::getModOffsetConstant());
        if ((modularization & oto::LEFT) == 0) //bottom-left corner
            this->texture.update(oto::opaqueCorner, 0, oto::getModCornerOffsetConstant());
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
