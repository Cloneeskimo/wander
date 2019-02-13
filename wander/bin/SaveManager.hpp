//
//  SaveManager.hpp
//  wander
//
//  Created by Jacob Oaks on 2/12/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef SaveManager_hpp
#define SaveManager_hpp

#include <string>
#include <vector>
#include <fstream>

//a class to represent a single piece of data and its children pieces of data
class Node {
    
public:
    
    //constructor with multiple children
    Node (std::string name, std::string value, std::vector<Node> children) {
        this->name = name;
        this->value = value;
        this->children = children;
    }
    
    //constructor with single child
    Node (std::string name, std::string value, Node child) {
        std::vector<Node> children;
        this->children.push_back(child);
        this->name = name;
        this->value = value;
        this->children = children;
    }
    
    //constructor with no children
    Node (std::string name, std::string value) {
        this->name = name;
        this->value = value;
        this->children = std::vector<Node>();
    }
    
    //constructor with no value
    Node (std::string name) {
        this->name = name;
    }
    
    //accessors
    std::string getV() { return this->value; } //get value
    std::string getN() { return this->name; } //get name
    std::vector<Node> getC() { return this->children; } //get all children
    Node getCwN(std::string name) { //get specific child by name
        for (Node node : this->children)
            if (node.getN() == name)
                return node;
    }
    int getCSize() { return this->children.size(); }
    
    //mutators
    void setV(std::string newV) { this->value = newV; } //set value
    void setN(std::string newN) { this->name = newN; } //set name
    void addC(Node newC) { this->children.push_back(newC); } //add child
    void setCwN(std::string name, std::string value) { //set child with specified name
        for (Node node : this->children)
            if (node.getN() == name)
                node.setV(value);
    }
    
private:
    
    std::string name; //the name of this piece of data
    std::string value; //the actual value of this node
    std::vector<Node> children; //all of the nodes beneath it
    
};

//sm - SaveManager
class sm {
    
public:
    //save node to file
    static bool saveMasterNode(std::string path, Node* node) {
        std::ofstream write;
        write.open(path);
        if (write.fail()) return false;
        
        saveNode(&write, node, "");
    }
    
    //load node from file
    static Node loadMasterNode(std::string path) {
        
        //open file
        std::ifstream read;
        read.open(path);
        //TODO: handle read.open failure
        
        //read entire file into vector of strings
        std::vector<std::string> file;
        std::string nextLine;
        while (!read.eof()) {
            getline(read, nextLine);
            file.push_back(nextLine);
        }
        
        //recursively loop through vector of strings to build the node
        int i = 0;
        return loadNode(&file, &i, 0);
    }
    
private:
    
    //a recursive function called to save each individual node
    static void saveNode(std::ofstream* write, Node* node, std::string indent) {
        *write << indent << node->getN() << ": ";
        if (node->getV() != "")
            *write << node->getV();
        *write << std::endl;
        if (node->getCSize() > 0) {
            *write << indent << "{" << std::endl;
            for (Node c : node->getC())
                saveNode(write, &c, indent + " ");
            *write << indent <<  "}" << std::endl;
        }
    }
    
    //a recursive function called to read each individual node
    //returns true if another node exists under it
    static Node loadNode(std::vector<std::string>* file, int* i, int indent) {
        
        //format next line and find dividing point
        std::string nextLine = file->at(*i); //nextLine
        nextLine = nextLine.substr(indent, nextLine.length() - indent); //remove indent
        int dividerLoc = -1; //location of divider in line
        for (int j = 0; j < nextLine.length() && dividerLoc == -1; j++) //find location of divider in line
            if (nextLine[j] == ':')
                dividerLoc = j;
        
        //TODO: no colon in line after name - format error
        
        //create node represented by next line
        Node node = Node(nextLine.substr(0, dividerLoc)); //create node with name
        std::string posVal = nextLine.substr(dividerLoc + 1, nextLine.length() - dividerLoc - 1); //load value
        if (posVal != " " && posVal != "") //if there is a value
            node.setV(posVal.substr(1, posVal.length() - 1)); //assign it to the new node (remove space)
        
        //check for more file
        if (*i + 1 <= file->size()) { //if not eof
            
            //check for child nodes
            if (file->at(*i + 1).find("{") != std::string::npos) { //if the node has children
                *i += 2; //iterate twice
                indent++; //iterate indent
                while (file->at(*i).find("}") == std::string::npos) { //if the children are over
                    node.addC(loadNode(file, i, indent));
                    *i += 1;
                    //TODO: handle sudden file stop
                }
            }
        }
        return node; //return newly-loaded node
    }
};

#endif /* SaveManager_hpp */
