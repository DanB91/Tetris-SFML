#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
int main() {
    sf::RenderWindow app(sf::VideoMode(800,600), "Tetris");
    Tetris::Game game;
    
    while(game.isRunning()) {
        sf::Event e;

        while(app.pollEvent(e)) {
            game.handleEvent(e);
        }

        game.render(app);

        app.display();
    }

    app.close();

    return 0;
}

