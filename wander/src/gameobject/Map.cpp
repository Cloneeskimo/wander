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
    
    //random number generation
    srand(time(NULL)); //initialize random generation with time as seed
    
    //set name and window reference
    this->name = name;
    this->w = w;
    
    //load master data node for map
    Node mn = SaveManager::loadMasterNode(layoutFile); //master node
    
    //create map from loaded data
    std::vector<CharTextureCombo> ctcs;
    loadCTCs(&ctcs, mn.getCwN("map_chars")); //load CTCs
    
    for (CharTextureCombo ctc : ctcs) {
        std::cout << ctc.character << ": " << std::endl;
        for (std::string s : ctc.possibleTiles)
            std::cout << "    " << s << "," << std::endl;
    }
    
    this->loadBackground(mn.getCwN("background_layout"), &ctcs); //load background
    this->loadWall(mn.getCwN("wall_layout"), &ctcs); //load wall
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
    
    //illustrate background first
    for (std::vector<StaticTile*> row : this->background) //each row
        for (StaticTile* st: row) //each item within that row
            if (st != nullptr) st->illustrate(this->w); //illustrate
    
    //illustrate walls second
    for (std::vector<StaticTile*> row : this->wall) //each row
        for (StaticTile* st: row) //each item within that row
            if (st != nullptr) st->illustrate(this->w); //illustrate
}

///////////////////////////////////////////////////////////////////
// Will return a node tree containing all the state info for
// the map at the current moment
///////////////////////////////////////////////////////////////////

Node Map::getStateInfo() {
    
}

///////////////////////////////////////////////////////////////////
// Will attempt to convert the node (@n) into CTCs
///////////////////////////////////////////////////////////////////

void Map::loadCTCs(std::vector<CharTextureCombo>* ctcs, Node n) {
    std::vector<Node> charReps = n.getC(); //get each representation node
    for (Node charRep : charReps) { //loop through each representation node
        CharTextureCombo ctc; //create ctc
        ctc.character = charRep.getN()[0]; //set character
        std::string tileList = charRep.getV(); //get possible tiles
        remove_if(tileList.begin(), tileList.end(), isspace); //remove spaces
        std::stringstream ss(tileList); //stream through the string
        std::string possibleTile; //individual tile
        while(std::getline(ss, possibleTile, ',')) ctc.possibleTiles.push_back(possibleTile); //split, add to vector
        std::string correction = ctc.possibleTiles.at(ctc.possibleTiles.size() - 1); //correct additional characters at end
        correction = correction.substr(0, correction.length() + 1 - ctc.possibleTiles.size());
        ctc.possibleTiles.at(ctc.possibleTiles.size() - 1) = correction;
        ctcs->push_back(ctc); //add to ctcs
    }
}

///////////////////////////////////////////////////////////////////
// Loads the background layer of tiles from node (@n) using (@ctcs)
///////////////////////////////////////////////////////////////////

void Map::loadBackground(Node n, std::vector<CharTextureCombo>* ctcs) {
    Node rowNode("");
    for (int y = 0; n.getCwN(&rowNode, "row " + std::to_string(y)); y++) { //loop through each row
        this->background.push_back(std::vector<StaticTile*>()); //add empty row
        std::string row = rowNode.getCwN("layout").getV(); //get row
        for (int x = 0; x < row.length(); x++) { //go through row
            bool charRepFound = false;
            for (CharTextureCombo ctc : *ctcs) { //search for character representation
                if (ctc.character == row[x]) { //if found
                    charRepFound = true; //flag as found
                    int no = rand() % ctc.possibleTiles.size();
                    this->background.at(y).push_back(new StaticTile(ctc.possibleTiles[no], x, y)); //add tile
                }
                if (!charRepFound) this->background.at(y).push_back(nullptr); //add empty tile
            }
        }
    }
}

///////////////////////////////////////////////////////////////////
// Loads the wall layer of tiles from node (@n) using (@ctcs)
///////////////////////////////////////////////////////////////////

void Map::loadWall(Node n, std::vector<CharTextureCombo>* ctcs) {
    Node rowNode("");
    for (int y = 0; n.getCwN(&rowNode, "row " + std::to_string(y)); y++) { //loop through each row
        this->wall.push_back(std::vector<StaticTile*>()); //add empty row
        std::string row = rowNode.getCwN("layout").getV(); //get row
        for (int x = 0; x < row.length(); x++) { //go through row
            bool charRepFound = false;
            for (CharTextureCombo ctc : *ctcs) { //search for character representation
                if (ctc.character == row[x]) { //if found
                    charRepFound = true; //flag as found
                    int no = rand() % ctc.possibleTiles.size();
                    this->wall.at(y).push_back(new StaticTile(ctc.possibleTiles[no], x, y)); //add tile
                }
                if (!charRepFound) this->wall.at(y).push_back(nullptr); //add empty tile
            }
        }
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
