//
//  Engine.cpp
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "Engine.h"

//ran by main.cpp. initializes engine and contains main game loop
int Engine::run() {
    
    //iniitialize engine
    this->init();
    
    //program loop
    while (w.isOpen()) { //when window is closed, exit status is returned
        
        this->input(); //phase 1 of cycle - gather input
        this->compute(); //phase 2 of cycle - update everything
        this->illustrate(); //phase 3 of cycle - draw everything
        
    }
    
    //program over
    return this->exitStatus;
}

//initializes all values/members of engine
void Engine::init() {
    
    //window init
    this->w.create(sf::VideoMode(gc::W_WIDTH, gc::W_HEIGHT), gc::W_TITLE, sf::Style::Default); //create window
    this->w.setFramerateLimit(gc::W_FRAMERATE_LIMIT); //limit framerate
    
    //debug text init
    this->f.loadFromFile("res//sansation.ttf"); //load font
    this->debug.setFont(this->f);
    this->debug.setCharacterSize(24);
    this->debug.setString("FPS");
    this->debug.setFillColor(sf::Color::Black);
    this->showDebug = false;
    
    //gobject array init
    this->gos[0] = new AnimGObject("res//dragon.png", 3, 4, 0.1f);
    
    //misc init
    this->exitStatus = gc::SUCCESS; //begin program with success status
    this->c = sf::Clock(); //create clock
}

//phase 1 - handles all window input
void Engine::input() {
    sf::Event e;
    while (this->w.pollEvent(e)) { //loop through pending events
        
        if (e.type == sf::Event::Closed) //closed event
            this->w.close(); //close window
        if (e.type == sf::Event::KeyPressed) {
            switch (e.key.code) {
                case sf::Keyboard::D:
                    this->showDebug = !this->showDebug; //toggle debug display
                    break;
                case sf::Keyboard::Left:
                    this->gos[0]->setFrameRow(2);
                    break;
                case sf::Keyboard::Right:
                    this->gos[0]->setFrameRow(3);
                    break;
                case sf::Keyboard::Down:
                    this->gos[0]->setFrameRow(1);
                    break;
                case sf::Keyboard::Up:
                    this->gos[0]->setFrameRow(4);
                    break;
                default:
                    break;
            }
        }
    }
}

//phase 2 - update everything
void Engine::compute() {
    
    //update GameObjects
    for (int i = 0; i < gosSize; i++)
        this->gos[i]->compute(this->c.getElapsedTime().asSeconds());
    
    //update additionals
    if (this->showDebug) {
        int FPS = 1 / this->c.getElapsedTime().asSeconds();
        this->debug.setString("FPS: " + std::to_string(FPS));
    }
    
    //restart clock
    this->c.restart();
}

//phase 3 - illustrate everything
void Engine::illustrate() {
    
    //clear screen
    this->w.clear(sf::Color::White);
    
    //draw GameObjects
    for (int i = 0; i < gosSize; i++)
        this->gos[i]->illustrate(&this->w);
    
    //draw additionals
    if (this->showDebug)
        this->w.draw(this->debug);
    
    //publish newly drawn screen
    this->w.display();
}
