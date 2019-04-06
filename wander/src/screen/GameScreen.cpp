///////////////////////////////////////////////////////////////////
//
//  GameScreen.cpp
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "GameScreen.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@w) - what to set the window reference to
// (@d) - reference to the debug info
///////////////////////////////////////////////////////////////////

GameScreen::GameScreen(sf::RenderWindow* w, Text* d) : Screen(w, d) {
    this->currentMap = Map("test", "data//maps//test_map.wdr", this->w);
}

///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////

void GameScreen::compute() {
    Screen::compute(); //call super
    
    //check for movement
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->worldV.move(-4, 0);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->worldV.move(4, 0);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        this->worldV.move(0, -4);
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        this->worldV.move(0, 4);
    }
    
}

///////////////////////////////////////////////////////////////////
// Illustrate Function
///////////////////////////////////////////////////////////////////

void GameScreen::illustrate() {
    
    //clear screen
    this->w->clear(gc::CLEAR_COLOR);
    
    //draw world
    this->currentMap.illustrate(); //illustrate the map
    
    //draw UI
    this->w->setView(this->uiV); //set to ui view
    if (this->showDebug) this->d->illustrate(this->w); //draw debug
    
    //display
    this->w->setView(this->worldV); //reset to world view
    this->w->display(); //display new screen
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
