///////////////////////////////////////////////////////////////////
//
//  Global.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#ifndef Global_h
#define Global_h

// Includes
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////
// GC Namepsace
// Global Constants
///////////////////////////////////////////////////////////////////

namespace gc {
    
    //Build Properties
    static const int A_BUILD = 69; //build number
    static const std::string A_VERSION = "basic_dev"; //version number
    
    //Window Properties
    static const int W_FRAMERATE_LIMIT = 60; //limits framerate
    static const std::string W_TITLE = "Wander v" + A_VERSION + " b" + std::to_string(A_BUILD); //defines title for window
    static const sf::Keyboard::Key DEBUG_KEY = sf::Keyboard::D;
    static const sf::Color CLEAR_COLOR = sf::Color::White;
    
    //GameObject Properties
    static const int GO_DEFAULT_X = 0; //default starting x for GameObjects
    static const int GO_DEFAULT_Y = 0; //default starting y for GameObjects
    static const int TILE_SIZE = 32; //size for tiles
    static const float TILE_TEXTURE_SCALE = 3.0f; //scale for tiles
    static const float GO_DEFAULT_FRAME_DELAY = 0.2f; //default delay between frames in an AnimatableGameObject
    
    //Exit Codes
    static const int SUCCESS = 1;
    static const int FAILURE_BY_FILEIO = -1;
    static const int FAILURE_BY_DATA = -2;
}

///////////////////////////////////////////////////////////////////
// GF Namespace
// Global Functions
///////////////////////////////////////////////////////////////////

namespace gf {
    
    //Global Utility Functions
    void ensureDir(std::string path);
    bool canOpenFile(std::string path);
    void terminate(int exitStatus);
    void error(std::string originFile, std::string message, int code, int exitStatus = gc::SUCCESS, bool fatal = false);
}

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
