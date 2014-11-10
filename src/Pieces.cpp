#include "Pieces.hpp"
#include <iostream>

namespace Tetris {

    static void moveBlocksToNewPositions(std::array<Block,4> &blocks, const std::array<sf::Vector2f,4> &rotationPosition, const sf::Vector2f& offset){
        for(auto i = 0; i < blocks.size(); i++) {
            std::cout << "Block " << i << std::endl;
            std::cout << "Block original pos: " << blocks[i] << std::endl;

            const sf::Vector2f &blockPosition = rotationPosition[i];
            blocks[i].move(blockPosition, offset);

            std::cout << "Rotation Vector: X:" << blockPosition.x << " Y: " << blockPosition.y << std::endl;
            std::cout << "Block new pos: " << blocks[i] << std::endl << std::endl;
        }
    }

    std::ostream& operator<<(std::ostream &os, const Block &block)
    {
        return os << "X: " << block.getPosition().x << " Y: " << block.getPosition().y;
    }


    Block::Block(const sf::Texture &texture, const sf::Vector2f &pixelPosition)
        : mBlockSprite(texture)
        
    {
        mBlockSprite.setPosition(sf::Vector2f(pixelPosition));
    }

    void Block::move(const sf::Vector2f& newPos, const sf::Vector2f& offset=sf::Vector2f(0,0) ) {
        sf::Vector2f texSize(mBlockSprite.getTextureRect().width, 
                                     mBlockSprite.getTextureRect().height);

        sf::Vector2f relativePos(newPos.x * texSize.x, newPos.y * texSize.y);

        mBlockSprite.setPosition(relativePos + offset); 
    }



    void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(mBlockSprite, states);
    }


    const sf::Vector2f& Block::getPosition() const {
        return mBlockSprite.getPosition();
    }





    //piece methods
    
    Piece::Piece(const Array2D<sf::Vector2f,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2f &offsetPosition) 
        :mCurrentRotation(0), mOffset(offsetPosition), mRotatationPositions(rotationPositions),
        mBlocks{{
                Block(blockTexture, offsetPosition +
                        sf::Vector2f(rotationPositions[0][0].x * blockTexture.getSize().x, rotationPositions[0][0].y * blockTexture.getSize().y)),
                Block(blockTexture, offsetPosition +
                        sf::Vector2f(rotationPositions[0][1].x * blockTexture.getSize().x, rotationPositions[0][1].y * blockTexture.getSize().y)),
                Block(blockTexture, offsetPosition +
                        sf::Vector2f(rotationPositions[0][2].x * blockTexture.getSize().x, rotationPositions[0][2].y * blockTexture.getSize().y)),
                Block(blockTexture, offsetPosition +
                        sf::Vector2f(rotationPositions[0][3].x * blockTexture.getSize().x, rotationPositions[0][3].y * blockTexture.getSize().y)),
        }}

    {

    }

    void Piece::rotateRight() {
       mCurrentRotation++;
       mCurrentRotation %= mRotatationPositions.size();
       moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
    }

    void Piece::rotateLeft() {
       mCurrentRotation--;
       mCurrentRotation %= mRotatationPositions.size();
       moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
    }


    void Piece::moveLeft() {

    }
    void Piece::moveRight() {

    }

    void Piece::moveDown() {
        for(auto& blockPositions : mRotatationPositions) {
            for(auto& blockPosition : blockPositions) {
                blockPosition.y++;
            }
        }
       moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
    }

    void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        for(auto &block : mBlocks){
            target.draw(block, states);
        }
    }

    I::I(const TextureHolder &textures, const sf::Vector2f &pos)
        :Piece({{
                {{{0,0},{0,1},{0,2},{0,3}}},
                {{{1,1},{0,1},{-1,1},{-2,1}}},
                {{{0,2},{0,1},{0,0},{0,-1}}},
                {{{-1,1},{0,1},{1,1},{2,1}}},
                }}, 
                textures.get(TextureID::I), pos)
    {}

    J::J(const TextureHolder &textures, const sf::Vector2f &pos)
        :Piece({{
                {{{1,0},{1,1},{1,2},{0,2}}},
                {{{2,1},{1,1},{0,1},{0,0}}},
                {{{1,2},{1,1},{1,0},{2,0}}},
                {{{0,1},{1,1},{2,1},{2,2}}},
                }}, 
                textures.get(TextureID::J), pos)
    {}



}
