//
//  GScreen.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef GScreen_h
#define GScreen_h

//SFML Includes
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

//Wander Includes
#include "SaveManager.h"
#include "AnimGObject.h"
#include "Global.h"

//C++ Includes
#include <vector>

//a generic class for a window/screen that should be kept discrete and distinct from others
//for example, this may be extended from to make the main menu screen, game screen, inventory screen, etc.
class GScreen {
    
public:
    
    //the method which enters the screen and returns data once screen is finished
    Node enter(sf::RenderWindow* w, sf::Text* debug) {
        this->w = w; //set window reference
        this->loop(); //loop
        
        //when loop is done, return a Node to summarize important takeaway from this screen
        //return data by default has a child node which indicates whether or not the
        //user indicated intent to return to the previous screen, or close to program entirely
        //the sending function should handle this accordingly
        rd.addC(Node("finish type", this->w->isOpen() ? "returned" : "closed"));
        return this->rd;
    }
    
private:
    
    //SFML Items
    sf::RenderWindow* w; //reference to the program's window
    sf::Text* d; //text which displays debug info
    sf::Clock c; //clock used for timekeeping purposes
    
    //Wander Items
    std::vector<AnimGObject> gos; //vector of screen's game objects
    Node rd = Node("return data"); //the node of information which will be returned when the screen is finished
    
    //C++ Items
    bool intentToReturn = false; //represents whether user has shown intent to return to previous screen
    bool showDebug = false; //represents whether debug info should be shown on screen or not

    //screen loop (input, compute, illustrate)
    void loop() {
        
        while (!(this->intentToReturn) && this->w->isOpen()) { //continue looping until user closes or returns
            std::cout << "window open: " << this->w->isOpen() << std::endl;
            this->input(); //phase 1 - input
            this->compute(); //phase 2 - compute
            this->illustrate(); //phase 3 - illustrate
        }
    }
    
    //phase 1 of screen loop - gather user input
    //needs to be overriden to consider any input other than user attempting to close window
    void input() {
        sf::Event e;
        while (this->w->pollEvent(e)) {
            if (e.type == sf::Event::Closed) //close window if user closes it
                this->w->close();
            if (e.type == sf::Event::KeyReleased && e.key.code == gc::DEBUG_KEY)
                this->showDebug = !this->showDebug;
        }
    }
    
    //phase 2 of screen loop - compute
    //needs to be overriden to update anything other than the objects within gos
    void compute() {
        for (AnimGObject o : this->gos)
            o.compute(this->c.getElapsedTime().asSeconds());
        this->c.restart(); //restart clock
    }
    
    //phase 3 of screen loop - illustrate
    //needs to be overriden to draw anything other than the objects within gos
    void illustrate() {
        
        this->w->clear(gc::CLEAR_COLOR); //clear screen
        for (AnimGObject o : this->gos) //illustrate objects
            o.illustrate(this->w);
        if (this->showDebug) this->w->draw(*this->d); //draw debug if enabled
        this->w->display(); //display new screen
    }
};

#endif /* GScreen_h */
