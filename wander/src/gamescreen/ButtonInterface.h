///////////////////////////////////////////////////////////////////
//
//  ButtonInterface.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef ButtonInterface_h
#define ButtonInterface_h

// Includes
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GText.h"
#include "Global.h"

///////////////////////////////////////////////////////////////////
// ButtonInterface Class
// Used to be a collection of buttons for a UI overlay
// Uses GText to make buttons out of text
///////////////////////////////////////////////////////////////////

class ButtonInterface {

public:
    
    // Button Adding Functions
    void addButton(std::string fsN, std::string fsH, std::string fsC, int ID, int x, int y, std::string text);
    void addButton(std::string fsN, std::string fsH, std::string fsC, int ID, float x, float y, std::string text, sf::RenderWindow* w);
    
    // Input/Compute/Illustrate Functions
    int input(sf::RenderWindow* w, sf::Event* e); //input method
    void compute(float dT);  //compute method
    void illustrate(sf::RenderWindow* w); //illustrate method
    
    // Mutators
    void setCenteredPositions(bool ncp) { this->centeredPositions = ncp; }
    void setScale(float ns) { this->scale = ns; }
    
    // Accessors
    int getNextX(int space = 20, bool toRight = true); //returns the x value to place a new button
    int getNextY(int space = 20, bool below = true); //returns the y value to place a new button to the right of to the previous one
    float getNextXF(sf::RenderWindow* w, int space = 20, bool toRight = true); //returns the x value to place a new button as a fraction of the screen width
    float getNextYF(sf::RenderWindow* w, int space = 20, bool below = true); //returns the y value to place a new button as a fraction of the screen height

private:
    
    // Private FontBundle struct to store the fonts of each of the buttons
    struct ButtonData {
    public:
        
        ///////////////////////////////////////////////////////////////////
        // Constructor
        // (@fsN) - dir for the font sheet to be used for the normal state
        // (@fsH) - dir for the font sheet to be used for the highlighted state
        // (@fsC) - dir for the font sheet to be used for the clicked state
        ///////////////////////////////////////////////////////////////////
        
        ButtonData(std::string fsN, std::string fsH, std::string fsC) {
            this->fsN = fsN;
            this->fsH = fsH;
            this->fsC = fsC;
        }
        
        // Data
        std::string fsN, fsH, fsC; //strings for normal, highlighted, and clicked states
        int state = 0;
    };
    
    // Private Data
    std::vector<GText*> bs; //vector of buttons
    std::vector<ButtonData*> bds; //vector of button data
    std::vector<int> IDs; //vector of each buttons' corresponding IDs
    bool centeredPositions = true; //represents whether buttons will be added at given positions as if their center is the position, rather than their top-left corner
    float scale = 1.0f; //represents how much the buttons will be scaled in size when added
    
    // Private Functions
    int mouseHover(float mouseX, float mouseY);
    void ensureButtonState(int i, int state);

};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
