#include <stdexcept>
#include <iostream>
#include "Game.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"
#include "KeyBuffer.hpp"


static constexpr float PIECE_MOVE_TIME = .5; //seconds
static const sf::Vector2f PIECE_SPAWN_OFFSET = sf::Vector2f(280, 50);

Game::Game(const std::string &imagesPath)
    : mIsRunning(true), mImagesPath(imagesPath) {

        if(mImagesPath[mImagesPath.length()] != '/') {
            mImagesPath += std::string("/");
        }

        loadResources();
    }


void Game::loadResources() {
    mTextureHolder.load(TextureID::Pit, mImagesPath + "Pit.png");
    mTextureHolder.load(TextureID::I, mImagesPath + "I.png");
    mTextureHolder.load(TextureID::J, mImagesPath + "J.png");
    mTextureHolder.load(TextureID::L, mImagesPath + "L.png");
    mTextureHolder.load(TextureID::O, mImagesPath + "O.png");
    mTextureHolder.load(TextureID::S, mImagesPath + "S.png");
    mTextureHolder.load(TextureID::Z, mImagesPath + "Z.png");
    mTextureHolder.load(TextureID::T, mImagesPath + "T.png");


    mPit = makeUPtr<Pit>(mTextureHolder.get(TextureID::Pit));
    mNextPiece = makeUPtr<I>(mTextureHolder, sf::Vector2f(0, 0));
    mCurrentPiece = makeUPtr<I>(mTextureHolder, PIECE_SPAWN_OFFSET);

}

void Game::handleKeyEvent(const sf::Event &e) {
    KeyBuffer::processEvent(e);

    if (KeyBuffer::hasKeys()) {
        switch(KeyBuffer::popKey()) {
            case sf::Keyboard::Left:
                mCurrentPiece->moveLeft();
                break;
            case sf::Keyboard::Right:
                mCurrentPiece->moveRight();
                break;
            case sf::Keyboard::Z:
                mCurrentPiece->rotateLeft();
                break;
            case sf::Keyboard::X:
                mCurrentPiece->rotateRight();
            default:
                break;
        }
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

