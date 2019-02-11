//
//  Engine.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef Engine_h
#define Engine_h

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "gameobject/GameObject.hpp"
#include "gameobject/AnimatableGameObject.hpp"
#include "Global.h"

class Engine {
    
public:
    
    //run function which begins program
    int run();
    
private:
    
    //game objects
    AnimatableGameObject* gos[1];
    int gosSize = 1;
    
    //sf objects
    sf::RenderWindow w;
    sf::Clock c;
    sf::Font f;
    sf::Text debug;
    
    //game settings
    bool showDebug;
    
    //functions
    void init();
    void input();
    void compute();
    void illustrate();
    
};

#endif /* Engine_h */
