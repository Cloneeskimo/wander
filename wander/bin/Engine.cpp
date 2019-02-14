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
    this->saveSettings();
    return gc::SUCCESS;
}

//initializes all values/members of engine
void Engine::init() {
    
    //window init
    int w_width = 800, w_height = 600; //window width/height
    this->loadSettings(&w_width, &w_height); //TODO: load width/height from a settings file
    this->w.create(sf::VideoMode(w_width, w_height), gc::W_TITLE, sf::Style::Default); //create window
    this->w.setFramerateLimit(gc::W_FRAMERATE_LIMIT); //limit framerate
    
    //debug text init
    this->f.loadFromFile("res//sansation.ttf"); //load font
    this->debug.setFont(this->f); //set font
    this->debug.setCharacterSize(24); //set text size
    this->debug.setString("FPS"); //set text
    this->debug.setFillColor(sf::Color::Black); //set text color
    this->showDebug = false; //hide debug by default
    
    //misc init
    this->c = sf::Clock(); //create clock
}

//phase 1 - handles all window input
void Engine::input() {
    
    sf::Event e; //event
    while (this->w.pollEvent(e)) { //loop through pending events
        if (e.type == sf::Event::Closed) //closed event
            this->w.close(); //close window
    }
}

//phase 2 - update everything
void Engine::compute() {
    
    //update GameObjects
    for (AnimGObject*o : this->gos)
        o->compute(this->c.getElapsedTime().asSeconds());
    
    //update additionals
    if (this->showDebug) {
        int FPS = 1 / this->c.getElapsedTime().asSeconds();
        this->debug.setString("FPS: " + std::to_string(FPS)); //show debug info
    }
    
    //restart clock
    this->c.restart();
}

//phase 3 - illustrate everything
void Engine::illustrate() {
    
    //clear screen
    this->w.clear(sf::Color::White);
    
    //draw GameObjects
    for (AnimGObject* o : this->gos)
        o->illustrate(&this->w);
    
    //draw additionals
    if (this->showDebug)
        this->w.draw(this->debug);
    
    //publish newly drawn screen
    this->w.display();
}

//loads settings from their file
void Engine::loadSettings(int* w_width, int* w_height) {
    
    //load data if exists
    gf::ensureDir("data");
    if (gf::canOpenFile("data//settings.wdr")) {
        Node settings = sm::loadMasterNode("data//settings.wdr");
        *w_width = std::stoi(settings.getCwN("w_width").getV());
        *w_height = std::stoi(settings.getCwN("w_height").getV());
    }
}

//saves all the current settings to be loaded next time program is run
void Engine::saveSettings() {
    
    //structure data node
    Node settings("settings");
    settings.addC(Node("w_width", std::to_string(this->w.getSize().x)));
    settings.addC(Node("w_height", std::to_string(this->w.getSize().y)));
    
    //save to file
    gf::ensureDir("data");
    sm::saveMasterNode("data//settings.wdr", &settings);
    
}
