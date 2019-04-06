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
#include "Global.h"
#include "SaveManager.h"
#include "screen/MainMenu.h"
#include "screen/GameScreen.h"
#include "ui/Font.h"

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
    Font df = Font("res//font//commo.png", "res//font//commo.wdr"); //default font used in gui
    Text d = Text(&this->df, "FPS: ", 5, 5); //debug text

    
    // Private Functions
    void initWindow(); //creates window
    void loadSettings(int* w_width, int* w_height); //loads previously saved settings from file
    void saveSettings(); //saves settings to file
    
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
