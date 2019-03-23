///////////////////////////////////////////////////////////////////
//
//  Engine.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Engine_h
#define Engine_h

// Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gamescreen/MainMenu.h"
#include "Global.h"
#include "SaveManager.h"

///////////////////////////////////////////////////////////////////
// Engine Class
// handles entire game
///////////////////////////////////////////////////////////////////

class Engine {
public:
    
    // Initializer
    int run(); //run function, called to initialize and run game

private:
    
    // SFML Objects
    sf::RenderWindow w; //window
    sf::Font f; //font used in GUI
    sf::Text d; //debug text
    
    // Private Functions
    void initWindow(); //creates window
    void initDebug(); //inits debug text
    void loadSettings(int* w_width, int* w_height); //loads previously saved settings from file
    void saveSettings(); //saves settings to file
    
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
