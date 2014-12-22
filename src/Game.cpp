#include <stdexcept>
#include <iostream>
#include "Game.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"
#include "KeyBuffer.hpp"

//TODO: define canPieceTakeAction()
//TODO: need to unify block locations.  First look at line 65 of Pit.cpp

static constexpr float PIECE_MOVE_TIME = .5; //seconds
static constexpr float PIT_WALL_WIDTH = 5; //how many pixels is the wall of the pit?
static const sf::Vector2f PIT_OFFSET = sf::Vector2f(275, 45);

static const sf::Vector2f PIECE_SPAWN_OFFSET = {PIT_OFFSET.x + PIT_WALL_WIDTH, PIT_OFFSET.y + PIT_WALL_WIDTH};
static const PitCoordinates PIECE_SPAWN_COORDINATES = {4,0};
static const sf::Vector2f NEXT_PIECE_OFFSET = {PIT_OFFSET.x - 100, PIT_OFFSET.y};
static const sf::Vector2f SCORE_POSITION = {NEXT_PIECE_OFFSET.x, NEXT_PIECE_OFFSET.y + 100};

static bool isPieceStopped = false;

//prototypes for helper functions
static UPtr<Piece> generateNextPiece(const TextureHolder&);
static bool canPieceMoveDown(const Piece &piece, const Pit &pit);
static bool canPieceMoveLeft(const Piece &piece, const Pit &pit);
static bool canPieceMoveRight(const Piece &piece, const Pit &pit);
static bool canPieceRotateRight(const Piece &piece, const Pit &pit);
static bool canPieceRotateLeft(const Piece &piece, const Pit &pit);
static void dropPiece(Piece& piece, const Pit& pit);
static bool shouldGameEnd(const Piece& piece, const Pit& pit);


Game::Game(const std::string &resourcesPath)
    : mIsRunning(true), mIsGameOver(false),
      mResourcesPath(resourcesPath), mImagesPath(resourcesPath + "/images/"),
      mFontsPath(resourcesPath + "/fonts/") {

    loadResources();
    initGameState();
}

void Game::initGameState() {
    mPit = makeUPtr<Pit>(mTextureHolder.get(TextureID::Pit), PIT_OFFSET);

    auto pitBounds = mPit->boundingRect();
    mScore = makeUPtr<Score>(mFontHolder, sf::Vector2f(pitBounds.left + pitBounds.width + 100, NEXT_PIECE_OFFSET.y));

    mGameOverText = makeUPtr<sf::Text>("\t\t\tGame Over!\nPress Enter to start a new game.", mFontHolder.get(FontID::GameFont));

    mGameOverText->setPosition(110,500);

    mNextPiece = generateNextPiece(mTextureHolder);
    mCurrentPiece = makeUPtr<I>(mTextureHolder, PIECE_SPAWN_OFFSET);
    mCurrentPiece->moveToCoords(PIECE_SPAWN_COORDINATES);
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

    mFontHolder.load(FontID::GameFont, mFontsPath + "simplistic_regular.ttf");



}

static bool canPieceMoveDown(const Piece &piece, const Pit &pit) {
    Piece tmpPiece = piece;
    tmpPiece.moveDown();

    for (auto& coords : tmpPiece.coordinatesOfAllBlocks()) {
        if (!pit.isBlockInBounds(coords) || pit.isBlockAtCoordinates(coords)) {
            return false;
        }
    }

    return true;
}
static bool canPieceMoveLeft(const Piece &piece, const Pit &pit) {
    Piece tmpPiece = piece;
    tmpPiece.moveLeft();

    for (auto& coords : tmpPiece.coordinatesOfAllBlocks()) {
        if (!pit.isBlockInBounds(coords) || pit.isBlockAtCoordinates(coords)) {
            return false;
        }
    }
    return true;
}

static bool canPieceMoveRight(const Piece &piece, const Pit &pit) {
    Piece tmpPiece = piece;
    tmpPiece.moveRight();

    for (auto& coords : tmpPiece.coordinatesOfAllBlocks()) {
        if (!pit.isBlockInBounds(coords) || pit.isBlockAtCoordinates(coords)) {
            return false;
        }
    }

    return true;
}

static bool canPieceRotateRight(const Piece &piece, const Pit &pit) {
    Piece tmpPiece = piece;
    tmpPiece.rotateRight();

    for (auto& coords : tmpPiece.coordinatesOfAllBlocks()) {
        if (!pit.isBlockInBounds(coords) || pit.isBlockAtCoordinates(coords)) {
            return false;
        }
    }

    return true;
}

static bool canPieceRotateLeft(const Piece &piece, const Pit &pit) {
    Piece tmpPiece = piece;
    tmpPiece.rotateLeft();

    for (auto& coords : tmpPiece.coordinatesOfAllBlocks()) {
        if (!pit.isBlockInBounds(coords) || pit.isBlockAtCoordinates(coords)) {
            return false;
        }
    }

    return true;
}
static void dropPiece(Piece& piece, const Pit& pit) {
    while (canPieceMoveDown(piece, pit)) {
        piece.moveDown();
    }

    isPieceStopped = true;
}

void Game::resetGameState() {
    initGameState();
}

void Game::handleKeyEvent(const sf::Event &e) {
    KeyBuffer::processEvent(e);

    if (KeyBuffer::hasKeys()) {
        if (!mIsGameOver) {
            switch(KeyBuffer::popKey()) {
            case sf::Keyboard::Left:
                if (canPieceMoveLeft(*mCurrentPiece, *mPit)) mCurrentPiece->moveLeft();
                break;
            case sf::Keyboard::Right:
                if (canPieceMoveRight(*mCurrentPiece, *mPit)) mCurrentPiece->moveRight();
                break;
            case sf::Keyboard::Down:
                if (canPieceMoveDown(*mCurrentPiece, *mPit)) mCurrentPiece->moveDown();
                break;
            case sf::Keyboard::Space:
                dropPiece(*mCurrentPiece, *mPit);
                break;
            case sf::Keyboard::Z:
                if (canPieceRotateLeft(*mCurrentPiece, *mPit)) mCurrentPiece->rotateLeft();
                break;
            case sf::Keyboard::X:
                if (canPieceRotateRight(*mCurrentPiece, *mPit)) mCurrentPiece->rotateRight();
                break;
            case sf::Keyboard::Escape:
                mIsRunning = false;
                break;
            default:
                break;

            }
        }
        else {
            switch(KeyBuffer::popKey()) {
            case sf::Keyboard::Return:
                mIsGameOver = false;
                initGameState();
                break;
            default:
                break;
            }
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

static bool shouldGameEnd(const Piece& piece, const Pit& pit) {
    for (auto& block : piece.blocks()) {
        if (pit.isBlockAtCoordinates(block.coordinates())) {
            return false;
        }
    }

    return true;
}

static UPtr<Piece> generateNextPiece(const TextureHolder &textureHolder) {
    PieceTypes chosenPiece = static_cast<PieceTypes>(rand() % NUM_PIECE_TYPES);

    //TODO change to generate correct peices
    switch(chosenPiece) {
    case PieceTypes::I:
        return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::O:
        return makeUPtr<O>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::J:
        return makeUPtr<J>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::L:
        return makeUPtr<L>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::Z:
        return makeUPtr<Z>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::S:
        return makeUPtr<S>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    case PieceTypes::T:
        return makeUPtr<T>(textureHolder, NEXT_PIECE_OFFSET);
        break;
    default:
        assert("This should be unreachable.");
        return nullptr;

    }
}



void Game::update(const sf::Time &delta) {
    static float secondsSinceLastPieceMove = 0;
    secondsSinceLastPieceMove += delta.asSeconds();

    if(!mIsGameOver) {
        //timer is up, or we are waiting for a new block
        if (secondsSinceLastPieceMove > PIECE_MOVE_TIME || isPieceStopped) {
            secondsSinceLastPieceMove = 0;

            if (!isPieceStopped && canPieceMoveDown(*mCurrentPiece, *mPit)) {
                mCurrentPiece->moveDown();
            }
            else { //cannot move down anymore.
                isPieceStopped = false;

                //1. add blocks to pit
                for (auto& block : mCurrentPiece->blocks()) {
                    mPit->putBlock(block);
                }


                int scoreToAdd = 0;

                //2. if there are full lines, we want to delete them and add to score
                switch(mPit->deleteFullRows()){
                case 1:
                    scoreToAdd = 40;
                    break;
                case 2:
                    scoreToAdd = 100;
                    break;
                case 3:
                    scoreToAdd = 300;
                    break;
                case 4:
                    scoreToAdd = 1200;
                    break;

                }

                mScore->setValue(mScore->value() + scoreToAdd);

                //3. if there is room, spawn new piece, else lose

                mCurrentPiece = std::move(mNextPiece);
                mCurrentPiece->moveToOffset(PIECE_SPAWN_OFFSET);
                mCurrentPiece->moveToCoords(PIECE_SPAWN_COORDINATES);
                mNextPiece = generateNextPiece(mTextureHolder);

                if (!shouldGameEnd(*mCurrentPiece, *mPit)) {
                    mIsGameOver = true;

                }

            }

        }
    }

}

void Game::render(sf::RenderTarget &rt) const {
    rt.clear(sf::Color(34,34,34));
    rt.draw(*mPit);
    rt.draw(*mScore);
    rt.draw(*mNextPiece);
    rt.draw(*mCurrentPiece);

    if (mIsGameOver) {
        rt.draw(*mGameOverText);
    }
    
}

