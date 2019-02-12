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

//GObject Includes
#include "gameobject/GObject.hpp"
#include "gameobject/AnimGObject.hpp"
#include "Global.h"

//engine class handles entire game
class Engine {
    
public:
    
    //run function which begins program. called from main.cpp
    int run();
    
private:
    
    //game objects
    AnimGObject* gos[1]; //array which holds all gobjects
    int gosSize = 1; //count variable for gos
    
    //sf objects
    sf::RenderWindow w; //window
    sf::Clock c; //clock used for timekeeping purposes
    sf::Font f; //font used in GUI
    sf::Text debug; //debug text
    
    //game properties
    bool showDebug; //determines whether Engine.debug will be display or not
    int exitStatus; //represents what status the program exits with
    
    //functions
    void init(); //initializes engine
    void input(); //phase 1 of cycle - gather user input
    void compute(); //phase 2 of cycle - update everything
    void illustrate(); //phase 3 of cycle - print to screen
    
};

#endif /* Engine_h */