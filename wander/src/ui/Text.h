///////////////////////////////////////////////////////////////////
//
//  Text.h
//  wander
//
//  Created by Jacob Oaks on 3/22/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Text_h
#define Text_h

// Includes
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Font.h"

///////////////////////////////////////////////////////////////////
// Text Class
// A class which can represent text on the screen using a custom font
///////////////////////////////////////////////////////////////////

class Text {
public:
    
    // Constructor
    Text(Font* font, std::string text, int x, int y); //constructor
    
    // Accessors
    int getX() { return this->x; } //gets x
    int getY() { return this->y; } //gets y
    int getW() { return this->font->getLetterWidth() * this->letters.size() * this->fontScale; } //get the width of the button
    int getH() { return this->font->getLetterHeight() * this->fontScale; } //gets the height of the button
    sf::IntRect getRect() { return sf::IntRect(this->x, this->y, this->getW(), this->getH()); } //get rect of button
    
    // Mutators
    void setText(std::string t, bool ignoreSpaces = true); //sets the text
    void setFontScale(float fs); //sets the scale of the text
    void setFont(Font* f); //sets the font
    void setX(int x) { this->x = x; refreshLetters(); } //sets x
    void setY(int y) { this->y = y; refreshLetters(); } //sets y
    
    // Other Public Methods
    void illustrate(sf::RenderWindow* w); //illustrate method
    
private:
    
    // Private Methods
    void refreshLetters(); //refreshes the sizes/placement of the letters
    
    // Private Data
    int x, y; //position
    float fontScale = 1.0f; //scale
    std::string text;
    sf::Texture* fontSheet; //pointer to the font's sheet
    std::vector<sf::Sprite> letters; //sprites for each letter
    Font* font; //reference to the text's font
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
