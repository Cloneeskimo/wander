//
//  MainMenu.cpp
//  wander
//
//  Created by Jacob Oaks on 2/17/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "MainMenu.h"

//add all GObjects
void MainMenu::initGOS() {
    bi.setScale(5.0f);
    bi.addButton("res//buttons//exit.png", EXIT_ID, 0.5f, 0.5f, 1, this->w);
}

//input phase
void MainMenu::input() {
    sf::Event e;
    while (this->w->pollEvent(e)) {
        this->handleEvent(e);
    }
}

//handle each individual event
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
            break;
            
        //USER INTERACTS WITH MOUSE
        case sf::Event::MouseButtonPressed: //user presses mouse
        case sf::Event::MouseButtonReleased: //user releases mouse
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

//illustrate phase
void MainMenu::illustrate() {
    this->w->clear(gc::CLEAR_COLOR); //clear screen
    this->bi.illustrate(this->w);
    if (this->showDebug) this->w->draw(*this->d); //draw debug if enabled
    this->w->display(); //display new screen
}
