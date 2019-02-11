//
//  Engine.cpp
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "Engine.h"

int Engine::run() {
    
    //iniitialize engine
    this->init();
    
    //program loop
    while (w.isOpen()) {
        
        this->input();
        this->compute();
        this->illustrate();
        
    }
    
    //program over
    return gc::SUCCESS;
}

void Engine::init() {
    
    //create sf objects
    this->w.create(sf::VideoMode(gc::W_WIDTH, gc::W_HEIGHT), gc::W_TITLE, sf::Style::Default);
    this->w.setFramerateLimit(gc::W_FRAMERATE_LIMIT);
    this->c = sf::Clock();
    this->f.loadFromFile("res//sansation.ttf");
    this->debug.setFont(this->f);
    this->debug.setCharacterSize(24);
    this->debug.setString("FPS");
    this->debug.setFillColor(sf::Color::Black);
    
    //create GameObject array
    this->gos[0] = new AnimatableGameObject("res//dragonTop.png", 3, 0.2f);
    
    //set settings
    this->showDebug = false;
}

//handles all window input
void Engine::input() {
    sf::Event e;
    while (this->w.pollEvent(e)) {
        
        if (e.type == sf::Event::Closed)
            this->w.close();
        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Space)
            this->showDebug = !this->showDebug;
    }
}

//computes per tick
void Engine::compute() {
    
    //compute GameObjects
    for (int i = 0; i < gosSize; i++)
        this->gos[i]->compute(this->c.getElapsedTime().asSeconds());
    
    //compute additionals
    if (this->showDebug) {
        int FPS = 1 / this->c.getElapsedTime().asSeconds();
        this->debug.setString("FPS: " + std::to_string(FPS));
    }
    
    //restart clock
    this->c.restart();
}

//illustrates
void Engine::illustrate() {
    
    //clear
    this->w.clear(sf::Color::White);
    
    //draw GameObjects
    for (int i = 0; i < gosSize; i++)
        this->gos[i]->illustrate(&this->w);
    
    //draw additionals
    if (this->showDebug)
        this->w.draw(this->debug);
    
    //publish
    this->w.display();
}
