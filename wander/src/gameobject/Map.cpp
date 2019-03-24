///////////////////////////////////////////////////////////////////
//
//  Map.cpp
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "Map.h"

///////////////////////////////////////////////////////////////////
// Constructor
// This constructor will create an entirely new instance of this
// map using its basic template loaded from a date file.
// (@name) - name of map
// (@layoutFile) - location of file to load map info from
///////////////////////////////////////////////////////////////////

Map::Map(std::string name, std::string layoutFile, sf::RenderWindow* w) {
    
    //set name and window reference
    this->name = name;
    this->w = w;
    
    //load node
    Node mn = SaveManager::loadMasterNode(layoutFile);
    
    //load width and height
    int width = std::stoi(mn.getCwN("map_width").getV());
    int height = std::stoi(mn.getCwN("map_height").getV());
    
    //fill statics with empty
    for (int y = 0; y < height; y++) {
        this->statics.push_back(std::vector<StaticTile*>());
        for (int x = 0; x < width; x++) {
            this->statics.at(y).push_back(nullptr);
        }
    }
    
    //load the character types and layout
    Node chars = mn.getCwN("map_chars");
    Node layout = mn.getCwN("map_layout");
    
    //create layout
    for (int y = 0; y < height; y++) {
        std::string row = layout.getCwN("row " + std::to_string(y)).getCwN("layout").getV();
        for (int x = 0; x < row.length(); x++) {
            Node charRep("");
            if (chars.getCwN(&charRep, std::string(1, row[x]))) {
                this->statics.at(y).at(x) = new StaticTile(charRep.getV(), x, y);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////
// Constructor
// This constructor will essentially recreate a previously saved
// version of this map
// (@stateInfo) - a node containing all the data to load
///////////////////////////////////////////////////////////////////

Map::Map(Node stateInfo, sf::RenderWindow* w) {
    this->w = w;
}

///////////////////////////////////////////////////////////////////
// Illustrates this map onto (@w)
///////////////////////////////////////////////////////////////////

void Map::illustrate() {
    
    //illustrate statics first
    for (std::vector<StaticTile*> row : this->statics) { //each row
        for (StaticTile* st: row) { //each item within that row
            if (st != nullptr) st->illustrate(this->w); //illustrate
        }
    }
}

///////////////////////////////////////////////////////////////////
// Will return a node tree containing all the state info for
// the map at the current moment
///////////////////////////////////////////////////////////////////

Node Map::getStateInfo() {
    
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
