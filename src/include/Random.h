//
// Created by Friedrich Tröscher on 01.03.25.
//

#pragma once

#include <random>
#include <stdexcept>

class Random {
public:
    Random();

    int generate();

    [[maybe_unused]] int generate_range(int min, int max);

private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> uniform_dist;
};
