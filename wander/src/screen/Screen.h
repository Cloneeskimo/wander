///////////////////////////////////////////////////////////////////
//
//  Screen.h
//  wander
//
//  Created by Jacob Oaks on 2/16/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Screen_h
#define Screen_h

// Includes

#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SaveManager.h"
#include "AnimObject.h"
#include "Global.h"
#include "Text.h"

///////////////////////////////////////////////////////////////////
// Screen Class
// a generic class for a window/screen that should be kept discrete and distinct from others
// for example, this may be extended from to make the main menu screen, game screen, inventory screen, etc.
///////////////////////////////////////////////////////////////////

class Screen {
    
public:
    
    ///////////////////////////////////////////////////////////////////
    // Constructor - takes window and debug references
    ///////////////////////////////////////////////////////////////////

    Screen(sf::RenderWindow* w, Text* d) {
        
        //set references
        this->w = w; //set window reference
        this->d = d; //set debug text reference
        
        //setup world view
        this->worldV.setCenter(this->w->getSize().x / 2, this->w->getSize().y / 2);
        this->worldV.setSize(this->w->getSize().x, this->w->getSize().y);
        this->w->setView(worldV);
        
        //setup ui view
        this->uiV.setCenter(this->w->getSize().x / 2, this->w->getSize().y / 2);
        this->uiV.setSize(this->w->sf::Window::getSize().x, this->w->getSize().y);
    }
    
    ///////////////////////////////////////////////////////////////////
    // the method which enters the screen and returns data once screen is finished
    ///////////////////////////////////////////////////////////////////

    virtual Node enter() {
        this->loop(); //loop

        //when loop is done, return a Node to summarize important takeaway from this screen
        //return data by default has a child node which indicates whether or not the
        //user indicated intent to return to the previous screen, or close to program entirely
        //the sending function should handle this accordingly
        rd.addC(Node("finish type", this->w->isOpen() ? "returned" : "closed"));
        return this->rd;
    }

protected:
    
    // SFML Objects
    sf::RenderWindow* w; //reference to the program's window
    Text* d; //text which displays debug info
    sf::Clock c; //clock used for timekeeping purposes
    sf::View worldV; //world view
    sf::View uiV; //UI view
    float debugCount = gc::D_DELAY; //in seconds
    
    // Other Protected Data
    std::vector<AnimObject*> gos; //vector of screen's game objects
    Node rd = Node("return data"); //the node of information which will be returned when the screen is finished
    bool intentToReturn = false; //represents whether user has shown intent to return to previous screen
    bool showDebug = false; //represents whether debug info should be shown on screen or

    ///////////////////////////////////////////////////////////////////
    // screen loop (input, compute, illustrate)
    ///////////////////////////////////////////////////////////////////

    virtual void loop() {
        while (!(this->intentToReturn) && this->w->isOpen()) { //continue looping until user closes or returns
            this->input(); //phase 1 - input
            this->compute(); //phase 2 - compute
            this->restartClock(); //phase 2.5 - restart clock
            this->illustrate(); //phase 3 - illustrate
        }
    }
    
    ///////////////////////////////////////////////////////////////////
    // phase 1 of screen loop - gather user input
    // should NOT be overriden - override handleEvent() instead
    ///////////////////////////////////////////////////////////////////

    virtual void input() final {
        sf::Event e;
        while (this->w->pollEvent(e)) this->handleEvent(e);
    }
    
    ///////////////////////////////////////////////////////////////////
    // handles an individual event from phase 1 (input)
    // when overriden, call this
    ///////////////////////////////////////////////////////////////////

    virtual void handleEvent(sf::Event e) {
        switch (e.type) {
            case sf::Event::Closed: //USER CLOSED WINDOW
                this->w->close();
                break;
            case sf::Event::KeyReleased: //USER PRESSED DEBUG KEY
                if (e.key.code == control::debug)
                    this->showDebug = !this->showDebug;
                break;
            case sf::Event::Resized: //USER RESIZED WINDOW
                this->worldV.setSize(this->w->getSize().x, this->w->getSize().y); //adapt world view
                this->uiV.setCenter(this->w->getSize().x / 2, this->w->getSize().y / 2); //adapt ui view pos
                this->uiV.setSize(this->w->getSize().x, this->w->getSize().y); //adapt ui view size
                this->updateUI();
                break;
            default:
                break;
        }
    }
    
    ///////////////////////////////////////////////////////////////////
    // phase 2 of screen loop - compute
    // needs to be overriden to update anything other than the objects within gos
    ///////////////////////////////////////////////////////////////////

    virtual void compute() {
        for (AnimObject* o : this->gos) o->compute(this->c.getElapsedTime().asSeconds()); //compute for gos
        if (this->showDebug) {
            this->debugCount -= this->c.getElapsedTime().asSeconds();
            if (this->debugCount < 0) {
                this->d->setText("FPS: " + std::to_string(1 / this->c.getElapsedTime().asSeconds())); //update debug text if enabled
                this->debugCount = gc::D_DELAY;
            }
        }
    }
    
    ///////////////////////////////////////////////////////////////////
    // phase 2.5 of screen loop - reset clock
    // resets the clock after compute. seperate to allow easier
    // overriding of compute w/o time errors
    ///////////////////////////////////////////////////////////////////
    
    virtual void restartClock() {
        this->c.restart(); //restart clock
    }
    
    ///////////////////////////////////////////////////////////////////
    // phase 3 of screen loop - illustrate
    // needs to be overriden to draw anything other than the objects within gos
    ///////////////////////////////////////////////////////////////////

    virtual void illustrate() {
        
        //clear screen
        this->w->clear(gc::CLEAR_COLOR); //clear
        
        //draw world
        for (AnimObject* o : this->gos) o->illustrate(this->w); //illustrate gos
        
        //draw UI
        this->w->setView(uiV); //set to ui view
        if (this->showDebug) this->d->illustrate(this->w);
        
        //display
        this->w->setView(worldV); //set back to world view
        this->w->display(); //display new screen
    }
    
    ///////////////////////////////////////////////////////////////////
    // resets all UI elements to their rightful position
    // needs to be overriden and called if more static UI elements are added
    // should be called whenever window is modified (resized or moved)
    ///////////////////////////////////////////////////////////////////

    virtual void updateUI() {}
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
