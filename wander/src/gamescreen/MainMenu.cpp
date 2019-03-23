///////////////////////////////////////////////////////////////////
//
//  MainMenu.cpp
//  wander
//
//  Created by Jacob Oaks on 2/17/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "MainMenu.h"

///////////////////////////////////////////////////////////////////
// adds all GObjects
///////////////////////////////////////////////////////////////////

void MainMenu::initGOS() {
    bi.setScale(2.5f);
    bi.setCenteredPositions(true);
    bi.addButton("res//font//button_n.png", "res//font//button_h.png", "res//font//button_n.png", NEW_GAME_ID, 0.5f, 0.4f, "New Game", this->w);
    bi.addButton("res//font//button_n.png", "res//font//button_h.png", "res//font//button_n.png", LOAD_GAME_ID, 0.5f, bi.getNextYF(this->w), "Load Game", this->w);
    bi.addButton("res//font//button_n.png", "res//font//button_h.png", "res//font//button_n.png", SETTINGS_ID, 0.5f, bi.getNextYF(this->w), "Settings", this->w);
    bi.addButton("res//font//button_n.png", "res//font//button_h.png", "res//font//button_n.png", EXIT_ID, 0.5f, bi.getNextYF(this->w), "Exit", this->w);
}

///////////////////////////////////////////////////////////////////
// input phase
///////////////////////////////////////////////////////////////////

void MainMenu::input() {
    sf::Event e;
    while (this->w->pollEvent(e)) {
        this->handleEvent(e);
    }
}

///////////////////////////////////////////////////////////////////
// handle each individual event
///////////////////////////////////////////////////////////////////

void MainMenu::handleEvent(sf::Event e) {
    switch (e.type) {
            
        //USER CLOSES WINDOW
        case sf::Event::Closed:
            this->w->close();
            break;
            
        //USER INTERACTS WITH MOUSE
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        case sf::Event::MouseMoved: //user moves mouse
            switch(this->bi.input(this->w, &e)) { //handle any mouse events relating to buttons
                case EXIT_ID: //if exit was pressed
                    this->w->close();
                default:
                    break;
            }
            break;
            
        //ANYTHING ELSE
        default:
            break;
    }
}

///////////////////////////////////////////////////////////////////
// illustrate phase
///////////////////////////////////////////////////////////////////

void MainMenu::illustrate() {
    this->w->clear(gc::CLEAR_COLOR); //clear screen
    
    this->bi.illustrate(this->w);
    if (this->showDebug) this->w->draw(*this->d); //draw debug if enabled
    
    this->w->display(); //display new screen
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
