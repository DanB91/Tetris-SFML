#include "Pit.hpp"


    Pit::Pit(const sf::Texture &pitTexture, const sf::Vector2f &pos)
:mPitSprite(pitTexture)
{
    mPitSprite.setPosition(pos);
}

void Pit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mPitSprite, states);

    for (auto& blockRow : mBlocks) {
        for (auto& block : blockRow) {
            if (block) {
                target.draw(*block, states);
            }
        }
    }
}



void Pit::putBlockAtCoords(UPtr<Block> block, const PitCoordinates &coordinates) {
    mBlocks.at(coordinates.x).at(coordinates.y) = std::move(block);
}
