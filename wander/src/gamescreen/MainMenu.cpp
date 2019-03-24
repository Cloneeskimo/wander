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
    
    std::vector<FrameRow> ghostFrs;
    ghostFrs.push_back(FrameRow(2, 0.33f));
    ghostFrs.push_back(FrameRow(16, 0.06f));
    ghostFrs.push_back(FrameRow(12, 0.13f));
    this->gos.push_back(new AnimGObject("res//ghost.png", ghostFrs, 100, 100));
    this->gos.at(0)->scale(9.0, 9.0);
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
            
        //USER RELEASES A KEY
        case sf::Event::KeyReleased:
            if (e.key.code == gc::DEBUG_KEY)
                this->showDebug = !this->showDebug;
            else if (e.key.code == sf::Keyboard::T)
                this->gos.at(0)->setFrameRow(1);
            else if (e.key.code == sf::Keyboard::Y)
                this->gos.at(0)->setFrameRow(2);
            else if (e.key.code == sf::Keyboard::U)
                this->gos.at(0)->setFrameRow(3);
        break;
        
        //USER INTERACTS WITH MOUSE
        case sf::Event::MouseButtonPressed: //user presses mouse
        case sf::Event::MouseButtonReleased: //user releases mouse
        case sf::Event::MouseMoved: //user moves mouse
            switch(this->bi.input(this->w, &e)) { //handle any mouse events relating to buttons
                case NEW_GAME_ID: //if new game was pressed
                    this->rd.addC(Node("button pressed", "new game"));
                    this->intentToReturn = true;
                case LOAD_GAME_ID: //if load game was pressed
                    this->rd.addC(Node("button pressed", "load game"));
                    this->intentToReturn = true;
                case SETTINGS_ID: //if settings was pressed
                    this->rd.addC(Node("button pressed", "settings"));
                    this->intentToReturn = true;
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
    
    this->bi.illustrate(this->w);
    if (this->showDebug) this->w->draw(*this->d); //draw debug if enabled
    this->gos.at(0)->illustrate(w);
    
    this->w->display(); //display new screen
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
