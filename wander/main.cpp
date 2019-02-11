
//
//  main.cpp
//  wander
//
//  Created by Jacob Oaks on 2/10/19.
//  Copyright © 2019 Jacob Oaks. All rights reserved.
//

#include "Engine.h"

//main function
int main(int, char const**)
{
    Engine engine;
    int result = engine.run();
    if (result == gc::FAILURE)
        std::cout << "engine returned an unsuccessful run" << std::endl;
}
