#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

template <typename Identifier, typename Resource>
class ResourceHolder {
public:

    template <typename... Args>
    void load(Identifier id, const std::string &filename, Args... args);

    const Resource &get(Identifier id) const;

private:
    std::map<Identifier, Resource> mResourceMap;
};


enum class TextureID{
    Pit,
    I,
    J,
    L,
    O,
    S,
    T,
    Z
};

typedef ResourceHolder<TextureID, sf::Texture> TextureHolder;







#include "ResourceHolder.inl"



