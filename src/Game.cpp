#include <stdexcept>
#include <iostream>
#include "Game.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"


namespace Tetris {
    static bool keyWasReleased = true;
    static constexpr float PIECE_MOVE_TIME = .5; //seconds
    static const sf::Vector2f PIECE_SPAWN_OFFSET = sf::Vector2f(280, 50);

    Game::Game(const std::string &imagesPath)
            : mIsRunning(true), imagesPath(imagesPath) {
        loadResources();
    }


    void Game::loadResources() {
        mTextureHolder.load(TextureID::Pit, imagesPath + "Pit.png");
        mTextureHolder.load(TextureID::I, imagesPath + "I.png");
        mTextureHolder.load(TextureID::J, imagesPath + "J.png");
        mTextureHolder.load(TextureID::L, imagesPath + "L.png");
        mTextureHolder.load(TextureID::O, imagesPath + "O.png");
        mTextureHolder.load(TextureID::S, imagesPath + "S.png");
        mTextureHolder.load(TextureID::Z, imagesPath + "Z.png");
        mTextureHolder.load(TextureID::T, imagesPath + "T.png");

        
        mPit = makeUPtr<Pit>(mTextureHolder.get(TextureID::Pit));
        mNextPiece = makeUPtr<I>(mTextureHolder, sf::Vector2f(0, 0));
        mCurrentPiece = makeUPtr<I>(mTextureHolder, PIECE_SPAWN_OFFSET);

    }

    void Game::handleKeyEvent(const sf::Event &e) {
        if (e.type == sf::Event::KeyPressed &&
                e.key.code == sf::Keyboard::X &&
                keyWasReleased) {
            mCurrentPiece->rotateRight();
            keyWasReleased = false;
        } else if (e.type == sf::Event::KeyReleased) {
            keyWasReleased = true;
        }
    }

    bool Game::isRunning() const noexcept {
        return mIsRunning;
    }

    void Game::handleEvent(const sf::Event &e) {
        switch (e.type) {
            case sf::Event::Closed:
                mIsRunning = false;
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
                handleKeyEvent(e);
            default:
                break;

        }


    }


    void Game::update(const sf::Time &delta) {
        static float secondsSinceLastPieceMove = 0;
        secondsSinceLastPieceMove += delta.asSeconds();
        
        //std::cout << secondsSinceLastPieceMove << "\n";

        if (secondsSinceLastPieceMove > PIECE_MOVE_TIME) {
            secondsSinceLastPieceMove = 0;
            mCurrentPiece->moveDown();
        }

    }

    void Game::render(sf::RenderTarget &rt) const {
        rt.draw(*mPit);
        rt.draw(*mNextPiece);
        rt.draw(*mCurrentPiece);
    }

}
