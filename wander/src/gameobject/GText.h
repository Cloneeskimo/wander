///////////////////////////////////////////////////////////////////
//
//  GText.h
//  wander
//
//  Created by Jacob Oaks on 3/22/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef GText_h
#define GText_h

// Includes
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GObject.h"

///////////////////////////////////////////////////////////////////
// GText Class
// A class which can represent text on the screen using a custom font
///////////////////////////////////////////////////////////////////

class GText {
public:
    
    // Constructor
    GText(std::string fontDir, std::string text, int x, int y); //constructor
    
    // Accessors
    int getX() { return this->x; } //gets x
    int getY() { return this->y; } //gets y
    int getW() { return this->lW * this->l.size() * this->fScale; } //get the width of the button
    int getH() { return this->lH * this->fScale; } //gets the height of the button
    sf::IntRect getRect() { return sf::IntRect(this->x, this->y, this->getW(), this->getH()); } //get rect of button
    
    // Mutators
    void setText(std::string t); //sets the text
    void setFontScale(float fs); //sets the scale of the text
    void setFont(std::string fontDir); //sets the font
    void setX(int x) { this->x = x; refreshLetters(); } //sets x
    void setY(int y) { this->y = y; refreshLetters(); } //sets y
    
    // Other Public Methods
    void illustrate(sf::RenderWindow* w); //illustrate method
    
private:
    
    // Private Methods
    void parseFontSheet(); //figures out the width and length of each letter in the font sheet
    void refreshLetters(); //refreshes the sizes/placement of the letters
    
    // Static Methods
    static void getCharacterPos(int* x, int* y, char c);
    
    // Private Data
    int x, y;
    int lW, lH; //letter width & height in fS
    float fScale = 1.0f;
    sf::Texture fSheet;
    std::vector<sf::Sprite> l; //sprites for each letter

};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
