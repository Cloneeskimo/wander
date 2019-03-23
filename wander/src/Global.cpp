///////////////////////////////////////////////////////////////////
//
//  Global.cpp
//  wander
//
//  Created by Jacob Oaks on 2/21/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//
///////////////////////////////////////////////////////////////////

#include "Global.h"

///////////////////////////////////////////////////////////////////
// GF Namespace
// Global Functions
///////////////////////////////////////////////////////////////////

namespace gf {
    
    ///////////////////////////////////////////////////////////////////
    // creates a directory (@path) if it doesn't already exist
    ///////////////////////////////////////////////////////////////////

    void ensureDir(std::string path) {
        
        //        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        //        CreateDirectory(path, NULL);
        //        if (!ERROR_ALREADY_EXISTS)
        //            error()
        //        #else
        //
        //        #endif
        
        std::string cmd = "mkdir " + path;
        system(cmd.c_str()); //TODO: update with a better, sytem-dependant solution
    }
    
    ///////////////////////////////////////////////////////////////////
    // returns whether or not file can be opened at path (@path)
    ///////////////////////////////////////////////////////////////////

    bool canOpenFile(std::string path) {
        std::ifstream open;
        open.open(path);
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
    // handles an error - parameters are defined below
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
        write.open("errors//" + date + ".txt", std::ofstream::app); //open errors.txt
        if (write.fail()) //display additional error to console if couldn't create error directory
            std::cout << "[" + time + "][Global.h]: unable to create error file (0)" << std::endl;
        else
            write << error << std::endl; //write error to file
        
        //terminate if fatal
        if (fatal) terminate(exitStatus);
    }
}

///////////////////////////////////////////////////////////////////
// EOF
///////////////////////////////////////////////////////////////////
