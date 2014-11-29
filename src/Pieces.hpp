#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include <ostream>
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pit.hpp"

class Block : public sf::Drawable {
public:
    //pos represent position in pixels
    Block(const sf::Texture &texture, const sf::Vector2f &pixelPosition, const PitCoordinates &coords);

    //newPos is in block coordinates, while offset uses pixel measurements
    void moveAbsolute(const PitCoordinates &newPos, const sf::Vector2f& offset);
    void moveDown();

    const sf::Vector2f& getPosition() const;
    const PitCoordinates& coordinates() const;
    PitCoordinates& coordinates();
    
    friend std::ostream& operator<<(std::ostream &os, const Block &block);


private:
    sf::Sprite mBlockSprite;
    PitCoordinates mCoordinates;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


};

class Piece : public sf::Drawable{
public:
    const std::array<PitCoordinates, 4>& coordinatesOfAllBlocks() const;
    const std::array<Block, 4> blocks() const;

    void rotateLeft();
    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveToOffset(const sf::Vector2f& offset); //moves piece to a pixel position
    void moveToCoords(const PitCoordinates &coordsOfTopLeftBlock);

protected:
    Piece(const Array2D<PitCoordinates,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2f &pixelPosition);

private:
    int mCurrentRotation = 0;
    sf::Vector2f mOffset;
    Array2D<PitCoordinates,4,4> mRotatationPositions;
    std::array<Block,4> mBlocks;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};


class I : public Piece{
public:
    //pos represent starting position in pixels
    I(const TextureHolder &textures, const sf::Vector2f &pos);

};


class J : public Piece{
public:
    //pos represent starting position in pixels
    J(const TextureHolder &textures, const sf::Vector2f &pos);

};

class L : public Piece{
public:
    //pos represent starting position in pixels
    L(const TextureHolder &textures, const sf::Vector2f &pos);

};
class O : public Piece{
public:
    //pos represent starting position in pixels
    O(const TextureHolder &textures, const sf::Vector2f &pos);

};
class S : public Piece{
public:
    //pos represent starting position in pixels
    S(const TextureHolder &textures, const sf::Vector2f &pos);

};
class Z : public Piece{
public:
    //pos represent starting position in pixels
    Z(const TextureHolder &textures, const sf::Vector2f &pos);

};
class T : public Piece{
public:
    //pos represent starting position in pixels
    T(const TextureHolder &textures, const sf::Vector2f &pos);

};

enum class PieceTypes {
    I = 0,
    J,
    L,
    O,
    S,
    Z, 
    T
};


constexpr int NUM_PIECE_TYPES = 7;
