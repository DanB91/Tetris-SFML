#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Pit.hpp"
#include "ResourceHolder.hpp"


namespace Tetris {

    class Game : sf::NonCopyable {

        public:
            Game();

            void handleEvent(const sf::Event &e);
            void update(const sf::Time &delta);
            void render(sf::RenderTarget &rt) const;
            bool isRunning() const noexcept;

        private:
            std::unique_ptr<Pit> mPit;
            TextureHolder mTextureHolder;
            bool mIsRunning;


            void loadResources();


    
    };
}
