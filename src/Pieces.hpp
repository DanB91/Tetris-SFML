#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include <ostream>
#include "ResourceHolder.hpp"
#include "Utility.hpp"



class Block : public sf::Drawable {
public:
    //pos represent position in pixels
    Block(const sf::Texture &texture, const sf::Vector2f &pixelPosition);
    
    //newPos is in block coordinates, while offset uses pixel measurements
    void move(const PitCoordinates &newPos, const sf::Vector2f& offset);

    const sf::Vector2f& getPosition() const;

    friend std::ostream& operator<<(std::ostream &os, const Block &block);


private:
    sf::Sprite mBlockSprite;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;


};

class Piece : public sf::Drawable{
public:
    std::array<UPtr<Block>,4>& takeBlocks();
    int bottom() const; //gets the y position of the bottom most block.  Used to see if piece should keep moving down
    int left() const; //gets the x position of the left most block.  Used to see if piece should keep moving down
    int right() const; //gets the x position of the right most block.  Used to see if piece should keep moving down
    const PitCoordinates& coordinatesForBlock(const UPtr<Block> &block) const;

    void rotateLeft();
    void rotateRight();
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveToOffset(const sf::Vector2f& offset); //moves piece to a pixel position


protected:
    Piece(const Array2D<PitCoordinates,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2f &pixelPosition);

private:
    int mCurrentRotation = 0;
    sf::Vector2f mOffset;
    Array2D<PitCoordinates,4,4> mRotatationPositions;
    std::array<UPtr<Block>,4> mBlocks;

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
