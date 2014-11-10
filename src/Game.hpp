#pragma once

#include <SFML/Graphics.hpp>
#include "Pit.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"

namespace Tetris {

    class Game : sf::NonCopyable {

        public:
            Game(const std::string &imagesPath);

            void handleEvent(const sf::Event &e);
            void update(const sf::Time &delta);
            void render(sf::RenderTarget &rt) const;
            bool isRunning() const noexcept;

        private:
            UPtr<Pit> mPit;
            UPtr<Piece> mNextPiece;
            UPtr<Piece> mCurrentPiece;
            TextureHolder mTextureHolder;
            bool mIsRunning;
            std::string imagesPath;

            void loadResources();
            void handleKeyEvent(const sf::Event &e);


    
    };
}
