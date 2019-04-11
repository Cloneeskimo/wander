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
    
    //Map Initialization
    this->currentMap = Map("test", "data//maps//test_map.wdr", this->w);
    this->worldV.setCenter(this->currentMap.getW() / 2, this->currentMap.getH() / 2);
    
    //Player Initialization
    std::vector<FrameRow> frs;
    frs.push_back(FrameRow(2, 0.2));
    frs.push_back(FrameRow(16, 0.2));
    frs.push_back(FrameRow(12, 0.2));
    this->player = new Player("res//entity//ghost.png", frs, this->d->getFont(), gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE * 4, gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE * 2);
    this->player->init("Player");
    this->worldV.setCenter(this->player->getX(), this->player->getY());
}

///////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////

void GameScreen::compute() {
    
    //call super
    Screen::compute();
    bool updateCam = false;
    
    //check for movement
    if (sf::Keyboard::isKeyPressed(control::moveLeft)) {
        this->player->moveX(-4);
        updateCam = true;
    }
    
    if (sf::Keyboard::isKeyPressed(control::moveRight)) {
        this->player->moveX(4);
        updateCam = true;
    }
    
    if (sf::Keyboard::isKeyPressed(control::moveUp)) {
        this->player->moveY(-4);
        updateCam = true;
    }
    
    if (sf::Keyboard::isKeyPressed(control::moveDown)) {
        this->player->moveY(4);
        updateCam = true;
    }
    
    if (updateCam) this->worldV.setCenter(this->player->getX(), this->player->getY());
    
    //compute entities
    for (Entity* e : this->entities) e->compute(this->c.getElapsedTime().asSeconds()); //entities
    this->player->compute(this->c.getElapsedTime().asSeconds()); //player
}

///////////////////////////////////////////////////////////////////
// Illustrate Function
///////////////////////////////////////////////////////////////////

void GameScreen::illustrate() {
    
    //clear screen
    this->w->clear(gc::CLEAR_COLOR);
    
    //draw world
    this->currentMap.illustrate(); //illustrate the map
    for (Entity* e : this->entities) e->illustrate(w); //illustrate the entities
    this->player->illustrate(w); //illustrate the player
    
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
