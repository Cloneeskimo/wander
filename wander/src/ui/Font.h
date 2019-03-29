///////////////////////////////////////////////////////////////////
//
//  Font.h
//  wander
//
//  Created by Jacob Oaks on 3/28/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Font_h
#define Font_h

// Includes

#include <vector>
#include <SFML/Graphics.hpp>
#include "SaveManager.h"

///////////////////////////////////////////////////////////////////
// GCharacterMap Struct
// Maps a certain character (@c) to a place in a font sheet grid
///////////////////////////////////////////////////////////////////

struct GCharacterMap {
public:
    
    // Constructor
    GCharacterMap(char c, int x, int y) {
        this->c = c;
        this->x = x;
        this->y = y;
    }
    
    // Data
    char c;
    int x;
    int y;
};

///////////////////////////////////////////////////////////////////
// Font Class
// Contains a mapping of character to position on a font sheet
///////////////////////////////////////////////////////////////////

class Font {
public:
    
    // Constructor
    Font(std::string fontDir, std::string mapDir);
    
    // Accessors
    sf::IntRect getBounds(char c);
    sf::Texture* getFontSheet() { return &this->fSheet; }
    int getLetterWidth() { return this->letterWidth; }
    int getLetterHeight() { return this->letterHeight; }
    
private:
    
    // Private Data
    sf::Texture fSheet; //font sheet texture
    std::vector<GCharacterMap> charMap; //mapping for each character
    std::vector<sf::Sprite> letters; //sprites for each letter
    int letterWidth, letterHeight; //width and height for each letter
    
    // Private Functions
    void getPos(char c, int* x, int* y);
    
    // Initialization
    void initFontSheet(std::string* fontDir); //loads the font sheet and calculates letter width and height
    void initCharacterMapping(std::string* mapDir); //loads the character mapping into (@charMap)
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
