#pragma once

#include <memory>

//types
template <typename T> 
using UPtr = std::unique_ptr<T>;

template <typename T, int numRows, int numColumns> 
using Array2D = std::array<std::array<T,numColumns>,numRows>; 

template <typename T, typename... Args>
UPtr<T> makeUPtr(Args&&... args);

#include "Utility.inl"
