
#include <stdexcept>
#include <cassert>


template<typename Identifier, typename Resource>
template<typename... Args>
void ResourceHolder<Identifier, Resource>::load(Identifier id, const std::string &filename, Args... args) {
    Resource res;

    if(!res.loadFromFile(filename, std::forward(args)...)){
        throw std::runtime_error("Failed to load " + filename);
    }

    auto inserted = mResourceMap.insert(std::make_pair(id, res));

    assert(inserted.second && "Texture already inserted");
}


template<typename Identifier, typename Resource>
const Resource &ResourceHolder<Identifier, Resource>::get(Identifier id) const{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end() && "Texture not loaded");

    return found->second;

}




