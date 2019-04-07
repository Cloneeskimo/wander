///////////////////////////////////////////////////////////////////
//
//  Text.cpp
//  wander
//
//  Created by Jacob Oaks on 3/22/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "Text.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@font) - reference to the Font to use
// (@text) - starting text
// (@x) - x position of text
// (@y) - y position of text
///////////////////////////////////////////////////////////////////

Text::Text(Font* font, std::string text, int x, int y) {
    this->setFont(font);
    this->setText(text);
    this->x = x;
    this->y = y;
}

///////////////////////////////////////////////////////////////////
// sets the text to (@t)
///////////////////////////////////////////////////////////////////

void Text::setText(std::string t) {
    
    //start by replacing/checking current letters
    int l = 0; //represents which letter of t we are on
    while (l < this->text.length()) {
        if (this->text[l] != t[l]) { //only change if letter is not equals
            this->letters[l].setTextureRect(this->font->getBounds(t[l])); //change texture rect
        }
        l++;
    }
    
    //remove any extra previous letters if necessary
    while (l < this->letters.size()) this->letters.pop_back(); //remove last letter
    
    //create any new characters if necessary
    while (l < t.size()) {
        sf::IntRect bounds = this->font->getBounds(t[l]); //get bounds on font sheet for character
        sf::Sprite nextLetter(*this->fontSheet); //create character sprite
        nextLetter.setTextureRect(bounds); //set bounds
        nextLetter.setScale(this->fontScale, this->fontScale); //set scale
        nextLetter.setPosition(this->x + (this->letters.size() * nextLetter.getGlobalBounds().width), this->y); //set letter position
        this->letters.push_back(nextLetter); //add to letters
        l++;
    }
    
    //record new text string
    this->text = t; //set text string
}

///////////////////////////////////////////////////////////////////
// scales the text by a factor of (@fs)
///////////////////////////////////////////////////////////////////

void Text::setFontScale(float fs) {
    this->fontScale = fs;
    this->refreshLetters();
}

///////////////////////////////////////////////////////////////////
// resets the font using the spritesheet at (@fontDir)
///////////////////////////////////////////////////////////////////

void Text::setFont(Font* f) {
    this->font = f;
    this->fontSheet = font->getFontSheet();
    this->refreshLetters(true);
}

///////////////////////////////////////////////////////////////////
// moves the text by (@dx) horizontally
///////////////////////////////////////////////////////////////////

void Text::moveX(int dx) {
    this->x += dx;
    for (int i = 0; i < this->letters.size(); i++) this->letters.at(i).move(dx, 0);
}

///////////////////////////////////////////////////////////////////
// moves the text by (@dy) vertically
///////////////////////////////////////////////////////////////////

void Text::moveY(int dy) {
    this->y += dy;
    for (int i = 0; i < this->letters.size(); i++) this->letters.at(i).move(0, dy);
}

///////////////////////////////////////////////////////////////////
// illustrates text onto (@w)
///////////////////////////////////////////////////////////////////

void Text::illustrate(sf::RenderWindow* w) {
    for (sf::Sprite s : this->letters) w->draw(s); //draw each letter
}

///////////////////////////////////////////////////////////////////
// resets the scale and positions of each letter
// if (@reload) is set to true, will also reset each letter texture
///////////////////////////////////////////////////////////////////

void Text::refreshLetters(bool reload) {
    for (int i = 0; i < this->letters.size(); i++) {
        if (reload) {
            this->letters.at(i).setTexture(*this->fontSheet); //reset texture
            this->letters.at(i).setTextureRect(this->font->getBounds(this->text[i])); //set bounds
        }
        this->letters.at(i).setScale(this->fontScale, this->fontScale); //set letter scale
        this->letters.at(i).setPosition(this->x + (i * this->letters.at(i).getGlobalBounds().width), this->y); //set letter position
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
