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
    
    //iniitialize window
    this->initWindow();
    this->initDebug();
    
    //program loop
    while (this->w.isOpen()) { //when window is closed, exit status is returned
        
        //continue showing main menu as base screen until window closed
        MainMenu mm(&this->w, &this->d);
        mm.enter();
        
    }
    
    //program over
    this->saveSettings();
    return gc::SUCCESS;
}

//initializes all values/members of engine
void Engine::initWindow() {
    
    //window init
    int w_width = 800, w_height = 600; //window width/height
    this->loadSettings(&w_width, &w_height); //TODO: load width/height from a settings file
    this->w.create(sf::VideoMode(w_width, w_height), gc::W_TITLE, sf::Style::Default); //create window
    this->w.setFramerateLimit(gc::W_FRAMERATE_LIMIT); //limit framerate
}

//initializes the font and debug text
void Engine::initDebug() {
    
    //debug text init
    this->f.loadFromFile("res//sansation.ttf"); //load font
    this->d.setFont(this->f); //set font
    this->d.setCharacterSize(24); //set text size
    this->d.setString("FPS"); //set text
    this->d.setFillColor(sf::Color::Black); //set text color
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