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
#include <vector>
#include <SFML/Graphics.hpp>
#include "StaticTile.h"
#include "SaveManager.h"

///////////////////////////////////////////////////////////////////
// Map Class
// holds all the data for a single map
///////////////////////////////////////////////////////////////////

class Map {
public:
    
    // Constructors
    Map() {}; //default constructor
    Map(std::string name, std::string layoutFile, sf::RenderWindow* w); //for creating a new instance of map from template
    Map(Node stateInfo, sf::RenderWindow* w); //for creating a new instance from a previously saved one
    
    // Utility Functions
    void illustrate(); //illustrates the map
    
    // Accessors
    Node getStateInfo(); //converts map into Node data
    
private:
    
    // SFML Objects
    sf::RenderWindow* w;
    
    // Data
    std::string name; //name of map
    std::vector<std::vector<StaticTile*>> statics; //mapping of staticTiles
    
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
