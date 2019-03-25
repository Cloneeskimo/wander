///////////////////////////////////////////////////////////////////
//
//  Map.h
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Map_h
#define Map_h

// Includes

#include <string>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "StaticTile.h"
#include "SaveManager.h"

///////////////////////////////////////////////////////////////////
// CharTextureCombo struct
// a piece of data which pairs a character to a set of
// possible textures
///////////////////////////////////////////////////////////////////

struct CharTextureCombo { //define CharTextureCombo struct
    
    // Data
    char character; //character representing the possible tiles
    std::vector<std::string> possibleTiles; //the possible tiles
};

///////////////////////////////////////////////////////////////////
// Map Class
// holds all the data for a single map
///////////////////////////////////////////////////////////////////

class Map {
public:
    
    // Constructors
    Map() {}; //default constructor
    Map(std::string name, std::string layoutFile, sf::RenderWindow* w); //for creating a new instance of map
    Map(Node stateInfo, sf::RenderWindow* w); //for creating an instance from a previously saved one
    
    // Utility Functions
    void illustrate(); //illustrates the map
    
    // Accessors
    Node getStateInfo(); //converts map into Node data
    
private:
    
    // SFML Objects
    sf::RenderWindow* w; //reference to window
    
    // Data
    std::string name; //name of map
    
    // Map Layers
    std::vector<std::vector<StaticTile*>> background; //mapping of background
    std::vector<std::vector<StaticTile*>> wall; //mapping of walls
    
    // Map Loading Methods
    void loadCTCs(std::vector<CharTextureCombo>* ctcs, Node n); //loads CTCs
    void loadBackground(Node n, std::vector<CharTextureCombo>* ctcs); //loads background layer of tiles
    void loadWall(Node n, std::vector<CharTextureCombo>* ctcs); //loads background layer of walls
    
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
