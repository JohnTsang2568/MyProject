#ifndef CARD_H
#define CARD_H

#include <QString>
class Player;
class Enemy;

class Card
{
public:
    enum class CostType{mana,life};
    enum class Status{normal,unplayable};
    enum class Type{act,power,attack,no_type};
    enum class PlayerClass{warrior,warlock,robot,neutral};
    enum class Place{deck,hand,graveyard,vanishyard};

    Card();
    int getCost();
    CostType getCostType() const    {return this->cost_type;};
    Status getStatus() const    {return this->status;};
    Type getType() const    {return this->type;};
    PlayerClass getClass() const    {return this->playerClass;};

    //provide getters for individual card

    void setCostType(CostType t)    {cost_type=t;};
    void setStatus(Status s)    {this->status=s;};
    void setType(Type t)   {this->type=t;};
    void setClass(PlayerClass c)    {this->playerClass=c;};
    void play(Player* player,Enemy* enemy);
    //constructor that may help



private:
    CostType cost_type = CostType::mana;
    Status status=Status::normal;
    Type type=Type::no_type;
    PlayerClass playerClass=PlayerClass::neutral;
    Place place=Place::deck;
    int cost=0;
    std::string name="";
};

#endif // CARD_H
