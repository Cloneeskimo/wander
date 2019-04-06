///////////////////////////////////////////////////////////////////
//
//  Font.cpp
//  wander
//
//  Created by Jacob Oaks on 3/28/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

// ERROR CODES USED: 0-1

#include "Font.h"

///////////////////////////////////////////////////////////////////
// Constructor
// (@fontDir) - the directory of the font sheet
// (@mapDir) - the directory of the character mapping file
///////////////////////////////////////////////////////////////////

Font::Font(std::string fontDir, std::string mapDir) {
    this->initFont(&fontDir, &mapDir); //initialize character mapping
}

///////////////////////////////////////////////////////////////////
// will set return the correct bounds for the character (@c) for
// this font
// will throw an error if an invalid character is given
///////////////////////////////////////////////////////////////////

sf::IntRect Font::getBounds(char c) {
    int x = -1, y = -1;
    this->getPos(c, &x, &y); //get the position of (@c)
    if (x == -1) gf::error("Font.cpp", "invalid character '" + std::string(1, c) + "' given when trying to set a letter sprite", 1); //throw error with invalid character
    return sf::IntRect(x * this->letterWidth, y * this->letterHeight, letterWidth, letterHeight); //return bounds
}

///////////////////////////////////////////////////////////////////
// will set (@x) and (@y) to the position in fSheet of (@c)
// will set (@x) and (@y) to -1 and -1 if (@c) is not found
// within the mapping
///////////////////////////////////////////////////////////////////

void Font::getPos(char c, int *x, int *y) {
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
// loads the character mapping from (@mapDir), loads the font
// sheet fron (@fontDir) and figures out the letter width
// and letter height
///////////////////////////////////////////////////////////////////

void Font::initFont(std::string* fontDir, std::string* mapDir) {
    
    // variables
    Node mn = SaveManager::loadMasterNode(*mapDir);
    std::vector<Node> cs = mn.getC();
    std::vector<Node> mappings = mn.getCwN("mappings")->getC(); //load mappings
    
    // load font sheet and calculate letter width and height
    this->fSheet.loadFromFile(*fontDir); //load font sheet
    this->letterWidth = this->fSheet.getSize().x / std::stoi(mn.getCwN("width")->getV()); //width
    this->letterHeight = this->fSheet.getSize().y / std::stoi(mn.getCwN("height")->getV()); //height
    
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
                gf::error("Font.cpp", "invalid character '" + std::string(1, c) + "' in font character mapping file + '" + *mapDir + "'", 0);
        }
    
        // convert and add
        int xI = std::stoi(x), yI = std::stoi(y); //convert data to integers
        this->charMap.push_back(GCharacterMap(n.getN()[0], xI, yI)); //add to character mappings
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
