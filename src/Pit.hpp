#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"
#include "Pieces.hpp"



class Pit : public sf::Drawable,
        sf::NonCopyable {

public:
    static constexpr int HEIGHT = 20;
    static constexpr int WIDTH = 10;

    Pit(const sf::Texture &pitTexture, const sf::Vector2f &pos);

    bool isBlockAtCoordinates(const PitCoordinates &coords) const;
    bool isBlockInBounds(const PitCoordinates &coords) const;
    void putBlockAtCoords(UPtr<Block> block, const PitCoordinates &coordinates); 

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Sprite mPitSprite;
    Array2D<UPtr<Block>, WIDTH, HEIGHT> mBlocks; 

};





