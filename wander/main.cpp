
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

//constants
static const int W_WIDTH = 800;   //defines width for window
static const int W_HEIGHT = 600;  //defines height for window
static const int A_BUILD = 6;     //records build no. for window
static const std::string W_TITLE = "Wander b" + std::to_string(A_BUILD);  //defines title for window

//game objects
GameObject* gos[0];
int gosSize = 0;

//function definitions
void input(sf::RenderWindow* w);
void compute();
void illustrate(sf::RenderWindow* w);

//main function
int main(int, char const**)
{
    sf::RenderWindow w(sf::VideoMode(W_WIDTH, W_HEIGHT), W_TITLE, sf::Style::Default); //create window
    
    while (w.isOpen()) { //program loop
    
        input(&w);
        compute();
        illustrate(&w);

    }
    
    return 0;
}

//handles all window input
void input(sf::RenderWindow* w) {
    sf::Event e;
    while (w->pollEvent(e)) {
        
        if (e.type == sf::Event::Closed)
            w->close();
    }
}

//comutes per tick
void compute() {
    
}

//illustrates
void illustrate(sf::RenderWindow* w) {
    
    //clear
    w->clear(sf::Color::Black);
    
    //draw
    for (int i = 0; i < gosSize; i++)
        gos[i]->illustrate(w);
    
    //publish
    w->display();
}
