//
//  SaveManager.h
//  wander
//
//  Created by Jacob Oaks on 2/12/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef SaveManager_h
#define SaveManager_h

//C++ Includes
#include <string>
#include <vector>
#include <fstream>

//Wander Includes
#include "Global.h"

static const std::string FILE_NAME = "SaveManager.hpp";

//a class to represent a single piece of data and its children pieces of data
class Node {
    
public:
    
    //constructors
    Node (std::string name, std::string value, std::vector<Node> children); //multiple children
    Node (std::string name, std::string value, Node child); //single child
    Node (std::string name, std::string value); //no children
    Node (std::string name) { this->name = name; } //no children or value
    
    //accessors
    std::string getV() { return this->value; } //get value
    std::string getN() { return this->name; } //get name
    std::vector<Node> getC() { return this->children; } //get all children
    Node getCwN(std::string name); //get specific child by name
    int getCSize() { return this->children.size(); } //get size of children
    
    //mutators
    void setV(std::string newV) { this->value = newV; } //set value
    void setN(std::string newN) { this->name = newN; } //set name
    void addC(Node newC) { this->children.push_back(newC); } //add child
    
private:
    
    std::string name; //the name of this piece of data
    std::string value; //the actual data of this node
    std::vector<Node> children; //all of the its child nodes
    
};

//sm - SaveManager
//used to write data nodes to files and conversely read files into data
class sm {
    
public:
    
    //save/load master node functions
    static bool saveMasterNode(std::string path, Node* node); //save node to file
    static Node loadMasterNode(std::string path); //load node from file
    
private:
    
    //recursive save/load functions
    static void saveNode(std::ofstream* write, Node* node, std::string indent); //save node recursively
    static Node loadNode(std::vector<std::string>* file, int* i, int indent); //load node recursively
    
};

#endif /* SaveManager_h */
