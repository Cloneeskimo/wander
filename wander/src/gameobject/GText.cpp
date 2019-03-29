///////////////////////////////////////////////////////////////////
//
//  GText.cpp
//  wander
//
//  Created by Jacob Oaks on 3/22/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "GText.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@font) - reference to the GFont to use
// (@text) - starting text
// (@x) - x position of text
// (@y) - y position of text
///////////////////////////////////////////////////////////////////

GText::GText(GFont* font, std::string text, int x, int y) {
    this->setFont(font);
    this->text = text;
    this->x = x;
    this->y = y;
    this->setText(text);
}

///////////////////////////////////////////////////////////////////
// sets the text to (@t)
///////////////////////////////////////////////////////////////////

void GText::setText(std::string t) {
    this->text = t;
    this->letters = std::vector<sf::Sprite>(); //remove previous letter
    for (char c : t) { //loop through each character of t
        
        sf::IntRect bounds = this->font->getBounds(c); //get bounds on font sheet for character
        sf::Sprite nextLetter(*this->fontSheet); //create character sprite
        nextLetter.setTextureRect(bounds); //set bounds
        nextLetter.setScale(this->fontScale, this->fontScale); //set scale
        nextLetter.setPosition(this->x + (this->letters.size() * nextLetter.getGlobalBounds().width), this->y); //set letter position
        this->letters.push_back(nextLetter); //add to letters
    }
}

///////////////////////////////////////////////////////////////////
// scales the text by a factor of (@fs)
///////////////////////////////////////////////////////////////////

void GText::setFontScale(float fs) {
    this->fontScale = fs;
    this->refreshLetters();
}

///////////////////////////////////////////////////////////////////
// resets the font using the spritesheet at (@fontDir)
///////////////////////////////////////////////////////////////////

void GText::setFont(GFont* f) {
    this->font = f;
    this->fontSheet = font->getFontSheet();
    this->setText(this->text);
}

///////////////////////////////////////////////////////////////////
// illustrates text onto (@w)
///////////////////////////////////////////////////////////////////

void GText::illustrate(sf::RenderWindow* w) {
    for (sf::Sprite s : this->letters) w->draw(s); //draw each letter
}

///////////////////////////////////////////////////////////////////
// resets the scale and positions of each letter
///////////////////////////////////////////////////////////////////

void GText::refreshLetters() {
    for (int i = 0; i < this->letters.size(); i++) {
        this->letters.at(i).setScale(this->fontScale, this->fontScale);
        this->letters.at(i).setPosition(this->x + (i * this->letters.at(i).getGlobalBounds().width), this->y); //set letter position
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
