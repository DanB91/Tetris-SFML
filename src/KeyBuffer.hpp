#ifndef KEYBUFFER_H
#define KEYBUFFER_H

#include <SFML/Graphics.hpp>

namespace KeyBuffer {

    void processEvent(const sf::Event &e);
    sf::Keyboard::Key popKey();
    bool hasKeys();

}

#endif // KEYBUFFER_H
