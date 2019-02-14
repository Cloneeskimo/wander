//
//  AnimGObject.cpp
//  wander
//
//  Created by Jacob Oaks on 2/13/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "AnimGObject.h"

//constructor - parameters are as follows
//textureFileName - location relative to working direction
//frames - amount of frames in one row of the spritesheet
//frameRows - amount of rows of frames in the spritesheet
//frameDelay - the time is seconds between frames (has a default in Global.h)
//startX - starting object X (has a default in Global.h)
//startY - starting object Y (has a default in GLobal.h)
AnimGObject::AnimGObject(std::string textureFileName, int frameCount, int frameRows, float frameDelay, int startX, int startY) : GObject(textureFileName, startX, startY) {
    this->frameCount = frameCount;
    this->currentFrame = -1;
    this->frameRows = frameRows;
    this->frameRow = 0;
    this->frameDelay = this->tBeforeNextFrame = frameDelay;
    this->frameWidth = this->texture.getSize().x / frameCount;
    this->frameHeight = this->texture.getSize().y / frameRows;
    this->cycleFrame(); //cycle first frame
}

//cycle to next frame
void AnimGObject::cycleFrame() {
    this->currentFrame = (this->currentFrame >= this->frameCount - 1 ? 0 : this->currentFrame + 1); //cycle
    this->textureRect = sf::IntRect(this->currentFrame * this->frameWidth, this->frameRow * this->frameHeight, this->frameWidth, this->frameHeight); //update textureRect
    this->sprite.setTextureRect(this->textureRect); //set textureRect within sprite
}

//compute function
void AnimGObject::compute(float dT) {
    if (this->paused) return;
    if (this->tBeforeNextFrame <= 0) { //check if time to cycle to next frame
        this->cycleFrame(); //cycle frame if ready to do so
        this->tBeforeNextFrame = this->frameDelay; //reset timer
    }
    this->tBeforeNextFrame -= dT; //count down until next cycle
}

//changes the currently selected frame row (animation setting)
//returns false if fr is out of bounds (animation setting does not exist), true otherwise
//parameter is 1-indexed, actual value is 0-indexed
bool AnimGObject::setFrameRow(int fr) {
    if (fr > this->frameRows || fr < 1) return false;
    this->frameRow = fr - 1;
    this->cycleFrame();
    return true;
}
