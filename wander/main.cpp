
//
//  main.cpp
//  wander
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "bin/Engine.h"

//main function
int main(int, char const**)
{
	Engine engine; //create engine
    int exitStatus = engine.run(); //run program
	std::cout << "wander ran with exit status: " << exitStatus << std::endl; //print exit status
}
