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
#include "GameObject.hpp"
#include "Global.h"

class Engine {
    
public:
    
    int run();
    
private:
    
    //game objects
    GameObject* gos[0];
    int gosSize = 0;
    
    //window
    sf::RenderWindow w;
    
    void input(sf::RenderWindow* w);
    void compute();
    void illustrate(sf::RenderWindow* w);
    
};

#endif /* Engine_h */
