///STD
#include <iostream>

///API
#include <SFML/Graphics.hpp>

///HEADERS
#include "Level.h"

int main () {

    lvl::Level * gmPoint = new lvl::MainMenu;

    sf::RenderWindow window (sf::VideoMode(800,600), "Plonk 0.0.1");

    while (window.isOpen()) {
        lvl::Section next = gmPoint->seq(window);
        if (next == lvl::Section::End)
            return 0;

        window.clear();
        for (auto& d : gbl::toDraw)
            window.draw(*d);
        window.display();
    }
}
