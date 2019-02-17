//
//  ButtonInterface.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef ButtonInterface_h
#define ButtonInterface_h

//C++ Includes
#include <vector>

//SFML Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Wander Includes
#include "AnimGObject.h"
#include "Global.h"

//Used to be a collection of buttons for a UI overlay. Spritesheets
//should be given with thier rows formatted as such:
//1 - regular button
//2 - highlighted button
//3 - clicked button
class ButtonInterface {

public:
    
    //adds a button to the interface
    void addButton(std::string textureLocation, int ID, int x, int y, int frameCount);
    void addButton(std::string textureLocation, int ID, float x, float y, int frameCount, sf::RenderWindow* w);
   
    //input/compute/illustrate
    int input(sf::RenderWindow* w, sf::Event* e); //input method
    void compute(float dT);  //compute method
    void illustrate(sf::RenderWindow* w); //illustrate method
    
    //mutators
    void setCenteredPositions(bool ncp) { this->centeredPositions = ncp; }
    void setScale(float ns) { this->scale = ns; }
    
private:
                     
    //determines if mouse is over a button - returns index of button if is, -1 if not
    int mouseHover(int mouseX, int mouseY);
    
    //private member variables
    std::vector<AnimGObject*> buttons; //vector of buttons
    std::vector<int> IDs; //vector of each buttons' corresponding IDs
    bool centeredPositions = true; //represents whether buttons will be added at given positions as if their center is the position, rather than their top-left corner
    float scale = 1.0f; //represents how much the buttons will be scaled in size when added
    
};

#endif /* ButtonInterface_h */
