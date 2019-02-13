//
//  Global.h
//  wander
//
//  Created by Jacob Oaks on 2/11/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#ifndef Global_h
#define Global_h

#include <string>
#include <fstream>

//GC = Global Constants
namespace gc {
    
    //build properties
    static const int A_BUILD = 23; //build number
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
        
        //TODO: incorporate date and timekeeping into error recording
        
        //make error string, display to console
        std::string error = "[build " + std::to_string(gc::A_BUILD) + "][" + originFile + "]: " + message + " (" + std::to_string(code) + ")";
        std::cout << error << std::endl;
        
        //attempt to open errors.txt to print to it
        system("mkdir errors"); //make error directory
        //TODO make mkdir OS-dependent

        std::ofstream write;
        write.open("errors//errors.txt", std::ofstream::app); //open errors.txt
        if (write.fail()) //display additional error to console if couldn't create error directory
            std::cout << "[Global.h]: unable to create error file (0)" << std::endl;
        else
            write << error << std::endl; //write error to file
        
        //terminate if fatal
        if (fatal) terminate(exitStatus);
    }
}

#endif /* Global_h */
