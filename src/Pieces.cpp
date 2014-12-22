#include "Pieces.hpp"
#include "Pit.hpp"
#include <iostream>




static void moveBlocksToNewPositions(std::array<Block,4> &blocks, const std::array<PitCoordinates,4> &rotationPosition, const sf::Vector2f& offset){
    for(auto i = 0u; i < blocks.size(); i++) {
        //DBGMSG("Block " << i);
        //DBGMSG("Block original pos: " << blocks[i]);

        const PitCoordinates& blockPosition = rotationPosition[i];
        blocks[i].moveAbsolute(blockPosition, offset);

        //DBGMSG("Rotation Vector: Row:" << blockPosition.row << " Column: " << blockPosition.column);
        //DBGMSG("Block new pos: " << blocks[i]);
    }
}

std::ostream& operator<<(std::ostream &os, const Block &block)
{
    return os << "X: " << block.getPosition().x << " Y: " << block.getPosition().y;
}


    Block::Block(const sf::Texture &texture, const sf::Vector2f &pixelPosition, const PitCoordinates &coords)
: mBlockSprite(texture), mCoordinates(coords)

{
    mBlockSprite.setPosition(sf::Vector2f(pixelPosition));
}


void Block::moveAbsolute(const PitCoordinates& newPos, const sf::Vector2f& offset ) {
    sf::Vector2f texSize(mBlockSprite.getTextureRect().width,
            mBlockSprite.getTextureRect().height);

    sf::Vector2f relativePos(newPos.column * texSize.x, newPos.row * texSize.y);
    mBlockSprite.setPosition(relativePos + offset);
    mCoordinates = newPos;
}

void Block::moveDown() {
    mCoordinates.row++;
    const sf::Vector2f& currentPos = mBlockSprite.getPosition();

    mBlockSprite.setPosition(currentPos.x, currentPos.y + mBlockSprite.getTextureRect().height);
}

void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mBlockSprite, states);
}


const sf::Vector2f& Block::getPosition() const {
    return mBlockSprite.getPosition();
}


const PitCoordinates& Block::coordinates() const {
    return mCoordinates;
}


PitCoordinates& Block::coordinates() {
    return mCoordinates;
}


//piece methods

Piece::Piece(const Array2D<PitCoordinates,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2f &offsetPosition)
    :mOffset(offsetPosition), mRotatationPositions(rotationPositions),
    mBlocks{{
        Block(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][0].column * blockTexture.getSize().x, rotationPositions[0][0].row * blockTexture.getSize().y), rotationPositions[0][0]),
        Block(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][1].column * blockTexture.getSize().x, rotationPositions[0][1].row * blockTexture.getSize().y), rotationPositions[0][1]),
        Block(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][2].column * blockTexture.getSize().x, rotationPositions[0][2].row * blockTexture.getSize().y), rotationPositions[0][2]),
        Block(blockTexture, offsetPosition +
                sf::Vector2f(rotationPositions[0][3].column * blockTexture.getSize().x, rotationPositions[0][3].row * blockTexture.getSize().y), rotationPositions[0][3]),
    }}

{}




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
            blockPosition.column--;
        }
    }
    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}
void Piece::moveRight() {

    for(auto& blockPositions : mRotatationPositions) {
        for(auto& blockPosition : blockPositions) {
            blockPosition.column++;
        }
    }

    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}

void Piece::moveDown() {
    for(auto& blockPositions : mRotatationPositions) {
        for(auto& blockPosition : blockPositions) {
            blockPosition.row++;
        }
    }
    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}

void Piece::moveToOffset(const sf::Vector2f& offset) {
    mOffset = offset;

    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);
}


const std::array<Block, 4> Piece::blocks() const {
    return mBlocks;
}


void Piece::moveToCoords(const PitCoordinates &coordsOfTopLeftBlock) {
    PitCoordinates coordOffset;
    coordOffset.column = coordsOfTopLeftBlock.column - mRotatationPositions[mCurrentRotation][0].column;
    coordOffset.row = coordsOfTopLeftBlock.row - mRotatationPositions[mCurrentRotation][0].row;


    for (auto& rotation : mRotatationPositions) {
        for (auto& coords : rotation) {
            coords.column += coordOffset.column;
            coords.row += coordOffset.row;
        }
    }

    moveBlocksToNewPositions(mBlocks, mRotatationPositions[mCurrentRotation], mOffset);


}
const std::array<PitCoordinates, 4>& Piece::coordinatesOfAllBlocks() const {
    return mRotatationPositions[mCurrentRotation];
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

O::O(const TextureHolder &textures, const sf::Vector2f &pos)
    :Piece({{
            {{{0,0},{1,0},{0,1},{1,1}}},
            {{{0,0},{1,0},{0,1},{1,1}}},
            {{{0,0},{1,0},{0,1},{1,1}}},
            {{{0,0},{1,0},{0,1},{1,1}}},
            }},
            textures.get(TextureID::O), pos)
{}

L::L(const TextureHolder &textures, const sf::Vector2f &pos)
    :Piece({{
            {{{0,0},{0,1},{0,2},{1,2}}},
            {{{-1,1},{0,1},{1,1},{-1,2}}},
            {{{0,0},{0,1},{0,2},{-1,0}}},
            {{{-1,1},{0,1},{1,1},{1,0}}},
            }},
            textures.get(TextureID::L), pos)
{}

Z::Z(const TextureHolder &textures, const sf::Vector2f &pos)
    :Piece({{
            {{{0,0},{1,0},{1,1},{2,1}}},
            {{{1,-1},{1,0},{0,0},{0,1}}},
            {{{0,-1},{1,-1},{1,0},{2,0}}},
            {{{1,1},{1,0},{2,0},{2,-1}}},
            }},
            textures.get(TextureID::Z), pos)
{}


S::S(const TextureHolder &textures, const sf::Vector2f &pos)
    :Piece({{
            {{{2,0},{1,0},{1,1},{0,1}}},
            {{{1,1},{1,0},{0,0},{0,-1}}},
            {{{2,-1},{1,-1},{1,0},{0,0}}},
            {{{2,1},{2,0},{1,0},{1,-1}}},
            }},
            textures.get(TextureID::S), pos)
{}

T::T(const TextureHolder &textures, const sf::Vector2f &pos)
    :Piece({{
            {{{0,0},{1,0},{2,0},{1,1}}},
            {{{1,-1},{1,0},{1,1},{0,0}}},
            {{{0,0},{1,0},{2,0},{1,-1}}},
            {{{1,1},{1,0},{1,-1},{2,0}}},
            }},
            textures.get(TextureID::T), pos)
{}

/*

case PieceTypes::T:
    return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
    break;
*/

