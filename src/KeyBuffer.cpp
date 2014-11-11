#include "KeyBuffer.hpp"
#include <queue>
#include <cassert>

namespace KeyBuffer {
    static std::queue<sf::Keyboard::Key> keysReleased;

    void processEvent(const sf::Event &e) {
        switch(e.type) {
            case sf::Event::KeyReleased:
                keysReleased.push(e.key.code);
                break;
            default:
                break;
        }
    }


    sf::Keyboard::Key popKey() {
        assert(!keysReleased.empty() && "KeyBuffer is empty.  This function should not be called");

        sf::Keyboard::Key key = keysReleased.front();
        keysReleased.pop();

        return key;

    }

    bool hasKeys() {
        return !keysReleased.empty(); 
    }
}
