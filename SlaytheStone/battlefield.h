#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H
#include <QString>
#include<vector>
#include<enemy.h>
#include<card.h>

class Player;
using Enemies= std::vector<Enemy*>;

class BattleField
{
public:
    BattleField(Player* p):_player(p),turn_idx(0){};

    enum class GameStatus{ongoing,win,lose,even};
    enum class TurnOwner{enemy,player};
    Enemies getEnemies() const {return this->_enemies;};
    Enemy* getEnemy(int idx) const {return this->_enemies.at(idx);}
    Player* getPlayer () const {return this->_player;};
    size_t getTurn()     const {return this->turn_idx;};
    void setPlayer(Player* p) {this->_player=p;};
    void setEnemies(Enemy* s) {this->_enemies.push_back(s);};

private:
    Enemies _enemies;
    Player* _player;
    size_t turn_idx;

};

#endif // BATTLEFIELD_H
