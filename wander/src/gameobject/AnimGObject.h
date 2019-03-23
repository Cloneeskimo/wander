//
//  AnimGObject.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef AnimGObject_h
#define AnimGObject_h

//C++ Includes
#include <iostream>

//SFML Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Wander Includes
#include "GObject.h"

//an extension of GObject that supports animations
class AnimGObject : public GObject {
    
public:
    
    //constructor - parameters listed in AnimGObject.cpp
    AnimGObject(std::string textureFileName, int frameCount, int frameRows = 1, float frameDelay = gc::GO_DEFAULT_FRAME_DELAY, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y);
    
    //public functions
    void compute(float dT); //compute method
    void pause() { this->paused = true; } //pauses animation
    void resume() { this->paused = false; } //resumes animation
    bool setFrameRow(int fr); //set frame row
    int getFrameRow() { return this->frameRow + 1; } //accessor for frame row
    
private:
    
    //animation properties
    int frameRows, frameRow; //amount of rows of frames (animation setting), currently selected frame row
    int frameCount, currentFrame; //amount of frames per row, current frame
    int frameWidth, frameHeight; //width of a single frame in the sheet, height of a single frame in the sheet
    float tBeforeNextFrame, frameDelay; //(in seconds) time before next frame shows, amount of time btn frames
    sf::IntRect textureRect; //currently selected rectangle of the sheet being shown
    bool paused = false;
    
    //private functions
    void cycleFrame(); //cycles to next frame
};

#endif /* AnimGObject_h */