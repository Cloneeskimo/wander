///////////////////////////////////////////////////////////////////
//
//  ButtonInterface.cpp
//  wander
//
//  Created by Jacob Oaks on 2/17/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

// ERROR CODES USED: 0-1

#include "ButtonInterface.h"

///////////////////////////////////////////////////////////////////
// adds a button to the interface using GText
// (@fsN) - location of font sheet for button in its normal case
// (@fsH) - location of font sheet for button in its highlighted case
// (@fsC) - location of font sheet for button in its clicked case
// (@ID) - unique identifier for the button - must be positive
// (@x) - x position as an absolute co-ordinate
// (@y) - y position as an absolute co-ordinate
// (@text) - the text to be displayed on the button
///////////////////////////////////////////////////////////////////

void ButtonInterface::addButton(std::string fsN, std::string fsH, std::string fsC, int ID, int x, int y, std::string text) {
    if (ID < 1) gf::error("ButtonInterface.h", "attempted to assign a non-positive ID to a button", 0);
    this->bs.push_back(new GText(fsN, text, x, y)); //add button
    this->bds.push_back(new ButtonData(fsN, fsH, fsC)); //add button fonts
    this->IDs.push_back(ID); //add ID
    int i = (int)this->bs.size() - 1; //get handle on button vector size
    this->bs.at(i)->setFontScale(this->scale); //set font scale
    if (this->centeredPositions) {
        int adjX = this->bs.at(i)->getX() - (this->bs.at(i)->getW() / 2); //adjust x
        int adjY = this->bs.at(i)->getY() - (this->bs.at(i)->getH() / 2); //adjust y
        this->bs.at(i)->setX(adjX); //set to adjusted x
        this->bs.at(i)->setY(adjY); //set to adjusted y
    }
}

///////////////////////////////////////////////////////////////////
// adds a button to the interface using GText
// (@fsN) - location of font sheet for button in its normal case
// (@fsH) - location of font sheet for button in its highlighted case
// (@fsC) - location of font sheet for button in its clicked case
// (@ID) - unique identifier for the button - must be positive
// (@x) - x position as an absolute co-ordinate
// (@y) - y position as an absolute co-ordinate
// (@text) - the text to be displayed on the button
///////////////////////////////////////////////////////////////////

void ButtonInterface::addButton(std::string fsN, std::string fsH, std::string fsC, int ID, float x, float y, std::string text, sf::RenderWindow* w) {
    this->addButton(fsN, fsH, fsC, ID, (float)w->getSize().x * x, (float)w->getSize().y * y, text);
}

///////////////////////////////////////////////////////////////////
// will handle any events dealing with the mouse and buttons and return the ID of a button if it is clicked
// (@w) - reference to the window
// (@e) - reference to the event to check
///////////////////////////////////////////////////////////////////

int ButtonInterface::input(sf::RenderWindow* w, sf::Event* e)
{
    //get mouse pos and button being hovered
    sf::Vector2i mousePosP = sf::Mouse::getPosition(*w); //get mouse position in pixel
    sf::Vector2f mousePosW = w->mapPixelToCoords(mousePosP); //convert mouse position to world
    int bI = this->mouseHover(mousePosW.x, mousePosW.y); //see if mouse is over any buttons
    
    //MOUSE MOVED
    if (e->type == sf::Event::MouseMoved) {
        for (int i = 0; i < this->bs.size(); i++) {
            if (i == bI) { //if button is being hovered
                if (this->bds.at(bI)->state == 1) { //if set to unhighlighted,
                    this->bds.at(bI)->state = 2; //set to highlighted texture
                    this->bs.at(bI)->setFont(this->bds.at(bI)->fsH);
                }
            } else ensureButtonState(i, 1); //set to unhighlighted texture
        }
    }
    
    //MOUSE CLICKED DOWN
    if (e->type == sf::Event::MouseButtonPressed && bI > -1) //if click is over a button
        ensureButtonState(bI, 3); //set to clicked texture
    
    //MOUSE RELEASED
    if (e->type == sf::Event::MouseButtonReleased) {
        if (bI > -1) {
            if (this->bds.at(bI)->state == 3) { //if this button was the one clicked
                ensureButtonState(bI, 2);
                this->bds.at(bI)->state = 2; //set to second state
                this->bs.at(bI)->setFont(this->bds.at(bI)->fsH); //set to highlighted frame row
                return this->IDs.at(bI); //return that the user selected it
            }
        }
    }
    
    return 0; //return no buttons pressed
}

///////////////////////////////////////////////////////////////////
// illustrate method, takes window (@w) reference
///////////////////////////////////////////////////////////////////

void ButtonInterface::illustrate(sf::RenderWindow* w) {
    for (GText* t : this->bs) t->illustrate(w);
}

///////////////////////////////////////////////////////////////////
// returns the x value to place a new button relative to the
// previously placed button.
// (@space) the amount of extra space to add after the previous button
// (@toRight) whether to calculate the x to the right or, if false, the left
// NOTE: will add an extra 1/2 of the previous button's width if centered
// is set to true, as assumes centered will remain true
// [Special Case]: returns 0 if there is no button
///////////////////////////////////////////////////////////////////

int ButtonInterface::getNextX(int space, bool toRight) {
    if (this->bs.size() < 1) return 0; //return 0 if no last button
    int deltaX = this->bs.at(this->bs.size() - 1)->getW() + space; //space of button itself
    if (this->centeredPositions) deltaX += (this->bs.at(this->bs.size() - 1)->getW() / 2); //account for centeredness
    if (!toRight) deltaX = -deltaX; //account for direction
    return this->bs.at(this->bs.size() - 1)->getX() + deltaX; //return new x
}

///////////////////////////////////////////////////////////////////
// returns the y value to place a new button relative to the
// previously placed button.
// @returns 0 if there is no button
// (@space) the amount of extra space to add after the previous button
// (@below) whether to calculate the x below or, if false, above
// NOTE: will add an extra 1/2 of the previous button's height if centered
// is set to true, as assumes centered will remain true
///////////////////////////////////////////////////////////////////

int ButtonInterface::getNextY(int space, bool below) {
    if (this->bs.size() < 1) return 0; //return 0 if no last button
    int deltaY = this->bs.at(this->bs.size() - 1)->getH() + space; //space of button itself
    if (this->centeredPositions) deltaY += (this->bs.at(this->bs.size() - 1)->getH() / 2); //account for centeredness
    if (!below) deltaY = -deltaY; //account for direction
    return this->bs.at(this->bs.size() - 1)->getY() + deltaY; //return new y
}

///////////////////////////////////////////////////////////////////
// @returns the next x as a float value of where to place the next button
// relative to previously placed button.
// (@space) the amount of extra space to add after the previous button
// (@toRight) whether to calculate the x to the right or, if false, the left
// NOTE: will add an extra 1/2 of the previous button's width if centered
// is set to true, as assumes centered will remain true
// [Special Case]: returns 0 if there is no button
///////////////////////////////////////////////////////////////////

float ButtonInterface::getNextXF(sf::RenderWindow* w, int space, bool toRight) {
    return (float)this->getNextX(space, toRight) / (float)w->getSize().x;
}

///////////////////////////////////////////////////////////////////
// returns the y value as a float value of where to place the next button
// relative topreviously placed button.
// @returns 0 if there is no button
// (@space) the amount of extra space to add after the previous button
// (@below) whether to calculate the x below or, if false, above
// NOTE: will add an extra 1/2 of the previous button's height if centered
// is set to true, as assumes centered will remain true
///////////////////////////////////////////////////////////////////

float ButtonInterface::getNextYF(sf::RenderWindow* w, int space, bool below) {
    return (float)this->getNextY(space, below) / (float)w->getSize().y;
}

///////////////////////////////////////////////////////////////////
// determines if mouse is over a button - returns index of button if is, -1 if not
// (@mouseX) - x position of the mouse
// (@mouseY) - y position of the mouse
///////////////////////////////////////////////////////////////////

int ButtonInterface::mouseHover(float mouseX, float mouseY) {
    for (int i = 0; i < this->bs.size(); i ++) {
        if (this->bs.at(i)->getRect().contains(mouseX, mouseY)) //if mouse is within rect
            return i; //return said button index
    }
    return -1;
}

///////////////////////////////////////////////////////////////////
// ensures that the button at index (@i) is in the state (@state)
// checks to see if it is already set, therefore saving overhead
///////////////////////////////////////////////////////////////////

void ButtonInterface::ensureButtonState(int i, int state) {
    if (this->bds.at(i)->state != state) {
        this->bds.at(i)->state = state;
        switch (state) {
            case 1:
                this->bs.at(i)->setFont(this->bds.at(i)->fsN);
                break;
            case 2:
                this->bs.at(i)->setFont(this->bds.at(i)->fsH);
                break;
            case 3:
                this->bs.at(i)->setFont(this->bds.at(i)->fsC);
                break;
            default:
                gf::error("ButtonInterface.cpp", "Tried to assign a button image state to an out of range integer state", 1);
                break;
        }
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
