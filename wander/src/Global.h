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
#include <boost/filesystem.hpp>
#include <boost/dll/runtime_symbol_info.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

///////////////////////////////////////////////////////////////////
// GC Namepsace
// Global Constants
///////////////////////////////////////////////////////////////////

namespace gc {
    
    //Build Properties
    static const int A_BUILD = 100; //build number
    static const bool FOR_EXPORT = false; //flag for export build or IDE build
    static const std::string A_VERSION = "basic_dev"; //version number
    
    //Window Properties
    static const int W_FRAMERATE_LIMIT = 60; //limits framerate
    static const std::string W_TITLE = "Wander v" + A_VERSION + " b" + std::to_string(A_BUILD); //defines title for window
    static const sf::Color CLEAR_COLOR = sf::Color::White;
    
    //GameObject Properties
    static const int GO_DEFAULT_X = 0; //default starting x for GameObjects
    static const int GO_DEFAULT_Y = 0; //default starting y for GameObjects
    
    //Tile Properties
    static const int TILE_SIZE = 32; //size for tiles
    static const float TILE_TEXTURE_SCALE = 3.0f; //scale for tiles
    static const float GO_DEFAULT_FRAME_DELAY = 0.2f; //default delay between frames in an AnimObject
    static const int TILE_MODULARIZATION_DIVISOR = 7; //the portion of a tile's edge to cut off in modularization
    
    //Other Properties
    static const char NODE_FILE_INDENT_CHARACTER = ' ';
    static const float D_DELAY = 0.5f; //delay between debug text updates in seconds
    
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
    std::string getWorkablePath();
    void ensureDir(std::string path);
    bool canOpenFile(std::string path);
    void terminate(int exitStatus);
    void error(std::string originFile, std::string message, int code, int exitStatus = gc::SUCCESS, bool fatal = false);
}

///////////////////////////////////////////////////////////////////
// OTO Struct
// Opaque Tile Overlays
// stores and managers data and operations related to the OTOs
// used for tile modularization
///////////////////////////////////////////////////////////////////

struct oto {
    
    // Modularization Bytes
    static const unsigned char TOP_LEFT = 128;
    static const unsigned char TOP = 64;
    static const unsigned char TOP_RIGHT = 32;
    static const unsigned char RIGHT = 16;
    static const unsigned char BOTTOM_RIGHT = 8;
    static const unsigned char BOTTOM = 4;
    static const unsigned char BOTTOM_LEFT = 2;
    static const unsigned char LEFT = 1;
    
    // Data
    static inline sf::Uint8* opaqueTile; //array of opaque pixels for modularization
    static inline sf::Image opaqueColumn; //opaque column used for modularization
    static inline sf::Image opaqueRow; //opaque row used for modularization
    static inline sf::Image opaqueCorner; //opaque corner used for modularization

    // Functions
    static void checkOpaqueTile();
    static int getModOffsetConstant() { return oto::modOffsetConstant; }
    static int getModCornerOffsetConstant() { return oto::modCornerOffsetConstant; }
    
private:
    
    // Offset Constants
    static inline int modOffsetConstant = 0;
    static inline int modCornerOffsetConstant = 0;
};

///////////////////////////////////////////////////////////////////
// Control Struct
// Stores all of the control settings for the game (keybindings)
///////////////////////////////////////////////////////////////////

struct control {
    
    //Control Settings
    static inline sf::Keyboard::Key debug = sf::Keyboard::D;
    static inline sf::Keyboard::Key moveLeft = sf::Keyboard::Left;
    static inline sf::Keyboard::Key moveUp = sf::Keyboard::Up;
    static inline sf::Keyboard::Key moveDown = sf::Keyboard::Down;
    static inline sf::Keyboard::Key moveRight = sf::Keyboard::Right;
};

#endif

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
