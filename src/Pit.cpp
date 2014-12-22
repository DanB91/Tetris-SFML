#include "Pit.hpp"
#include "Pieces.hpp"


    Pit::Pit(const sf::Texture &pitTexture, const sf::Vector2f &pos)
:mPitSprite(pitTexture)
{
    mPitSprite.setPosition(pos);
}

void Pit::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(mPitSprite, states);

    for (auto& blockRow : mBlocks) {
        for (auto& block : blockRow) {
            if (block) {
                target.draw(*block, states);
            }
        }
    }
}


sf::FloatRect Pit::boundingRect() const {
    return mPitSprite.getGlobalBounds();
}

bool Pit::isBlockInBounds(const PitCoordinates &coords) const {
    return coords.column < Pit::WIDTH && coords.column >= 0 && coords.row >= 0 &&
        coords.row < Pit::HEIGHT;
}

bool Pit::isBlockAtCoordinates(const PitCoordinates &coords) const {
    return  mBlocks.at(coords.row).at(coords.column) != nullptr;

}

static bool isRowFull(const std::array<UPtr<Block>, Pit::WIDTH>& row) {
    for (auto& block : row) {
        if (!block) {
            return false;
        }
    }

    return true;
}

void Pit::putBlock(const Block& block) {
    mBlocks.at(block.coordinates().row).at(block.coordinates().column) = makeUPtr<Block>(block);

    if (isRowFull(mBlocks[block.coordinates().row])) {
        mLocationOfFullRows.push_back(block.coordinates().row);
    }
}


static void deleteRow(int rowNum, Array2D<UPtr<Block>, Pit::HEIGHT, Pit::WIDTH>& blocks) {

    //delete row
    std::for_each(blocks[rowNum].begin(), blocks[rowNum].end(), [](UPtr<Block>& block){block.reset();});

    //move rows down
    for (auto it = blocks.begin() + rowNum; it != blocks.begin(); it--) {
        DBGMSG("Before:" << *it);

        *it = std::move(*(it - 1));

        for (auto& block : *it) {
            if (block) {
                block->moveDown();
            }
        }

        DBGMSG("After:" << *it);
    }

    DBGMSG("Pit:" << blocks);

}
int Pit::deleteFullRows() {

    if (mLocationOfFullRows.size() == 0)
        return 0;

    int numFullRows = 0;

    for (auto& rowNum : mLocationOfFullRows) {
        deleteRow(rowNum, mBlocks);
        numFullRows++;
    }

    mLocationOfFullRows.clear();

    return numFullRows;
}


