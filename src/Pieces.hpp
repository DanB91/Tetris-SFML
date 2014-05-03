#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pit.hpp"

namespace Tetris {

    class Block : public sf::Drawable {
        public:
            //xPos and yPos represent position in pixels
            Block(const sf::Texture &texture, int xPos, int yPos);
            void moveLeft();
            void moveRight();
            void moveUp();
            void moveDown();

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
            Piece(std::array<Block,4> &&blocks);

        private:
            std::array<Block,4>  mBlocks;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };


    class I : public Piece{
        public:
            //xPos and yPos represent starting position in pixels
            I(const TextureHolder &textures, int xPos, int yPos);

    };

}
