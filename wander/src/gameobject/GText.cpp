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
// (@fontDir) - directory for the font sheet
// (@text) - starting text for the button
// (@x) - x position of button
// (@y) - y position of button
///////////////////////////////////////////////////////////////////

GText::GText(std::string fontDir, std::string text, int x, int y) {
    this->fSheet.loadFromFile(fontDir); //load font spritesheet
    this->x = x;
    this->y = y;
    this->parseFontSheet();
    this->setText(text);
}

///////////////////////////////////////////////////////////////////
// sets the text to (@t)
///////////////////////////////////////////////////////////////////

void GText::setText(std::string t) {
    this->l = std::vector<sf::Sprite>(); //remove previous letter
    int lX, lY; //letter x and y
    for (char c : t) { //loop through each character of t
        
        getCharacterPos(&lX, &lY, c); //get position in font sheet of character
        if (lX != -1 && lY != -1) { //if valid position
            sf::Sprite nl(this->fSheet); //create letter
            nl.setTextureRect(sf::IntRect(lX * this->lW, lY * this->lH, lW, lH)); //set letter texture rect
            nl.setScale(this->fScale, this->fScale);
            nl.setPosition(this->x + (this->l.size() * nl.getGlobalBounds().width), this->y); //set letter position
            this->l.push_back(nl); //add to letters
        }
    }
}

///////////////////////////////////////////////////////////////////
// scales the text by a factor of (@fs)
///////////////////////////////////////////////////////////////////

void GText::setFontScale(float fs) {
    this->fScale = fs;
    this->refreshLetters();
}

///////////////////////////////////////////////////////////////////
// resets the font using the spritesheet at (@fontDir)
///////////////////////////////////////////////////////////////////

void GText::setFont(std::string fontDir) {
    this->fSheet.loadFromFile(fontDir);
    this->parseFontSheet();
}

///////////////////////////////////////////////////////////////////
// illustrates text onto (@w)
///////////////////////////////////////////////////////////////////

void GText::illustrate(sf::RenderWindow* w) {
    for (sf::Sprite s : this->l) {
        w->draw(s);
    }
}

///////////////////////////////////////////////////////////////////
// figures out width and height of each letter in the font sheet
///////////////////////////////////////////////////////////////////

void GText::parseFontSheet() {
    this->lW = this->fSheet.getSize().x / 10; //10 columns
    this->lH = this->fSheet.getSize().y / 3; //3 rows
}

///////////////////////////////////////////////////////////////////
// resets the scale and positions of each letter
///////////////////////////////////////////////////////////////////

void GText::refreshLetters() {
    for (int i = 0; i < this->l.size(); i++) {
        this->l.at(i).setScale(this->fScale, this->fScale);
        this->l.at(i).setPosition(this->x + (i * this->l.at(i).getGlobalBounds().width), this->y); //set letter position
    }
}

///////////////////////////////////////////////////////////////////
// sets (@x) and (@y) to the standard x and y grid positions
// (respectively) of a specified character (@c)
///////////////////////////////////////////////////////////////////

void GText::getCharacterPos(int* x, int* y, char c) {
    switch (c) {
        case 'a':
        case 'A':
            *x = *y = 0;
            break;
        case 'b':
        case 'B':
            *x = 1; *y = 0;
            break;
        case 'c':
        case 'C':
            *x = 2; *y = 0;
            break;
        case 'd':
        case 'D':
            *x = 3; *y = 0;
            break;
        case 'e':
        case 'E':
            *x = 4; *y = 0;
            break;
        case 'f':
        case 'F':
            *x = 5; *y = 0;
            break;
        case 'g':
        case 'G':
            *x = 6; *y = 0;
            break;
        case 'h':
        case 'H':
            *x = 7; *y = 0;
            break;
        case 'i':
        case 'I':
            *x = 8; *y = 0;
            break;
        case 'j':
        case 'J':
            *x = 9; *y = 0;
            break;
        case 'k':
        case 'K':
            *x = 0; *y = 1;
            break;
        case 'l':
        case 'L':
            *x = 1; *y = 1;
            break;
        case 'm':
        case 'M':
            *x = 2; *y = 1;
            break;
        case 'n':
        case 'N':
            *x = 3; *y = 1;
            break;
        case 'o':
        case 'O':
            *x = 4; *y = 1;
            break;
        case 'p':
        case 'P':
            *x = 5; *y = 1;
            break;
        case 'q':
        case 'Q':
            *x = 6; *y = 1;
            break;
        case 'r':
        case 'R':
            *x = 7; *y = 1;
            break;
        case 's':
        case 'S':
            *x = 8; *y = 1;
            break;
        case 't':
        case 'T':
            *x = 9; *y = 1;
            break;
        case 'u':
        case 'U':
            *x = 0; *y = 2;
            break;
        case 'v':
        case 'V':
            *x = 1; *y = 2;
            break;
        case 'w':
        case 'W':
            *x = 2; *y = 2;
            break;
        case 'x':
        case 'X':
            *x = 3; *y = 2;
            break;
        case 'y':
        case 'Y':
            *x = 4; *y = 2;
            break;
        case 'z':
        case 'Z':
            *x = 5; *y = 2;
            break;
        default:
            *x = *y = -1;
            break;
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
