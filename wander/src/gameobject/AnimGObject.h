///////////////////////////////////////////////////////////////////
//
//  AnimGObject.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef AnimGObject_h
#define AnimGObject_h

// Includes
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GObject.h"

///////////////////////////////////////////////////////////////////
// FrameRow struct
// a small data structure that holds data for a particular frame row
///////////////////////////////////////////////////////////////////

struct FrameRow {
public:
    
    ///////////////////////////////////////////////////////////////////
    // Constructor
    // (@fC) - frame count for this row
    // (@d) - frame delay for this row
    ///////////////////////////////////////////////////////////////////
    
    FrameRow(int fC, float d) {
        this->fC = fC;
        this->d = d;
    }
    
    // Default constructor
    
    FrameRow() {
        this->fC = 1;
        this->d = gc::GO_DEFAULT_FRAME_DELAY;
    }
    
    // Data
    
    int fC; //frame count
    float d; //delay
};

///////////////////////////////////////////////////////////////////
// AnimGObject class
// an extension of GObject that supports animations
///////////////////////////////////////////////////////////////////

class AnimGObject : public GObject {
public:
    
    // Constructors
    AnimGObject(std::string textureFileName, std::vector<FrameRow> frameRows = std::vector<FrameRow>(), int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y);
    AnimGObject(std::string textureFileName, int frameRows, int frameCount, float frameDelay = gc::GO_DEFAULT_FRAME_DELAY, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y);
    
    // Public Functions
    void compute(float dT); //compute method
    void pause() { this->paused = true; } //pauses animation
    void resume() { this->paused = false; } //resumes animation
    bool setFrameRow(int fr); //set frame row
    int getFrameRow() { return this->currentFrameRow + 1; } //accessor for frame row
    
private:
    
    // Animation Data
    int frameWidth, frameHeight; //width of a single frame in the sheet, height of a single frame in the sheet
    std::vector<FrameRow> frameRows; //collection of data for each frame row
    float tBeforeNextFrame; //time in seconds before next frame shows
    float currentFrameDelay; //amount of time in seconds between frames for the currently selected row
    int currentFrame, currentFrameRow, currentFrameCount; //current frame of the row, currently selected row, amount of frames in the currently selected row
    sf::IntRect textureRect; //currently selected rectangle of the sheet being shown
    bool paused = false; //whether the animation is paused or not
    
    // Private Functions
    void initAnimation(std::string textureFileName, std::vector<FrameRow> frameRows);
    void cycleFrame(); //cycles to next frame
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
