//
//  GameObject.hpp
//  wander
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"

//a generic class for any game object. contains a sprite and a position.
class GObject {
    
protected:

    //gobject properties
    sf::Sprite sprite; //object sprite
    sf::Texture texture; //texture owned by the sprite
    
public:
    
    //constructor - parameters are as follows
    //textureFileName - location & name of texture file relative to working directory
    //startX - starting object x (has default value defined in Global.h)
    //startY - starting object y (has default value defined in Global.h)
    GObject(std::string textureFileName, int startX = gc::GO_DEFAULT_X, int startY = gc::GO_DEFAULT_Y) {
        if(!this->texture.loadFromFile(textureFileName)) { //attempt to load texture
            std::cout << "[GObject.hpp]: '" << textureFileName << "' could not be loaded (0)" << std::endl;
            return; //print error and return if image loading fails
        }
        this->sprite = sf::Sprite(this->texture); //initialize sprite
        this->sprite.setPosition(startX, startY); //set sprite starting position
    };
    
    //utility functions
    void illustrate(sf::RenderWindow *w) { w->draw(this->sprite); } //illustrate method just draws the sprite
    void compute(float dT) {}; //written to be overriden by inherited classes
    
    //accessors
    int getX() { return this->sprite.getPosition().x; }
    int getY() { return this->sprite.getPosition().y; }
    sf::Vector2f getPos() { return this->sprite.getPosition(); }
    
    //mutators
    void setX(int newX) { this->sprite.setPosition(newX, this->sprite.getPosition().y); }
    void setY(int newY) { this->sprite.setPosition(this->sprite.getPosition().x, newY); }
    void setPos(sf::Vector2f newPos) { this->sprite.setPosition(newPos); }
};

#endif /* GObject_hpp */
