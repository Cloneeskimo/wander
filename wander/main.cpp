
#include <iostream>
#include <string>
#include <SFML/Window.hpp>

static const int W_WIDTH = 800;   //defines width for window
static const int W_HEIGHT = 600;  //defines height for window
static const int A_BUILD = 3;     //records build no. for window
static const std::string W_TITLE = "Wander b" + std::to_string(A_BUILD);  //defines title for window

int main(int, char const**)
{
    sf::Window w(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Default); //create window
    
    while (w.isOpen()) { //program loop
    
        //check events
        sf::Event e;
        while (w.pollEvent(e)) {
            
            if (e.type == sf::Event::Closed) //window close event
                w.close();
        }
    }
    
    return 0; //return successful run
}
