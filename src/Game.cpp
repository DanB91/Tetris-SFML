#include <stdexcept>
#include <iostream>
#include "Game.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"
#include "KeyBuffer.hpp"


static constexpr float PIECE_MOVE_TIME = .5; //seconds
static constexpr float PIT_WALL_WIDTH = 5; //how many pixels is the wall of the pit?
static const sf::Vector2f PIT_OFFSET = sf::Vector2f(275, 45);

static const sf::Vector2f PIECE_SPAWN_OFFSET = sf::Vector2f(PIT_OFFSET.x + PIT_WALL_WIDTH, PIT_OFFSET.y + PIT_WALL_WIDTH);
static const sf::Vector2f NEXT_PIECE_OFFSET = sf::Vector2f(PIT_OFFSET.x - 100, PIT_OFFSET.y);

static bool isPieceStopped = false;

//prototypes for helper functions
static UPtr<Piece> generateNextPiece(const TextureHolder&);
static bool canPieceMoveDown(const Piece &piece, const Pit &pit);
static bool canPieceMoveLeft(const Piece &piece, const Pit &pit);
static bool canPieceMoveRight(const Piece &piece, const Pit &pit);
static bool canPieceRotateRight(const Piece &piece, const Pit &pit);
static bool canPieceRotateLeft(const Piece &piece, const Pit &pit);
static void dropPiece(Piece& piece, const Pit& pit);
static bool canSpawn(const Piece& piece, const Pit& pit);

static std::array<UPtr<Block>, 20> blocks; //for test purposes only



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


    mPit = makeUPtr<Pit>(mTextureHolder.get(TextureID::Pit), PIT_OFFSET);
    mNextPiece = generateNextPiece(mTextureHolder); 
    mCurrentPiece = makeUPtr<I>(mTextureHolder, PIECE_SPAWN_OFFSET);

    int pos = 0;
    for (auto& block : blocks) {
        block = makeUPtr<Block>(mTextureHolder.get(TextureID::I), PIECE_SPAWN_OFFSET);
        block->move({0, pos++}, PIECE_SPAWN_OFFSET);
    }
}

//TODO: Need to do collision detection for other blocks
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

void Game::handleKeyEvent(const sf::Event &e) {
    KeyBuffer::processEvent(e);

    if (KeyBuffer::hasKeys()) {
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

static bool canSpawn(const Piece& piece, const Pit& pit) {
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
            return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        case PieceTypes::J:
            return makeUPtr<J>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        case PieceTypes::L:
            return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        case PieceTypes::Z:
            return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        case PieceTypes::S:
            return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        case PieceTypes::T:
            return makeUPtr<I>(textureHolder, NEXT_PIECE_OFFSET);
            break;
        default:
            assert("This should be unreachable.");
            return nullptr;

    }
}



void Game::update(const sf::Time &delta) {
    static float secondsSinceLastPieceMove = 0;
    secondsSinceLastPieceMove += delta.asSeconds();

    //timer is up, or we are waiting for a new block
    if (secondsSinceLastPieceMove > PIECE_MOVE_TIME || isPieceStopped) {
        secondsSinceLastPieceMove = 0;

        if (!isPieceStopped && canPieceMoveDown(*mCurrentPiece, *mPit)) {
            mCurrentPiece->moveDown();
        }
        else { //cannot move down anymore.
            isPieceStopped = false;

            //1. add blocks to pit
            for (auto& block : mCurrentPiece->takeBlocks()) {
                mPit->putBlockAtCoords(std::move(block), mCurrentPiece->coordinatesForBlock(block));
            }

            //

            //2. if there are full lines, we want to delete them and add to score
            
            //3. if there is room, spawn new piece, else lose
            
           if (canSpawn(*mNextPiece, *mPit)) {
               mCurrentPiece = std::move(mNextPiece);
               mCurrentPiece->moveToOffset(PIECE_SPAWN_OFFSET);
               mNextPiece = generateNextPiece(mTextureHolder);
           }

        }

    }

}

void Game::render(sf::RenderTarget &rt) const {
    rt.clear(sf::Color(34,34,34));
    rt.draw(*mPit);
    rt.draw(*mNextPiece);
    rt.draw(*mCurrentPiece);
    
    /*
    for (auto& block : blocks) {
        rt.draw(*block);
    }
    */
}

