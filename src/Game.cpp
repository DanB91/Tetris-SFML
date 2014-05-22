#include <stdexcept>
#include "Game.hpp"
#include "Utility.hpp"
#include "Pieces.hpp"


namespace Tetris {
  static const std::string IMAGES_DIR = "../images/";
  static bool keyWasReleased = true;
  
  Game::Game() 
  :mIsRunning(true)
  {
    loadResources();
  }
  
  
  void Game::loadResources() { 
    mTextureHolder.load(TextureID::Pit, IMAGES_DIR + "Pit.png");
    mTextureHolder.load(TextureID::I, IMAGES_DIR + "I.png");
    mTextureHolder.load(TextureID::J, IMAGES_DIR + "J.png");
    mTextureHolder.load(TextureID::L, IMAGES_DIR + "L.png");
    mTextureHolder.load(TextureID::O, IMAGES_DIR + "O.png");
    mTextureHolder.load(TextureID::S, IMAGES_DIR + "S.png");
    mTextureHolder.load(TextureID::Z, IMAGES_DIR + "Z.png");
    mTextureHolder.load(TextureID::T, IMAGES_DIR + "T.png");
    
    
    mPit = makeUPtr<Pit>(mTextureHolder.get(TextureID::Pit));
    mNextPiece = makeUPtr<I>(mTextureHolder, sf::Vector2u(0,0));
  }

  void Game::handleKeyEvent(const sf::Event &e){
      if (e.type == sf::Event::KeyPressed &&
              e.key.code == sf::Keyboard::X &&
              keyWasReleased) {
          mNextPiece->rotateRight();
          keyWasReleased = false;
      } else if (e.type == sf::Event::KeyReleased) {
          keyWasReleased = true;
      }
  }
  
  bool Game::isRunning() const noexcept {
    return mIsRunning;
  }
  
  void Game::handleEvent(const sf::Event &e) {
      switch(e.type){
      case sf::Event::Closed:
          mIsRunning = false;
          break;
      case sf::Event::KeyPressed:
      case sf::Event::KeyReleased:
          handleKeyEvent(e);

      }



  }
  
  
  void Game::update(const sf::Time &delta) {
  }
  
  void Game::render(sf::RenderTarget &rt) const {
    rt.draw(*mPit);
    rt.draw(*mNextPiece);
  }
  
}
