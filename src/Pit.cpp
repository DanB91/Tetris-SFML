#include "Pit.hpp"

namespace Tetris {

    Pit::Pit(const sf::Texture &pitTexture)
        :mPitSprite(pitTexture)
    {}

    void Pit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(mPitSprite, states);
    }
}



