///////////////////////////////////////////////////////////////////
//
//  ButtonInterface.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

// ERROR CODES USED: 0

#ifndef ButtonInterface_h
#define ButtonInterface_h

// Button State Constants
const int BUTTON_NORMAL = 0;
const int BUTTON_HIGHLIGHT = 1;
const int BUTTON_CLICK = 2;

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
    void addButton(GFont* normalFont, GFont* highlightFont, GFont* clickFont, int ID, int x, int y, std::string text);
    void addButton(GFont* normalFont, GFont* highlightFont, GFont* clickFont, int ID, float x, float y, std::string text, sf::RenderWindow* w);
    
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
    struct Button {
    public:
        
        ///////////////////////////////////////////////////////////////////
        // Constructor
        // (@fsN) - dir for the font sheet to be used for the normal state
        // (@fsH) - dir for the font sheet to be used for the highlighted state
        // (@fsC) - dir for the font sheet to be used for the clicked state
        ///////////////////////////////////////////////////////////////////
        
        Button(GFont* normalFont, GFont* highlightFont, GFont* clickFont, std::string text, int ID, int x, int y) {
            this->normalFont = normalFont;
            this->highlightFont = highlightFont;
            this->clickFont = clickFont;
            this->ID = ID;
            this->text = new GText(normalFont, text, x, y);
        }
        
        // Functions
        
        void setState(int state) {
            if (this->state == state) return;
            this->state = state;
            if (state == BUTTON_NORMAL)
                this->text->setFont(normalFont);
            else if (state == BUTTON_HIGHLIGHT)
                this->text->setFont(highlightFont);
            else if (state == BUTTON_CLICK)
                this->text->setFont(clickFont);
            else
                gf::error("ButtonInterface.h", "Tried to assign an invalid state (" + std::to_string(state) + ") to a button", 0);
        }
        int getState() { return this->state; }
        int getID() { return this->ID; }
        
        // Public Data
        GText* text; //actual text
        
    private:
        
        // Private Data
        GFont* normalFont;
        GFont* highlightFont;
        GFont* clickFont; //GFont references for each three states
        int state = BUTTON_NORMAL; //state of button
        int ID; //id of button
    };
    
    // Private Data
    std::vector<Button*> buttons; //vector of button data
    bool centeredPositions = true; //represents whether buttons will be added at given positions as if their center is the position, rather than their top-left corner
    float scale = 1.0f; //represents how much the buttons will be scaled in size when added
    
    // Private Functions
    int mouseHover(float mouseX, float mouseY);
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
