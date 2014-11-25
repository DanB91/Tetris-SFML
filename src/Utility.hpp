#pragma once

#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <array>

//types
template <typename T> 
using UPtr = std::unique_ptr<T>;

template <typename T, int numRows, int numColumns> 
using Array2D = std::array<std::array<T,numColumns>,numRows>; 

template <typename T, typename... Args>
UPtr<T> makeUPtr(Args&&... args);


#ifdef DEBUG
    #define DBGMSG(msg) \
        std::cout << "DBG: " << __FILE__ << "(" << __LINE__ << ") " \
        << msg << std::endl
#else
    #define DBGMSG(msg)
#endif

#include "Utility.inl"
