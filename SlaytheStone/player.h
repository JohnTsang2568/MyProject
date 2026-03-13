#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include <card.h>
#include <entity.h>

class BattleField;

class Player : public Entity
{
public:
    Player();
    using Hand =std::vector<std::unique_ptr<Card>>;
    void drawCard();
    void playCard();
    void discardCard();
    void vanishCard();
    void suffleCard();
    void sortHandbyCost();



    int mana=0;

private:
    Hand hand;
    BattleField* battle_field;
};

#endif // PLAYER_H
