#include "Pieces.hpp"
#include <iostream>

namespace Tetris {

    static void moveBlocksToNewPositions(std::array<UPtr<Block>,4> &blocks, const std::array<sf::Vector2i,4> &rotationPosition){
        for(size_t i = 0; i < blocks.size(); i++) {
            std::cout << "Block " << i << std::endl;
            std::cout << "Block original pos: " << *blocks[i] << std::endl;

            const sf::Vector2i &blockPosition = rotationPosition[i];
            blocks[i]->move(blockPosition);

            std::cout << "Rotation Vector: X:" << blockPosition.x << " Y: " << blockPosition.y << std::endl;
            std::cout << "Block new pos: " << *blocks[i] << std::endl << std::endl;
        }
    }

    std::ostream& operator<<(std::ostream &os, const Block &block)
    {
        os << "X: " << block.mBlockSprite.getPosition().x << " Y: " << block.mBlockSprite.getPosition().y;
    }


    Block::Block(const sf::Texture &texture, const sf::Vector2u &pixelPosition)
        : mBlockSprite(texture)
    {
        mBlockSprite.setPosition(sf::Vector2f(pixelPosition));
    }

    void Block::move(const sf::Vector2i &newPos) {
        sf::Vector2u texSize(mBlockSprite.getTextureRect().width, 
                                     mBlockSprite.getTextureRect().height);


        mBlockSprite.setPosition(newPos.x * texSize.x, newPos.y * texSize.y);

    }



    void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(mBlockSprite, states);
    }

    
    Piece::Piece(const Array2D<sf::Vector2i,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2u &piecePixelPosition) 
        :mCurrentRotation(0), mOffset(0,0), mRotatationPositions(rotationPositions)
    {
        int i = 0;
        for(auto &blockPosition : mRotatationPositions[mCurrentRotation]) {
             mPtrBlocks[i++] = makeUPtr<Block>(blockTexture, piecePixelPosition + 
                    sf::Vector2u(blockPosition.x * blockTexture.getSize().x, blockPosition.y * blockTexture.getSize().y));
        }
    }

    void Piece::rotateRight() {
       mCurrentRotation++;
       mCurrentRotation %= mRotatationPositions.size();
       moveBlocksToNewPositions(mPtrBlocks, mRotatationPositions[mCurrentRotation]);
    }

    void Piece::rotateLeft() {
       mCurrentRotation--;
       mCurrentRotation %= mRotatationPositions.size();
       moveBlocksToNewPositions(mPtrBlocks, mRotatationPositions[mCurrentRotation]);
    }

    void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for(auto &block : mPtrBlocks){
            target.draw(*block, states);
        }
    }

    I::I(const TextureHolder &textures, const sf::Vector2u &pos)
        :Piece({{
                {{{0,0},{0,1},{0,2},{0,3}}},
                {{{1,1},{0,1},{-1,1},{-2,1}}},
                {{{0,2},{0,1},{0,0},{0,-1}}},
                {{{-1,1},{0,1},{1,1},{2,1}}},
                }}, 
                textures.get(TextureID::I), pos)
    {}

    J::J(const TextureHolder &textures, const sf::Vector2u &pos)
        :Piece({{
                {{{1,0},{1,1},{1,2},{0,2}}},
                {{{2,1},{1,1},{0,1},{0,0}}},
                {{{1,2},{1,1},{1,0},{2,0}}},
                {{{0,1},{1,1},{2,1},{2,2}}},
                }}, 
                textures.get(TextureID::J), pos)
    {}



}
