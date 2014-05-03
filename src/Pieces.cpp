#include "Pieces.hpp"
#include <iostream>

namespace Tetris {

    Block::Block(const sf::Texture &texture, int xPos, int yPos)
        : mBlockSprite(texture)
    {
        mBlockSprite.setPosition(xPos, yPos);
    }

    
    void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(mBlockSprite, states);
    }

    
    Piece::Piece(std::array<Block,4> &&blocks)
        : mBlocks(blocks)
    {}
   

    void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for(auto block : mBlocks){
            target.draw(block, states);
        }
    }

    I::I(const TextureHolder &textures, int xPos, int yPos)
        : Piece(std::array<Block,4>{{Block(textures.get(TextureID::I), xPos, yPos),
                    Block(textures.get(TextureID::I), xPos, yPos + textures.get(TextureID::I).getSize().y), 
                    Block(textures.get(TextureID::I), xPos, yPos + textures.get(TextureID::I).getSize().y * 2), 
                    Block(textures.get(TextureID::I), xPos, yPos + textures.get(TextureID::I).getSize().y * 3)}})
    {}


}
