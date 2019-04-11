///////////////////////////////////////////////////////////////////
//
//  Global.cpp
//  wander
//
//  Created by Jacob Oaks on 2/21/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

//ERROR CODES USED: 0

#include "Global.h"

///////////////////////////////////////////////////////////////////
// GF Namespace
// Global Functions
///////////////////////////////////////////////////////////////////

namespace gf {
    
    ///////////////////////////////////////////////////////////////////
    // returns the workable directory of the program for FileIO
    ///////////////////////////////////////////////////////////////////
    
    std::string getWorkablePath() {
        
        //check if this is an export build
        if (!gc::FOR_EXPORT) return ""; //if not, just work with the immediate path
        
        //get desirable path
        std::string p = boost::dll::program_location().string(); //get path
        std::string r = "wander.app/Contents/MacOS/wander"; //part of directory to check for and remove
        if (p.length() >= r.length() && p.substr(p.length() - r.length(), r.length()) == r) //if the ending is r
            p = p.substr(0, p.length() - r.length()); //remove the end and return
        
        //add double slashes
        for (int i = 0; i < p.length(); i++) {
            if (p[i] == 47) {
                p.insert(i, "/");
                i++;
            }
        }
        
        //return path
        return p;
    }
    
    ///////////////////////////////////////////////////////////////////
    // creates a directory (@path) if it doesn't already exist
    ///////////////////////////////////////////////////////////////////

    void ensureDir(std::string path) {
        if (!boost::filesystem::is_directory(getWorkablePath() + path))
            if (boost::filesystem::create_directory(getWorkablePath() + path))
                std::cout << "failure" << std::endl;
    }
    
    ///////////////////////////////////////////////////////////////////
    // returns whether or not file can be opened at path (@path)
    ///////////////////////////////////////////////////////////////////

    bool canOpenFile(std::string path) {
        std::ifstream open;
        open.open(getWorkablePath() + path);
        return !open.fail();
    }
    
    ///////////////////////////////////////////////////////////////////
    // exits program with a code (@exitStatus).
    // preferably only use in case of error
    ///////////////////////////////////////////////////////////////////

    void terminate(int exitStatus) {
        std::cout << "wander finished with status " << exitStatus << std::endl;
        exit(exitStatus);
    }
    
    ///////////////////////////////////////////////////////////////////
    // handles an error
    // @originFile - file which error occurs in
    // @message - description of error
    // @code - a unique code for that error in that file (there can be duplicate codes across files)
    // @exitStatus - if fatal, a status to terminate the program with
    // @fatal - whether or not error is fatal and program needs to terminate
    ///////////////////////////////////////////////////////////////////

    void error(std::string originFile, std::string message, int code, int exitStatus, bool fatal) {
        
        //Record Time
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        std::string date = std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday) + "-" + std::to_string(now->tm_year + 1900);
        std::string time = std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" + std::to_string(now->tm_sec);
        
        //make error string, display to console
        std::string error = "[" + time + "][build " + std::to_string(gc::A_BUILD) + "][" + originFile + "]: " + message + " (" + std::to_string(code) + ")";
        std::cout << error << std::endl;
        
        //attempt to open errors.txt to log error
        std::ofstream write;
        ensureDir("errors"); //make error directory
        write.open(getWorkablePath() + "errors//" + date + ".txt", std::ofstream::app); //open errors.txt
        if (write.fail()) //display additional error to console if couldn't create error directory
            std::cout << "[" + time + "][Global.h]: unable to create error file (0)" << std::endl;
        else
            write << error << std::endl; //write error to file
        
        //terminate if fatal
        if (fatal) terminate(exitStatus);
    }
}
    
///////////////////////////////////////////////////////////////////
// Checks to see if the opaque tile arrays and other oto objects
// are initialized and initializes them if not
///////////////////////////////////////////////////////////////////

void oto::checkOpaqueTile() {
    
    //Create Opaque Pixel Array
    if (oto::opaqueTile == nullptr) {
        oto::opaqueTile = new sf::Uint8[gc::TILE_SIZE * gc::TILE_SIZE * 4];
        for(int y = 0; y < gc::TILE_SIZE; y++) {
            for(int x = 0; x < gc::TILE_SIZE; x++) {
                oto::opaqueTile[4*(x * gc::TILE_SIZE +y)]   = 0;    // R
                oto::opaqueTile[4*(x * gc::TILE_SIZE +y)+1] = 100;  // G
                oto::opaqueTile[4*(x * gc::TILE_SIZE +y)+2] = 0;    // B
                oto::opaqueTile[4*(x * gc::TILE_SIZE +y)+3] = 0;  // A
            }
        }
        
        //Calculate Constants
        int dividedConstant = gc::TILE_SIZE / gc::TILE_MODULARIZATION_DIVISOR;
        oto::modOffsetConstant = gc::TILE_SIZE - dividedConstant;
        oto::modCornerOffsetConstant = oto::modOffsetConstant - dividedConstant;
        
        //Create Opaque Images
        oto::opaqueColumn.create(dividedConstant, gc::TILE_SIZE, oto::opaqueTile);
        oto::opaqueRow.create(gc::TILE_SIZE, dividedConstant, oto::opaqueTile);
        oto::opaqueCorner.create(2 * dividedConstant, 2 * dividedConstant, oto::opaqueTile);
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
