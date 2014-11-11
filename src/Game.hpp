#pragma once

#include <SFML/Graphics.hpp>
#include "Pit.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"


class Game : sf::NonCopyable {

public:
    Game(const std::string &mImagesPath);

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
    std::string mImagesPath;

    void loadResources();
    void handleKeyEvent(const sf::Event &e);


    
};

