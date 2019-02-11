//
//  Engine.cpp
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "Engine.h"

int Engine::run() {
    
    this->w.create(sf::VideoMode(gc::W_WIDTH, gc::W_HEIGHT), gc::W_TITLE, sf::Style::Default); //create window
    
    while (w.isOpen()) { //program loop
        
        this->input(&w);
        this->compute();
        this->illustrate(&w);
        
    }
    
    return gc::SUCCESS;
}

//handles all window input
void Engine::input(sf::RenderWindow* w) {
    sf::Event e;
    while (this->w.pollEvent(e)) {
        
        if (e.type == sf::Event::Closed)
            this->w.close();
    }
}

//computes per tick
void Engine::compute() {
    
}

//illustrates
void Engine::illustrate(sf::RenderWindow* w) {
    
    //clear
    this->w.clear(sf::Color::Black);
    
    //draw
    for (int i = 0; i < gosSize; i++)
        this->gos[i]->illustrate(w);
    
    //publish
    this->w.display();
}
