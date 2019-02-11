//
//  AnimatableGameObject.hpp
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef AnimatableGameObject_hpp
#define AnimatableGameObject_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "GameObject.hpp"

class AnimatableGameObject : public GameObject {
    
private:
    
    int frames;
    int frame;
    int frameWidth;
    int frameHeight;
    float tBeforeNextFrame; //in seconds always
    float frameDelay;
    sf::IntRect textureRect;
    
    void updateFrame() {
        this->frame = (this->frame >= this->frames - 1 ? 0 : this->frame + 1);
        this->textureRect = sf::IntRect(this->frame * frameWidth, 0, this->frameWidth, this->frameHeight);
        this->sprite.setTextureRect(this->textureRect);
    }
    
public:
    AnimatableGameObject(std::string textureFileName, int frames, float frameDelay = gc::GO_DEFAULT_FRAME_DELAY, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y) : GameObject(textureFileName, startX, startY) {
        this->frames = frames;
        this->frameDelay = this->tBeforeNextFrame = frameDelay;
        this->frame = -1;
        this->frameWidth = this->texture.getSize().x / this->frames;
        this->frameHeight = this->texture.getSize().y;
        this->updateFrame();
    }
    
    void illustrate(sf::RenderWindow *w) {
        w->draw(this->sprite);
    }
    
    void compute(float dT) {
        if (this->tBeforeNextFrame <= 0) {
            this->updateFrame();
            this->tBeforeNextFrame = this->frameDelay;
        }
        this->tBeforeNextFrame -= dT;
    }
};

#endif /* AnimatableGameObject_hpp */
