
//
//  main.cpp
//  wander
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "Global.h"

//constants

//game objects
GameObject* gos[0];
int gosSize = 0;

//function definitions
void input(sf::RenderWindow* w);
void compute();
void illustrate(sf::RenderWindow* w);

//main function
int main(int, char const**)
{
    sf::RenderWindow w(sf::VideoMode(GC::W_WIDTH, GC::W_HEIGHT), GC::W_TITLE, sf::Style::Default); //create window
    
    while (w.isOpen()) { //program loop
    
        input(&w);
        compute();
        illustrate(&w);

    }
    
    return 0;
}

//handles all window input
void input(sf::RenderWindow* w) {
    sf::Event e;
    while (w->pollEvent(e)) {
        
        if (e.type == sf::Event::Closed)
            w->close();
    }
}

//comutes per tick
void compute() {
    
}

//illustrates
void illustrate(sf::RenderWindow* w) {
    
    //clear
    w->clear(sf::Color::Black);
    
    //draw
    for (int i = 0; i < gosSize; i++)
        gos[i]->illustrate(w);
    
    //publish
    w->display();
}
