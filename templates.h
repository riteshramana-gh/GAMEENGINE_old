#pragma once
#include <memory>
#include <utility>

// returns std::unique_ptr<GameT>
template<typename GameT, typename... Args>
std::unique_ptr<GameT> make_game(Args&&... args) {
    return std::make_unique<GameT>(std::forward<Args>(args)...);
}