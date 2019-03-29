///////////////////////////////////////////////////////////////////
//
//  GFont.cpp
//  wander
//
//  Created by Jacob Oaks on 3/28/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

// ERROR CODES USED: 0-1

#include "GFont.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@fontDir) - the directory of the font sheet
// (@mapDir) - the directory of the character mapping file
///////////////////////////////////////////////////////////////////

GFont::GFont(std::string fontDir, std::string mapDir) {
    this->initFontSheet(&fontDir); //initialize font sheet
    this->initCharacterMapping(&mapDir); //initialize character mapping
}

///////////////////////////////////////////////////////////////////
// will set return the correct bounds for the character (@c) for
// this font
// will throw an error if an invalid character is given
///////////////////////////////////////////////////////////////////

sf::IntRect GFont::getBounds(char c) {
    int x = -1, y = -1;
    this->getPos(c, &x, &y); //get the position of (@c)
    if (x == -1) gf::error("GFont.cpp", "invalid character '" + std::string(1, c) + "' given when trying to set a letter sprite", 1); //throw error with invalid character
    return sf::IntRect(x * this->letterWidth, y * this->letterHeight, letterWidth, letterHeight); //return bounds
}

///////////////////////////////////////////////////////////////////
// will set (@x) and (@y) to the position in fSheet of (@c)
// will set (@x) and (@y) to -1 and -1 if (@c) is not found
// within the mapping
///////////////////////////////////////////////////////////////////

void GFont::getPos(char c, int *x, int *y) {
    for (GCharacterMap gcm : this->charMap) { //search character mapping for (@c)
        if (gcm.c == c) { //if found
            *x = gcm.x; //set x
            *y = gcm.y; //set y
            return; //return
        }
    }
    *x = *y = -1; //not found, set to -1
}

///////////////////////////////////////////////////////////////////
// loads the font sheet from (@fontDir) into fSheet and calculates
// the letter width and letter height
///////////////////////////////////////////////////////////////////

void GFont::initFontSheet(std::string* fontDir) {
    this->fSheet.loadFromFile(*fontDir); //load font spritesheet
    this->letterWidth = this->fSheet.getSize().x / 10; //10 columns
    this->letterHeight = this->fSheet.getSize().y / 3; //3 rows
}

///////////////////////////////////////////////////////////////////
// loads the character mapping from (@mapDir)
///////////////////////////////////////////////////////////////////

void GFont::initCharacterMapping(std::string* mapDir) {
    
    // variables
    std::vector<Node> mappings = SaveManager::loadMasterNode(*mapDir).getC(); //load mappings
    
    // load each mapping
    for (Node n : mappings) {
        
        // parse mapping
        std::string mapping = n.getV(); //get data
        std::string x, y; //x and y
        bool passedSpace = false; //represent whether the space has been passed in parsing
        for (char c : mapping) { //parse each character of the value
            if (c == ' ') passedSpace = true;
            else if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') { //make sure a valid number is given
                if (passedSpace) //y
                    y += c;
                else x += c; //x
            } else //invalid character
                gf::error("GFont.cpp", "invalid character '" + std::string(1, c) + "' in font character mapping file + '" + *mapDir + "'", 0);
        }
    
        // convert and add
        int xI = std::stoi(x), yI = std::stoi(y); //convert data to integers
        this->charMap.push_back(GCharacterMap(n.getN()[0], xI, yI)); //add to character mappings
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
