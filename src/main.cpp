#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"

int main(int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(800,600), "Tetris");
    Game game((argc > 1) ? argv[1] : "../res");
    sf::Clock clock;

    window.setFramerateLimit(60);

    while(game.isRunning()) {
        sf::Event e;

        while(window.pollEvent(e)) {
            game.handleEvent(e);
        }

        game.update(clock.restart());

        window.clear();
        game.render(window);
        window.display();
    }

    window.close();

    return 0;
}

