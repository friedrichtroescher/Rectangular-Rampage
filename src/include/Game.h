//
// Created by Friedrich Tröscher on 26.02.25.
//

#ifndef CMAKESFMLPROJECT_GAME_H
#define CMAKESFMLPROJECT_GAME_H

#include "Player.h"
#include "Scoreboard.h"
#include "Projectile.h"
#include "Monster.h"


class Game {
public:
    Game();

    std::vector<Projectile> &getProjectiles();

    std::vector<Monster> &getMonsters();

    Player &getPlayer();

    Scoreboard &getScoreboard();

    Player player;
    std::vector<Projectile> projectiles;
    std::vector<Monster> monsters;
    Scoreboard scoreboard;

    void setPlayer(const Player &player);

    void setProjectiles(const std::vector<Projectile> &projectiles);

    void setMonsters(const std::vector<Monster> &monsters);

    void setScoreboard(const Scoreboard &scoreboard);

    std::vector<Combatant *> getAllCombatants();

    void setGameOver();

    bool getGameOver();

protected:
private:
    bool gameOver;
};


#endif //CMAKESFMLPROJECT_GAME_H
