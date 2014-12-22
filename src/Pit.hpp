#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.hpp"

class Block;

struct PitCoordinates {
    int column;
    int row;
};

class Pit : public sf::Drawable,
        sf::NonCopyable {

public:
    static constexpr int HEIGHT = 20;
    static constexpr int WIDTH = 10;



    Pit(const sf::Texture &pitTexture, const sf::Vector2f &pos);

    sf::FloatRect boundingRect() const;
    bool isBlockAtCoordinates(const PitCoordinates &coords) const;
    bool isBlockInBounds(const PitCoordinates &coords) const;
    
    void putBlock(const Block& block);

    void clear();  //clears the pit.  used when reseting for a new game
    
    //returns number of rows deleted
    int deleteFullRows();

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Sprite mPitSprite;
    Array2D<UPtr<Block>, HEIGHT, WIDTH> mBlocks; 

    //each element is a row number that points to a full row.
    std::vector<int> mLocationOfFullRows; 

};






