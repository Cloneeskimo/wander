///////////////////////////////////////////////////////////////////
//
//  GameScreen.h
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef GameScreen_h
#define GameScreen_h

// Includes

#include <vector>
#include "Screen.h"
#include "Map.h"
#include "Entity.h"

///////////////////////////////////////////////////////////////////
// GameScreen Class
// Screen for the in-game state
///////////////////////////////////////////////////////////////////

class GameScreen : public Screen {
public:
    
    // Constructor
    GameScreen(sf::RenderWindow* w, Text* d);
    
private:
    
    // Data
    Map currentMap; //map currently being displayed
    std::vector<Entity*> entities; //entities currently being considered
    
    // Private Functions
    void compute();
    void illustrate(); //overriden illustrate
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
