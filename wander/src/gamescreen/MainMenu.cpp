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

    //Format Title
    this->title.setFontScale(10.0f); //scale
    this->title.setX((float)this->w->getSize().x / 2 - (this->title.getW() / 2)); //x
    this->title.setY((float)this->w->getSize().y * 0.2f); //y
    
    //Format Buttons
    bi.setScale(6.0f);
    bi.setCenteredPositions(true);
    bi.addButton("res//font//jax_n.png", "res//font//jax_h.png", "res//font//jax_c.png", NEW_GAME_ID, 0.5f, 0.5f, "New Game", this->w);
    bi.addButton("res//font//jax_n.png", "res//font//jax_h.png", "res//font//jax_c.png", LOAD_GAME_ID, 0.5f, bi.getNextYF(this->w), "Load Game", this->w);
    bi.addButton("res//font//jax_n.png", "res//font//jax_h.png", "res//font//jax_c.png", SETTINGS_ID, 0.5f, bi.getNextYF(this->w), "Settings", this->w);
    bi.addButton("res//font//jax_n.png", "res//font//jax_h.png", "res//font//jax_c.png", EXIT_ID, 0.5f, bi.getNextYF(this->w), "Exit", this->w);

}

///////////////////////////////////////////////////////////////////
// handle each individual event
///////////////////////////////////////////////////////////////////

void MainMenu::handleEvent(sf::Event e) {
    GScreen::handleEvent(e); //call superclass method first
    
    //switch on event type
    switch (e.type) {
        
        //USER INTERACTS WITH MOUSE
        case sf::Event::MouseButtonPressed: //user presses mouse
        case sf::Event::MouseButtonReleased: //user releases mouse
        case sf::Event::MouseMoved: //user moves mouse
            switch(this->bi.input(this->w, &e)) { //handle any mouse events relating to buttons
                case EXIT_ID: //if exit was pressed
                    this->rd.addC(Node("button pressed", "exit"));
                    this->intentToReturn = true;
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
    
    //World Drawing
    this->bi.illustrate(this->w); //buttons
    this->title.illustrate(this->w); //title
    if (this->showDebug) this->w->draw(*this->d); //draw debug if enabled
    
    this->w->display(); //display new screen
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
