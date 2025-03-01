#pragma once
//
// Created by Friedrich Tröscher on 26.02.25.
//


#include "Player.h"
#include "Scoreboard.h"
#include "Projectile.h"
#include "Monster.h"

//The game class is used to collect all entities of the game, so that passing the game reference to those entities enables them to access other elements of the game

class Game {
public:
    //after creation of game, it needs to be assigned a player and a scoreboard instance
    //this can't be done with a constructor because the player and scoreboard need a reference to the game object
    Game(sf::RenderWindow *renderWindow);

    std::vector<Projectile> &getProjectiles();

    std::vector<Monster> &getMonsters();

    Player &getPlayer();

    Scoreboard &getScoreboard();

    sf::RenderWindow *getRenderWindow() const;

    void spawnMonsters(int count);

    void setPlayer(const Player &player);

    [[maybe_unused]] void setProjectiles(const std::vector<Projectile> &projectiles);

    [[maybe_unused]] void setMonsters(const std::vector<Monster> &monsters);

    void setScoreboard(const Scoreboard &scoreboard);

    void tickProjectiles();

    [[maybe_unused]] void tickMonsters();

    std::vector<Combatant *> getAllCombatants();

    void setGameOver();

    bool getGameOver() const;

protected:
private:
    Player player;
    std::vector<Projectile> projectiles;
    std::vector<Monster> monsters;
    Scoreboard scoreboard;
    bool gameOver;

    void setRenderWindow(sf::RenderWindow *pointer);

    sf::RenderWindow *renderWindow;
};


