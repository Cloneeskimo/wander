
#include <iostream>
#include <string>
#include <SFML/Window.hpp>

static const int W_WIDTH = 800;
static const int W_HEIGHT = 600;
static const int A_BUILD = 2;
static const std::string W_TITLE = "Wander b" + std::to_string(A_BUILD);

int main(int, char const**)
{
    sf::Window w(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Default);
    
    while (w.isOpen()) {
    
        sf::Event e;
        
        while (w.pollEvent(e)) {
            
            if (e.type == sf::Event::Closed)
                w.close();
        }
    }
    
    return 0;
}
