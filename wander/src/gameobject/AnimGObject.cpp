///////////////////////////////////////////////////////////////////
//
//  AnimGObject.cpp
//  wander
//
//  Created by Jacob Oaks on 2/13/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

// ERROR CODES USED: 0

#include "AnimGObject.h"

///////////////////////////////////////////////////////////////////
// Consructor which allows for custom frame row configurations
// (@textureFileName) - location relative to working direction
// (@frameRows) - data for each frame row - see FrameRow struct
// in "AnimGObject.h"
// (@startX) - starting object X (has a default in Global.h)
// (@startY) - starting object Y (has a default in GLobal.h)
///////////////////////////////////////////////////////////////////

AnimGObject::AnimGObject(std::string textureFileName, std::vector<FrameRow> frameRows, int startX, int startY) : GObject(textureFileName, startX, startY) {
    
    //Initialize Data
    this->frameRows = frameRows; //set frame rows
    this->currentFrameDelay = this->tBeforeNextFrame = this->frameRows.at(0).d; //set time and delay
    this->currentFrameCount = this->frameRows.at(0).fC; //set current frame count
    this->currentFrameRow = 0;
    this->currentFrame = -1; //set current frame
    int widestFrameCount = 1; //find widest frame count to calculate frame width
    for (FrameRow fr : this-> frameRows) {
        if (fr.fC > widestFrameCount) widestFrameCount = fr.fC;
    }
    this->frameWidth = this->texture.getSize().x / widestFrameCount; //set frame width
    this->frameHeight = this->texture.getSize().y / this->frameRows.size(); //set frame height
    this->cycleFrame(); //cycle first frame
}

///////////////////////////////////////////////////////////////////
// Consructor which assumes all frame rows will have the same configurations
// (@textureFileName) - location relative to working direction
// (@frameCount) - amount of frames in one row of the spritesheet
// (@frameRows) - amount of rows of frames in the spritesheet
// (@frameDelay) - the time in seconds between frames
// (@startX) - starting object X (has a default in Global.h)
// (@startY) - starting object Y (has a default in GLobal.h)
///////////////////////////////////////////////////////////////////

AnimGObject::AnimGObject(std::string textureFileName, int frameRows, int frameCount, float frameDelay, int startX, int startY) : GObject(textureFileName, startX, startY) {
    std::vector<FrameRow> frs;
    for (int i = 0; i < frameRows; i++)
        frs.push_back(FrameRow(frameCount, frameDelay));
}

///////////////////////////////////////////////////////////////////
// cycles to next frame
///////////////////////////////////////////////////////////////////

void AnimGObject::cycleFrame() {
    this->currentFrame = (this->currentFrame >= this->currentFrameCount - 1 ? 0 : this->currentFrame + 1); //cycle
    this->textureRect = sf::IntRect(this->currentFrame * this->frameWidth, this->currentFrameRow * this->frameHeight, this->frameWidth, this->frameHeight); //update textureRect
    this->sprite.setTextureRect(this->textureRect); //set textureRect within sprite
}

///////////////////////////////////////////////////////////////////
// Compute Function
// (@dT) - change in time in seconds since last call
///////////////////////////////////////////////////////////////////

void AnimGObject::compute(float dT) {
    if (this->paused) return; //do not animate if
    if (this->tBeforeNextFrame <= 0) { //check if time to cycle to next frame
        this->cycleFrame(); //cycle frame if ready to do so
        this->tBeforeNextFrame = this->currentFrameDelay; //reset timer
    }
    this->tBeforeNextFrame -= dT; //count down until next cycle
}

///////////////////////////////////////////////////////////////////
// changes the currently selected frame row (animation setting)
// returns false if fr is out of bounds (animation setting does not exist), true otherwise
// (@fr) is 1-indexed, actual value is 0-indexed
///////////////////////////////////////////////////////////////////

bool AnimGObject::setFrameRow(int fr) {
    if (fr > this->frameRows.size() || fr < 1) { //if invalid frame row
        gf::error("AnimGObject.cpp", "attempted to set an invalid frame row to an AnimGObject", 1); //throw error
        return false; //return false
    }
    this->currentFrameRow = fr - 1; //convert to zero-indexed
    this->currentFrameDelay = this->frameRows.at(fr - 1).d; //set frame delay
    this->currentFrameCount = this->frameRows.at(fr - 1).fC; //set frame count
    this->cycleFrame(); //cycle to next frame
    return true; //return true
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
