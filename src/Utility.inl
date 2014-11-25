#include <memory>
#include <type_traits>
#include <utility>


template <typename T, typename... Args>
static std::unique_ptr<T> make_unique_helper(std::false_type, Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template <typename T, typename... Args>
static std::unique_ptr<T> make_unique_helper(std::true_type, Args&&... args) {
    static_assert(std::extent<T>::value == 0,
            "make_unique<T[N]>() is forbidden, please use make_unique<T[]>().");

    typedef typename std::remove_extent<T>::type U;
    return std::unique_ptr<T>(new U[sizeof...(Args)]{std::forward<Args>(args)...});
}

template <typename T, typename... Args>
std::unique_ptr<T> makeUPtr(Args&&... args) {
    return make_unique_helper<T>(std::is_array<T>(), std::forward<Args>(args)...);
}

class Block;

template <size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<UPtr<Block>,size>& blocks) {
    std::string rep = "";

    for (auto& block : blocks) {
        rep += (block) ? "x" : "_";
    }
    os << rep;

    return os; 
}

template <size_t w, size_t h>
std::ostream& operator<<(std::ostream& os, const Array2D<UPtr<Block>,w,h>& blocks) {
    std::string rep = "";

    for (auto& row : blocks) {

        for (auto& block : row) {
            rep += (block) ? "x" : "_";
        }
        rep += "\n";
    }
    os << rep;

    return os; 
}
