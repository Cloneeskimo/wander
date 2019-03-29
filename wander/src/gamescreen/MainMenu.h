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
    MainMenu(sf::RenderWindow* w, sf::Text* d);
    
protected:
    
    // Protected Data
    GFont jax, jaxH, jaxC;
    GText title;
    ButtonInterface bi;
    
    // Protected Functions
    void handleEvent(sf::Event e); //handle each individual event
    void illustrate(); //illustrate phase
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
