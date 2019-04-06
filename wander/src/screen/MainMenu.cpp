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
// Constructor
// Initializes main menu on (@w) and stores the debug text reference
// (@d)
///////////////////////////////////////;///////////////////////////

MainMenu::MainMenu(sf::RenderWindow* w, Text* d) : Screen(w, d), jax("res//font//jax_n.png", "res//font//jax.wdr"), jaxH("res//font//jax_h.png", "res//font//jax.wdr"), jaxC("res//font//jax_c.png", "res//font//jax.wdr"), title(&jax, "Wander", 0, 0) {
    
    //Format Title
    this->title.setFontScale(10.0f); //scale
    this->title.setX((float)this->w->getSize().x / 2 - (this->title.getW() / 2)); //x
    this->title.setY((float)this->w->getSize().y * 0.2f); //y
    
    //Format Buttons
    bi.setScale(6.0f);
    bi.setCenteredPositions(true);
    bi.addButton(&this->jax, &this->jaxH, &this->jaxC, NEW_GAME_ID, 0.5f, 0.5f, "New Game", this->w);
    bi.addButton(&this->jax, &this->jaxH, &this->jaxC, LOAD_GAME_ID, 0.5f, bi.getNextYF(this->w), "Load Game", this->w);
    bi.addButton(&this->jax, &this->jaxH, &this->jaxC, SETTINGS_ID, 0.5f, bi.getNextYF(this->w), "Settings", this->w);
    bi.addButton(&this->jax, &this->jaxH, &this->jaxC, EXIT_ID, 0.5f, bi.getNextYF(this->w), "Exit", this->w);

}

///////////////////////////////////////////////////////////////////
// handle each individual event
///////////////////////////////////////////////////////////////////

void MainMenu::handleEvent(sf::Event e) {
    Screen::handleEvent(e); //call superclass method first
    
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
                case LOAD_GAME_ID: //if load game was pressed
                    this->rd.addC(Node("button pressed", "load game"));
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
    
    //clear screen
    this->w->clear(gc::CLEAR_COLOR); //clear
    
    //draw world
    this->bi.illustrate(this->w); //buttons
    this->title.illustrate(this->w); //title
    
    //draw UI
    this->w->setView(this->uiV); //set to UI view
    if (this->showDebug) this->d->illustrate(this->w); //draw debug
    
    //display
    this->w->setView(this->worldV); //set back to world view
    this->w->display(); //display new screen
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
