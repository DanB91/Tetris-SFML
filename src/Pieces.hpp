#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <map>
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pit.hpp"

namespace Tetris {

    class Block : public sf::Drawable {
        public:
            //pos represent position in pixels
            Block(const sf::Texture &texture, const sf::Vector2u &pixelPosition);
            void move(const sf::Vector2i &newPos);

        private:
            sf::Sprite mBlockSprite;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    };

    class Piece : public sf::Drawable{
        public:
            const std::array<Block,4> &getBlocks() const noexcept;
            void rotateLeft();
            void rotateRight();

        protected:
            Piece(const Array2D<sf::Vector2i,4,4> &rotationPositions, const sf::Texture &blockTexture, const sf::Vector2u &pixelPosition);

        private:
            int mCurrentRotation;
            sf::Vector2i mOffset;
            std::array<UPtr<Block>,4> mPtrBlocks;
            Array2D<sf::Vector2i,4,4> mRotatationPositions;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };


    class I : public Piece{
        public:
            //pos represent starting position in pixels
            I(const TextureHolder &textures, const sf::Vector2u &pos);

    };


    class J : public Piece{
        public:
            //pos represent starting position in pixels
            J(const TextureHolder &textures, const sf::Vector2u &pos);

    };

    class L : public Piece{
        public:
            //pos represent starting position in pixels
            L(const TextureHolder &textures, const sf::Vector2u &pos);

    };
    class O : public Piece{
        public:
            //pos represent starting position in pixels
            O(const TextureHolder &textures, const sf::Vector2u &pos);

    };
    class S : public Piece{
        public:
            //pos represent starting position in pixels
            S(const TextureHolder &textures, const sf::Vector2u &pos);

    };
    class Z : public Piece{
        public:
            //pos represent starting position in pixels
            Z(const TextureHolder &textures, const sf::Vector2u &pos);

    };
    class T : public Piece{
        public:
            //pos represent starting position in pixels
            T(const TextureHolder &textures, const sf::Vector2u &pos);

    };
}
