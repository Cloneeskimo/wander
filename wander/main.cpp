
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
	std::cout << "wander ran with exit status: " << engine.run() << std::endl; //run program, record exit status
}
