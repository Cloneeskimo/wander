//
//  MainMenu.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef MainMenu_h
#define MainMenu_h

#include "GScreen.h"
#include "ButtonInterface.h"

//constants for each button's ID
static const int EXIT_ID = 1;

//GScreen which contains the main menu
class MainMenu : public GScreen {
    
public:
    
    //constructor
    MainMenu(sf::RenderWindow* w, sf::Text* d) : GScreen(w, d) { this->initGOS(); }
    
protected:
    
    //button interface which contains all the main menu buttons
    ButtonInterface bi;
    
    //instance functions
    void initGOS(); //add all GObjects
    void input(); //input phase
    void handleEvent(sf::Event e); //handle each individual event
    void illustrate(); //illustrate phase
};

#endif /* MainMenu_h */
