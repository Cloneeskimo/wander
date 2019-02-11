//
//  GameObject.hpp
//  Graphics
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include <iostream>
#include <SFML/Graphics.hpp>

class GameObject {
    
private:
    
    //private properties
    sf::Sprite sprite; //https://www.sfml-dev.org/tutorials/2.5/graphics-sprite.php for hella texture info
    sf::Texture texture;
    
public:
    
    //constructors
    GameObject(std::string textureFileName, int startX = 0, int startY = 0) {
        if(!this->texture.loadFromFile(textureFileName)) { //an sf::IntRect can also be given to load only a small part of the image
            std::cout << textureFileName << " file not found to load texture with" << std::endl;
            return;
        }
        this->sprite = sf::Sprite(this->texture);
        this->sprite.setPosition(startX, startY);
    };
    
    //utility functions
    void illustrate(sf::RenderWindow *w) { w->draw(this->sprite); }
    
    //accessors
    int getX() { return this->sprite.getPosition().x; }
    int getY() { return this->sprite.getPosition().y; }
    sf::Vector2f getPos() { return this->sprite.getPosition(); }
    
    //mutators
    void setX(int newX) { this->sprite.setPosition(newX, this->sprite.getPosition().y); }
    void setY(int newY) { this->sprite.setPosition(this->sprite.getPosition().x, newY); }
    void setPos(sf::Vector2f newPos) { this->sprite.setPosition(newPos); }
};

#endif
