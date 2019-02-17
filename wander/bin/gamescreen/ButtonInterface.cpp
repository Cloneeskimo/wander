//
//  ButtonInterface.cpp
//  wander
//
//  Created by Jacob Oaks on 2/17/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "ButtonInterface.h"

//adds a button to the interface
//textureLocation - location of sprite sheet relative to working directory
//ID - unique identifier for the button - MUST BE POSITIVE
//x, y - position of the button
void ButtonInterface::addButton(std::string textureLocation, int ID, int x, int y, int frameCount) {
    if (ID < 1) //make sure ID is positive
        gf::error("ButtonInterface.h", "attempted to assign a non-positive ID to a button", 0);
    this->buttons.push_back(new AnimGObject(textureLocation, frameCount, 3, gc::GO_DEFAULT_FRAME_DELAY, x, y)); //add button
    this->IDs.push_back(ID); //add corresponding ID
    int i = this->buttons.size() - 1; //get index of button just added
    this->buttons.at(i)->scale(this->scale, this->scale); //scale appropriately
    if (this->centeredPositions) { //adjust for centeredness
        int adjX = this->buttons.at(i)->getX() - (this->buttons.at(i)->getW() / 2); //adjust x
        int adjY = this->buttons.at(i)->getY() - (this->buttons.at(i)->getH() / 2); //adjust y
        this->buttons.at(this->buttons.size() - 1)->setPos(adjX, adjY); //set to adjusted values
    }
}

//adds a button to the interface
//same as above method with following difference:
//x and y are given between 0/1 to represent a position on screen as a percentage of width/height
void ButtonInterface::addButton(std::string textureLocation, int ID, float x, float y, int frameCount, sf::RenderWindow* w) {
    this->addButton(textureLocation, ID, (float)w->getSize().x * x, (float)w->getSize().y * y, frameCount);
}

//will handle any events dealing with the mouse and buttons and return the ID of a button if it is clicked
int ButtonInterface::input(sf::RenderWindow* w, sf::Event* e)
{
    //get mouse pos and button being hovered
    sf::Vector2i mousePos = sf::Mouse::getPosition(*w); //get mouse position
    int bI = this->mouseHover(mousePos.x, mousePos.y); //see if mouse is over any buttons
    
    //MOUSE MOVED
    if (e->type == sf::Event::MouseMoved) {
        for (int i = 0; i < this->buttons.size(); i++) {
            if (i == bI) { //if button is being hovered
                if (this->buttons.at(bI)->getFrameRow() == 1) //if set to unhighlighted,
                    this->buttons.at(bI)->setFrameRow(2); //set to highlighted texture
            } else { //if button is not being hovered
                this->buttons.at(i)->setFrameRow(1); //set to unhighlighted texture
            }
        }
    }
    
    //MOUSE CLICKED DOWN
    if (e->type == sf::Event::MouseButtonPressed && bI > -1) { //if click is over a button
        this->buttons.at(bI)->setFrameRow(3); //set to clicked frame row
    }
    
    //MOUSE RELEASED
    if (e->type == sf::Event::MouseButtonReleased) {
        if (bI > -1) {
            if (this->buttons.at(bI)->getFrameRow() == 3) { //if this button was the one clicked
                std::cout << this->IDs.at(bI) << " clicked" << std::endl;
                return this->IDs.at(bI); //return that the user selected it
            }
            this->buttons.at(bI)->setFrameRow(2); //set to highlighted frame row
        }
    }
    
    return 0; //return no buttons pressed
}

//compute method
void ButtonInterface::compute(float dT) {
    for (AnimGObject* o : this->buttons)
        o->compute(dT);
}

//illustrate method
void ButtonInterface::illustrate(sf::RenderWindow* w) {
    for (AnimGObject* o : this->buttons)
        o->illustrate(w);
}

int ButtonInterface::mouseHover(int mouseX, int mouseY) {
    for (int i = 0; i < this->buttons.size(); i ++) {
        if (this->buttons.at(i)->getRect().contains(mouseX, mouseY)) //if mouse is within rect
            return i; //return said button index
    }
    return -1;
}
