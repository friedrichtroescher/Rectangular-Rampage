# Rectangular Rampage

A minimalist, top-down retro shooter featuring wave-based gameplay.

This repository is a project work for the 4th Semester Computer Science Course "Programming in C++", lectured by David
Hackbart at Hochschule für Wirtschaft und Recht Berlin.

## How to Build and Run

1. Create a build directory and navigate into it:
   ```
   mkdir build
   cd build
   ```

2. Run CMake to configure the build:
   ```
   cmake ..
   ```

3. Compile the project:
   ```
   make
   ```

4. Navigate to the `build/bin` directory and execute the program:
   ```
   ./main
   ```

## Game basics

### Movement

Control the Player by using our choice of WASD or arrow buttons.

### Shooting

You can shoot by left mouse click or usage of the spacebar. You shoot in the direction you last walked in.

### Gameplay

Each level spawns Monsters that you need to take care of, but watch out! **They will not leave without a fight**. Make
sure to dodge their projectiles. Once you defeat all Monsters, you level up. A level up **refills your health**, **buffs
your
capabilities** and **spawns a new and stronger wave of Monsters**.

## Licenses

This project is licensed under the MIT License. You are free to use, modify, and distribute it, but you must include the
original licenses and give me a mention, please.

This project was built on the [cmake-sfml-template](https://github.com/SFML/cmake-sfml-project), published under the
public domain. It also uses the PressStart2P-Regular Font, which is published under the Open Font License (OFL).

