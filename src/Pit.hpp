#pragma once

#include <SFML/Graphics.hpp>

namespace Tetris {
    
    class Pit : public sf::Drawable, 
                sf::NonCopyable {

        public:
            Pit(const sf::Texture &pitTexture);

        private:
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            sf::Sprite mPitSprite;
            
    };

}




