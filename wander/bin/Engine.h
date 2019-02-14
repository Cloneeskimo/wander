//
//  Engine.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

//C++ Includes
#include <vector>

//SFML Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Wander Includes
#include "gameobject/GObject.h"
#include "gameobject/AnimGObject.h"
#include "Global.h"
#include "SaveManager.h"

//engine class handles entire game
class Engine {
    
public:
    
    //run function which begins program. called from main.cpp
    int run();
    
private:
    
    //game objects
    std::vector<AnimGObject*> gos; //array which holds all gobjects
    
    //sf objects
    sf::RenderWindow w; //window
    sf::Clock c; //clock used for timekeeping purposes
    sf::Font f; //font used in GUI
    sf::Text debug; //debug text
    
    //game properties
    bool showDebug; //determines whether Engine.debug will be display or not
    
    //functions
    void init(); //initializes engine
    void input(); //phase 1 of cycle - gather user input
    void compute(); //phase 2 of cycle - update everything
    void illustrate(); //phase 3 of cycle - print to screen
    
    //settings
    void loadSettings(int* w_width, int* w_height); //loads previously saved settings from file
    void saveSettings(); //saves settings to file
    
    //controls states
    bool KeyLeft = false;
    bool KeyRight = false;
    bool KeyUp = false;
    bool KeyDown = false;
};

#endif /* Engine_h */
