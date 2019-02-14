//
//  Global.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef Global_h
#define Global_h

//C++ Includes
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

//GC = Global Constants
namespace gc {
    
    //build properties
    static const int A_BUILD = 33; //build number
    static const std::string A_VERSION = "basic_dev"; //version number
    
    //window properties
    static const int W_FRAMERATE_LIMIT = 120; //limits framerate
    static const std::string W_TITLE = "Wander v" + A_VERSION + " b" + std::to_string(A_BUILD); //defines title for window
    
    //GameObject properties
    static const int GO_DEFAULT_X = 0; //default starting x for GameObjects
    static const int GO_DEFAULT_Y = 0; //default starting y for GameObjects
    static const float GO_DEFAULT_FRAME_DELAY = 0.2f; //default delay between frames in an AnimatableGameObject
    
    //Exit Codes
    static const int SUCCESS = 1;
    static const int FAILURE_BY_FILEIO = -1;
}

//GF = Global Functions
namespace gf {
    
    //creates a directory if it doesn't already exist
    static void ensureDir(std::string path) {
        std::string cmd = "mkdir " + path;
        system(cmd.c_str()); //TODO: update with a betetr, sytem-dependant solution
    }
    
    //returns whether or not file can be opened
    static bool canOpenFile(std::string path) {
        std::ifstream open;
        open.open(path);
        return !open.fail();
    }
    
    //used to exit program in case of an error
    static void terminate(int exitStatus) {
        std::cout << "wander finished with status " << exitStatus << std::endl;
        exit(exitStatus);
    }
    
    //report an error - params are as follows
    //originFile - file which error occurs in
    //message - description of error
    //code - a unique code for that error in that file (there can be duplicate codes across files)
    //exitStatus - if fatal, a status to terminate the program with
    //fatal - whether or not error is fatal and program needs to terminate
    static void error(std::string originFile, std::string message, int code, int exitStatus = gc::SUCCESS, bool fatal = false) {
        
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
        write.open("errors//" + date + ".txt", std::ofstream::app); //open errors.txt
        if (write.fail()) //display additional error to console if couldn't create error directory
            std::cout << "[" + time + "][Global.h]: unable to create error file (0)" << std::endl;
        else
            write << error << std::endl; //write error to file
    
        //terminate if fatal
        if (fatal) terminate(exitStatus);
    }
}

#endif /* Global_h */

//REFERENCE: OS Preprocessor Directions
//_WIN32
//(Windows 32-bit)
//_WIN64
//(Windows 64-bit)
//__unix || __unix__
//(Unix)
//__APPLE__ || __MACH__
//(Mac OSX)
//__linux__
//(Linux)
//__FreeBSD__
//(FreeBSD)
