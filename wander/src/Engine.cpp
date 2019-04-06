///////////////////////////////////////////////////////////////////
//
//  Engine.cpp
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "Engine.h"

///////////////////////////////////////////////////////////////////
// ran by main.cpp. initializes engine and contains main game loop
///////////////////////////////////////////////////////////////////

int Engine::run() {
    
    //initialize window
    this->initWindow();
    this->d.setFontScale(4.0f);
    
    //program loop
    while (this->w.isOpen()) { //when window is closed, exit status is returned
        
        //show main menu, get button pressed
        MainMenu mm(&this->w, &this->d);
        Node mmData = mm.enter();
        std::string buttonPressed = mmData.getCwN("button pressed")->getV();
        
        //exit
        if (buttonPressed == "exit") this->w.close();
        
        //load game
        if (buttonPressed == "load game") {
            GameScreen gs(&this->w, &this->d); //show gamescreen
            Node gsData = gs.enter(); //get gamescreen data
        }
    }
    
    //program over
    this->saveSettings();
    return gc::SUCCESS;
}

///////////////////////////////////////////////////////////////////
// initializes the window
///////////////////////////////////////////////////////////////////

void Engine::initWindow() {
    
    //window init
    int w_width = 800, w_height = 600; //window width/height
    this->loadSettings(&w_width, &w_height); //TODO: load width/height from a settings file
    this->w.create(sf::VideoMode(w_width, w_height), gc::W_TITLE, sf::Style::Default); //create window
    this->w.setFramerateLimit(gc::W_FRAMERATE_LIMIT); //limit framerate
}

///////////////////////////////////////////////////////////////////
// loads settings from their file
// (@w_width) gets set to the loaded window width
// (@w_height) gets set to the loaded window height
///////////////////////////////////////////////////////////////////

void Engine::loadSettings(int* w_width, int* w_height) {
    
    //load data if exists
    gf::ensureDir("data");
    if (gf::canOpenFile("data//settings.wdr")) {
        Node settings = SaveManager::loadMasterNode("data//settings.wdr");
        *w_width = std::stoi(settings.getCwN("w_width")->getV());
        *w_height = std::stoi(settings.getCwN("w_height")->getV());
    }
}

///////////////////////////////////////////////////////////////////
// saves all the current settings to be loaded next time program is run
///////////////////////////////////////////////////////////////////

void Engine::saveSettings() {
    
    //structure data node
    Node settings("settings");
    settings.addC(Node("w_width", std::to_string(this->w.getSize().x)));
    settings.addC(Node("w_height", std::to_string(this->w.getSize().y)));
    
    //save to file
    gf::ensureDir("data");
    SaveManager::saveMasterNode("data//settings.wdr", &settings);
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
