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
// (@normalFont) - reference to font for normal button state
// (@highlightFont) - reference to font for highlighted button state
// (@clickFont) - reference to font for clicked button state
// (@ID) - unique identifier for the button - must be positive
// (@x) - x position as an absolute co-ordinate
// (@y) - y position as an absolute co-ordinate
// (@text) - the text to be displayed on the button
///////////////////////////////////////////////////////////////////

void ButtonInterface::addButton(GFont* normalFont, GFont* highlightFont, GFont* clickFont, int ID, int x, int y, std::string text) {
    if (ID < 1) gf::error("ButtonInterface.h", "attempted to assign a non-positive ID to a button", 0);
    this->buttons.push_back(new Button(normalFont, highlightFont, clickFont, text, ID, x, y));
    int i = (int)this->buttons.size() - 1; //get handle on button vector size
    this->buttons.at(i)->text->setFontScale(this->scale);
    if (this->centeredPositions) {
        int adjX = this->buttons.at(i)->text->getX() - (this->buttons.at(i)->text->getW() / 2); //adjust x
        int adjY = this->buttons.at(i)->text->getY() - (this->buttons.at(i)->text->getH() / 2); //adjust y
        this->buttons.at(i)->text->setX(adjX); //set to adjusted x
        this->buttons.at(i)->text->setY(adjY); //set to adjusted y
    }
}

///////////////////////////////////////////////////////////////////
// adds a button to the interface using GText
// (@normalFont) - reference to font for normal button state
// (@highlightFont) - reference to font for highlighted button state
// (@clickFont) - reference to font for clicked button state
// (@ID) - unique identifier for the button - must be positive
// (@x) - x position as an absolute co-ordinate
// (@y) - y position as an absolute co-ordinate
// (@text) - the text to be displayed on the button
///////////////////////////////////////////////////////////////////

void ButtonInterface::addButton(GFont* normalFont, GFont* highlightFont, GFont* clickFont, int ID, float x, float y, std::string text, sf::RenderWindow* w) {
    this->addButton(normalFont, highlightFont, clickFont, ID, (float)w->getSize().x * x, (float)w->getSize().y * y, text);
}

///////////////////////////////////////////////////////////////////
// will handle any events dealing with the mouse and buttons and return the ID of a button if it is clicked
// (@w) - reference to the window
// (@e) - reference to the event to check
///////////////////////////////////////////////////////////////////

int ButtonInterface::input(sf::RenderWindow* w, sf::Event* e)
{
    //get mouse pos and button being hovered
    sf::Vector2f mousePosW = w->mapPixelToCoords(sf::Mouse::getPosition(*w)); //get mouse position in world coordinates
    int bI = this->mouseHover(mousePosW.x, mousePosW.y); //see if mouse is over any buttons
    
    //MOUSE MOVED
    if (e->type == sf::Event::MouseMoved) {
        for (int i = 0; i < this->buttons.size(); i++) {
            if (i == bI) { //if button is being hovered
                if (this->buttons.at(bI)->getState() == BUTTON_NORMAL) { //if set to unhighlighted,
                    this->buttons.at(bI)->setState(BUTTON_HIGHLIGHT);
                }
            } else this->buttons.at(i)->setState(BUTTON_NORMAL); //set to unhighlighted texture
        }
    }
    
    //MOUSE CLICKED DOWN
    if (e->type == sf::Event::MouseButtonPressed && bI > -1) //if click is over a button
        this->buttons.at(bI)->setState(BUTTON_CLICK); //set to clicked texture
    
    //MOUSE RELEASED
    if (e->type == sf::Event::MouseButtonReleased) {
        if (bI > -1) {
            if (this->buttons.at(bI)->getState() == BUTTON_CLICK) { //if this button was the one clicked
                this->buttons.at(bI)->setState(BUTTON_HIGHLIGHT);
                return this->buttons.at(bI)->getID(); //return that the user selected it
            }
        }
    }
    
    return 0; //return no buttons pressed
}

///////////////////////////////////////////////////////////////////
// illustrate method, takes window (@w) reference
///////////////////////////////////////////////////////////////////

void ButtonInterface::illustrate(sf::RenderWindow* w) {
    for (int i = 0; i < this->buttons.size(); i++) this->buttons.at(i)->text->illustrate(w);
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
    if (this->buttons.size() < 1) return 0; //return 0 if no last button
    int deltaX = this->buttons.at(this->buttons.size() - 1)->text->getW() + space; //space of button itself
    if (this->centeredPositions) deltaX += (this->buttons.at(this->buttons.size() - 1)->text->getW() / 2); //account for centeredness
    if (!toRight) deltaX = -deltaX; //account for direction
    return this->buttons.at(this->buttons.size() - 1)->text->getX() + deltaX; //return new x
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
    if (this->buttons.size() < 1) return 0; //return 0 if no last button
    int deltaY = this->buttons.at(this->buttons.size() - 1)->text->getH() + space; //space of button itself
    if (this->centeredPositions) deltaY += (this->buttons.at(this->buttons.size() - 1)->text->getH() / 2); //account for centeredness
    if (!below) deltaY = -deltaY; //account for direction
    return this->buttons.at(this->buttons.size() - 1)->text->getY() + deltaY; //return new y
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
    for (int i = 0; i < this->buttons.size(); i ++) {
        if (this->buttons.at(i)->text->getRect().contains(mouseX, mouseY)) //if mouse is within rect
            return i; //return said button index
    }
    return -1;
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
