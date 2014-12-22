#pragma once

#include <SFML/Graphics.hpp>
#include "Pit.hpp"
#include "ResourceHolder.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"
#include "Score.hpp" 

class Game : sf::NonCopyable {

public:
    Game(const std::string &resourcesPath);

    void handleEvent(const sf::Event &e);
    void update(const sf::Time &delta);
    void render(sf::RenderTarget &rt) const;
    bool isRunning() const noexcept;
    void resetGameState();

private:
    UPtr<Pit> mPit;
    UPtr<Piece> mNextPiece;
    UPtr<Piece> mCurrentPiece;
    UPtr<Score> mScore;
    UPtr<sf::Text> mGameOverText;

    TextureHolder mTextureHolder;
    FontHolder mFontHolder;

    bool mIsRunning;
    bool mIsGameOver;
    std::string mResourcesPath;
    std::string mImagesPath;
    std::string mFontsPath;



    void loadResources();
    void initGameState();
    void handleKeyEvent(const sf::Event &e);


    
};

