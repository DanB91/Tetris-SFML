#pragma once

#include <memory>

//types
template <typename T> using UPtr = std::unique_ptr<T>;


template <typename T, typename... Args>
UPtr<T> makeUPtr(Args&&... args);

#include "Utility.inl"
