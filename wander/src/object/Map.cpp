///////////////////////////////////////////////////////////////////
//
//  Map.cpp
//  wander
//
//  Created by Jacob Oaks on 3/24/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

//ERROR CODES USED: 0

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
    srand((unsigned int)time(NULL)); //initialize random generation with time as seed
    
    //set name and window reference
    this->name = name;
    this->w = w;
    
    //load master data node for map
    Node mn = SaveManager::loadMasterNode(layoutFile); //master node
    
    //create map from loaded data
    std::vector<CharTextureCombo> ctcs;
    loadCTCs(&ctcs, *mn.getCwN("map_chars")); //load CTCs
    
    //load static layers
    this->loadStaticLayer(*mn.getCwN("background_layout"), &ctcs, &(this->background)); //load background
    this->loadStaticLayer(*mn.getCwN("wall_layout"), &ctcs, &(this->wall)); //load walls
    this->modularizeLayer(&(this->wall));
    this->modularizeLayer(&(this->background));
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
// (@returns) a CollisionResult representing what kind of collision
// would occur with the IntRect (@r)
// if (@otoCompenstate), small portions of (@r) will be shaved off
// to compensate for the empty space at the end of modularized
// tiles
///////////////////////////////////////////////////////////////////

CollisionResult Map::checkForCollision(sf::IntRect r, bool otoCompensate) {
    if (otoCompensate) {
        r.top += oto::getModOffsetConstant();
        r.left += oto::getModOffsetConstant();
        r.width -= 2 * oto::getModOffsetConstant();
        r.height -= 2 * oto::getModOffsetConstant();
    }
    for (std::vector<StaticTile*> row : this->wall) { //for each row
        for (StaticTile* st : row) { //for each wall
            if (st != nullptr) { //if exists
                if (st->getRect().intersects(r)) //if contains the desired x/y
                    return CollisionResult::Static; //collision with a wall
            }
        }
    }
    return CollisionResult::None;
}

///////////////////////////////////////////////////////////////////
// will return a node tree containing all the state info for
// the map at the current moment
///////////////////////////////////////////////////////////////////

Node Map::getStateInfo() {
    
}

///////////////////////////////////////////////////////////////////
// returns the width of the map, based on the largest row of the map
///////////////////////////////////////////////////////////////////

int Map::getW() {
    int largestW = 0;
    for (std::vector<StaticTile*> r : this->background) {
        int s = (int)r.size();
        if (s > largestW) largestW = s;
    }
    return largestW * gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE;
}

///////////////////////////////////////////////////////////////////
// returns the height of the map, based on how many rows there are
///////////////////////////////////////////////////////////////////

int Map::getH() {
    return this->background.size() * gc::TILE_SIZE * gc::TILE_TEXTURE_SCALE;
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
// Loads a StaticTile layer of tiles from node (@n) using (@ctcs)
// and places it at (@layer)
///////////////////////////////////////////////////////////////////

void Map::loadStaticLayer(Node n, std::vector<CharTextureCombo>* ctcs, std::vector<std::vector<StaticTile*>>* layer) {
    Node rowNode("");
    for (int y = 0; n.getCwN(&rowNode, "row " + std::to_string(y)); y++) { //loop through each row
        layer->push_back(std::vector<StaticTile*>()); //add empty row
        std::string row = rowNode.getCwN("layout")->getV(); //get row
        for (int x = 0; x < row.length(); x++) { //go through row
            bool charRepFound = false;
            for (int i = 0; i < ctcs->size() && !charRepFound; i++) { //search for character representation
                if (ctcs->at(i).character == row[x]) { //if found
                    charRepFound = true; //flag as found
                    int no = rand() % ctcs->at(i).possibleTiles.size();
                    layer->at(y).push_back(new StaticTile(ctcs->at(i).possibleTiles[no], x, y)); //add tile
                }
            }
            if (!charRepFound) layer->at(y).push_back(nullptr); //add empty tile
        }
    }
}

///////////////////////////////////////////////////////////////////
// takes a given layer (@layer) and modularizes it - that is,
// it makes the corners and edges look better
///////////////////////////////////////////////////////////////////

void Map::modularizeLayer(std::vector<std::vector<StaticTile*>>* layer) {
    
    for (int y = 0; y < layer->size(); y++) { //go through each row
        for (int x = 0; x < layer->at(y).size(); x++) { //and then through each tile in that row
            if (layer->at(y).at(x) != nullptr) { //check if tile is actually there
            
                //variables
                char modularization = 0; //contains whether the
                char null = 0;
                
                //check if on edge
                if (x == 0) null = null | oto::LEFT;
                if (x == layer->at(y).size() - 1)  null = null | oto::RIGHT;
                if (y == 0) null = null | oto::TOP;
                if (y == layer->size() - 1) null |= oto::BOTTOM;
                
                //check for other tile in all directions
                if ((null & oto::LEFT) == 0) //check to left
                    if (layer->at(y).at(x-1) != nullptr)
                        modularization = modularization | oto::LEFT;
                if ((null & oto::RIGHT) == 0) //check to right
                    if (layer->at(y).at(x+1) != nullptr)
                        modularization = modularization | oto::RIGHT;
                if ((null & oto::TOP) == 0) //check above
                    if (layer->at(y-1).size() > x)
                        if (layer->at(y-1).at(x) != nullptr)
                            modularization = modularization | oto::TOP;
                if ((null & oto::BOTTOM) == 0) //check below
                    if (layer->at(y+1).size() > x)
                        if (layer->at(y+1).at(x) != nullptr)
                            modularization = modularization | oto::BOTTOM;
                
                //if this tile is not completely surrounded, modularize it
                if (modularization != 0) layer->at(y).at(x)->modularize(modularization);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
