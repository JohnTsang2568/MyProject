#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <QString>
#include<vector>
#include<enemy.h>
#include<card.h>

class Player;
using Enemies= std::vector<Enemy>;

class BattleField
{
public:
    BattleField();

    enum class GameStatus{ongoing,win,lose,even};
    enum class TurnOwner{enemy,player};
    Enemies getEnemies() const {return this->enemies;};
    Player* getPlayer () const {return this->player;};
    size_t getTurn()     const {return this->turn_idx;};
    void setEnemies(Enemy s);

private:
    Enemies enemies;
    Player* player;
    size_t turn_idx;

};

#endif // BATTLEFIELD_H
