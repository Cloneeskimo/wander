//
//  Engine.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

//SFML Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Wander Includes
#include "gamescreen/MainMenu.h"
#include "Global.h"
#include "SaveManager.h"

//engine class handles entire game
class Engine {
    
public:
    
    //run function which begins program. called from main.cpp
    int run();
    
private:
    
    //sf objects
    sf::RenderWindow w; //window
    sf::Font f; //font used in GUI
    sf::Text d; //debug text
    
    //init functions
    void initWindow(); //creates window
    void initDebug(); //inits debug text
    
    //settings
    void loadSettings(int* w_width, int* w_height); //loads previously saved settings from file
    void saveSettings(); //saves settings to file
};

#endif /* Engine_h */
