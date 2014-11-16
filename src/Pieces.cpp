#include "Pieces.hpp"
#include "Pit.hpp"
#include <iostream>




static void moveBlocksToNewPositions(std::array<UPtr<Block>,4> &blocks, const std::array<PitCoordinates,4> &rotationPosition, const sf::Vector2f& offset){
    for(auto i = 0u; i < blocks.size(); i++) {
        DBGMSG("Block " << i);
        DBGMSG("Block original pos: " << *blocks[i]);

        const PitCoordinates& blockPosition = rotationPosition[i];
        blocks[i]->move(blockPosition, offset);

        DBGMSG("Rotation Vector: X:" << blockPosition.x << " Y: " << blockPosition.y);
        DBGMSG("Block new pos: " << *blocks[i]);
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

void Block::move(const PitCoordinates& newPos, const sf::Vector2f& offset=sf::Vector2f(0,0) ) {
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

Piece::Piece(const Array2D<PitCoordinates,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2f &offsetPosition)
    :mOffset(offsetPosition), mRotatationPositions(rotationPositions),
    mBlocks{{
        makeUPtr<Block>(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][0].x * blockTexture.getSize().x, rotationPositions[0][0].y * blockTexture.getSize().y)),
        makeUPtr<Block>(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][1].x * blockTexture.getSize().x, rotationPositions[0][1].y * blockTexture.getSize().y)),
        makeUPtr<Block>(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][2].x * blockTexture.getSize().x, rotationPositions[0][2].y * blockTexture.getSize().y)),
        makeUPtr<Block>(blockTexture, offsetPosition +
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

    for(auto& blockPositions : mRotatationPositions) {
        for(auto& blockPosition : blockPositions) {
            blockPosition.x--;
        }
    }
    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}
void Piece::moveRight() {

    for(auto& blockPositions : mRotatationPositions) {
        for(auto& blockPosition : blockPositions) {
            blockPosition.x++;
        }
    }

    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}

void Piece::moveDown() {
    for(auto& blockPositions : mRotatationPositions) {
        for(auto& blockPosition : blockPositions) {
            blockPosition.y++;
        }
    }
    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}

void Piece::moveToOffset(const sf::Vector2f& offset) {
    mOffset = offset;

    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}
int Piece::bottom() const {
    int highestY = 0;

    for (auto& blockPos : mRotatationPositions[mCurrentRotation]) {
        highestY = (blockPos.y > highestY) ? blockPos.y : highestY;
    }

    return highestY;
}
int Piece::right() const {
    int highestX = 0;

    for (auto& blockPos : mRotatationPositions[mCurrentRotation]) {
        highestX = (blockPos.x > highestX) ? blockPos.x : highestX;
    }

    return highestX;
}

int Piece::left() const {
    int lowestX = Pit::WIDTH;

    for (auto& blockPos : mRotatationPositions[mCurrentRotation]) {
        lowestX = (blockPos.x < lowestX) ? blockPos.x : lowestX;
    }

    return lowestX;
}

std::array<UPtr<Block>,4>& Piece::takeBlocks() {
    return mBlocks;
}

const PitCoordinates& Piece::coordinatesForBlock(const UPtr<Block> &block) const {
    int i = 0;

    for (auto& blockInPiece : mBlocks) {
        if (block == blockInPiece) {
            break;
        }
        i++;
    }

   return mRotatationPositions.at(mCurrentRotation).at(i);
}

void Piece::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto &block : mBlocks){
        target.draw(*block, states);
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




