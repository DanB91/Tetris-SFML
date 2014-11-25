#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

class Score : public sf::Drawable {

    public:
        Score(const FontHolder &fontHolder, const sf::Vector2f& position);
        int value() const;
        void setValue(int value);
    private:
        int mValue = 0;
        sf::Text mText;

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};



