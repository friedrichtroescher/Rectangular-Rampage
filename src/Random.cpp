//
// Created by Friedrich Tröscher on 01.03.25.
//

#include "include/Random.h"
#include <ctime>
#include <limits>

// Constructor
Random::Random()
        : rng(std::random_device{}()), uniform_dist(0, std::numeric_limits<int>::max()) {
    rng.seed(static_cast<unsigned>(std::time(nullptr)));
}

// Function to generate a random number
int Random::generate() {
    return uniform_dist(rng);
}

// Function to generate an integer in range [min, max)
int Random::generate_range(int min, int max) {
    if (min >= max) {
        throw std::invalid_argument("min must be less than max");
    }
    std::uniform_int_distribution<int> dist(min, max - 1);
    return dist(rng);
}