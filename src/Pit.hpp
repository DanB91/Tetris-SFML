#pragma once

#include <SFML/Graphics.hpp>


class Pit : public sf::Drawable,
        sf::NonCopyable {

public:
    static constexpr int HEIGHT = 20;
    static constexpr int WIDTH = 10;

    Pit(const sf::Texture &pitTexture);

private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    sf::Sprite mPitSprite;

};





