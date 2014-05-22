#pragma once

#include <SFML/Graphics.hpp>
#include "Pit.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"

namespace Tetris {

    class Game : sf::NonCopyable {

        public:
            Game();

            void handleEvent(const sf::Event &e);
            void update(const sf::Time &delta);
            void render(sf::RenderTarget &rt) const;
            bool isRunning() const noexcept;

        private:
            UPtr<Pit> mPit;
            UPtr<Piece> mNextPiece;
            TextureHolder mTextureHolder;
            bool mIsRunning;


            void loadResources();
            void handleKeyEvent(const sf::Event &e);


    
    };
}
