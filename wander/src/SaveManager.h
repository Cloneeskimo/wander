///////////////////////////////////////////////////////////////////
//
//  SaveManager.h
//  wander
//
//  Created by Jacob Oaks on 2/12/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef SaveManager_h
#define SaveManager_h

// Includes
#include <string>
#include <vector>
#include <fstream>
#include "Global.h"

///////////////////////////////////////////////////////////////////
// Node Class
// used to represent a single piece of data and its children pieces of data
///////////////////////////////////////////////////////////////////

class Node {
public:
    
    // Constructors
    Node (std::string name, std::string value, std::vector<Node> children); //multiple children
    Node (std::string name, std::string value, Node child); //single child
    Node (std::string name, std::string value); //no children
    Node (std::string name) { this->name = name; } //no children or value
    Node () {} //no children, value, or name
    
    // Accessors
    std::string getV() { return this->value; } //get value
    std::string getN() { return this->name; } //get name
    std::vector<Node> getC() { return this->children; } //get all children
    Node getCwN(std::string name); //get specific child by name
    bool getCwN(Node* node, std::string name); //get specific child by name, return existence
    int getCSize() { return (int)this->children.size(); } //get size of children
    
    // Mutators
    void setV(std::string newV) { this->value = newV; } //set value
    void setN(std::string newN) { this->name = newN; } //set name
    void addC(Node newC) { this->children.push_back(newC); } //add child
    
private:
    
    // Private Data
    std::string name; //the name of this piece of data
    std::string value; //the actual data of this node
    std::vector<Node> children; //all of the its child nodes
    
};

///////////////////////////////////////////////////////////////////
// SaveManager Class
// used to write data nodes to files and conversely read files into data
///////////////////////////////////////////////////////////////////

class SaveManager {
    
public:
    
    // Master Node Saving/Loading
    static void saveMasterNode(std::string path, Node* node); //save node to file
    static Node loadMasterNode(std::string path); //load node from file
    
private:
    
    // Recursive Node Saving/Loading
    static void saveNode(std::ofstream* write, Node* node, std::string indent); //save node recursively
    static Node loadNode(std::vector<std::string>* file, int* i, int indent); //load node recursively
    
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
