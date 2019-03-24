///////////////////////////////////////////////////////////////////
//
//  MainMenu.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef MainMenu_h
#define MainMenu_h

// Includes
#include "GScreen.h"
#include "GText.h"
#include "ButtonInterface.h"

// Button ID Constants
static const int NEW_GAME_ID = 1;
static const int LOAD_GAME_ID = 2;
static const int SETTINGS_ID = 3;
static const int EXIT_ID = 4;

///////////////////////////////////////////////////////////////////
// MainMenu Class
// GScreen which contains the main menu interface
///////////////////////////////////////////////////////////////////

class MainMenu : public GScreen {
public:
    
    //Constructor
    MainMenu(sf::RenderWindow* w, sf::Text* d) : GScreen(w, d) { this->initGOS(); }
    
protected:
    
    // Protected Data
    ButtonInterface bi;
    GText title = GText("res//font//jax_n.png", "Wander", 0, 0);
    
    // Protected Functions
    void initGOS(); //add all GObjects
    void input(); //input phase
    void handleEvent(sf::Event e); //handle each individual event
    void illustrate(); //illustrate phase
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
