#pragma once
//
// Created by Friedrich Tröscher on 08.02.25.
//



#include "Direction.h"

//Input just provides some tooling for getting input from the player
class Input {
public:
    static Direction getWASDDirection();

    static bool isShooting();
};


