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

//GC = Global Cosntants
namespace gc {
    
    //build properties
    static const int A_BUILD = 15; //records build no. for window
    
    //window properties
    static const int W_WIDTH = 800; //defines width for window
    static const int W_HEIGHT = 600; //defines height for window
    static const int W_FRAMERATE_LIMIT = 120;
    static const std::string W_TITLE = "Wander b" + std::to_string(A_BUILD); //defines title for window
    
    //GameObject properties
    static const int GO_DEFAULT_X = 0; //default starting x for GameObjects
    static const int GO_DEFAULT_Y = 0; //default starting y for GameObjects
    static const float GO_DEFAULT_FRAME_DELAY = 0.4f; //default delay between frames in an AnimatableGameObject
    
    //Run Codes
    static const int SUCCESS = 1;
    static const int FAILURE_BY_INPUT = -1;
    static const int FAILURE_BY_COMPUTE = -2;
    static const int FAILURE_BY_ILLUSRATE = -3;
}
    
#endif /* Global_h */