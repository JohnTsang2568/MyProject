#ifndef CARD_H
#define CARD_H

#include <QString>
#include<jsonparser.h>
#include<ieffect.h>

class Player;
class Enemy;

class Card
{
public:

    Card(const CardData& data,const EffectFactory & factory)
    {
        id=data.id;
        name=data.name;
        cost=data.cost;
        for(const auto & now:data.effects)
        {
            auto effect=factory.MakeCard(now);
            if(effect){
            effects.push_back(std::move(effect));
            }
        }
    }

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

    void play(Player* source, const std::vector<Entity*>& targets) const {
        EffectContext ctx;
        ctx.player = source;
        ctx.targets = targets;
        for (const auto& effect : effects) {
            effect->Execute(ctx);
        }
    }

private:
    CostType cost_type = CostType::mana;
    Status status=Status::normal;
    Type type=Type::no_type;
    PlayerClass playerClass=PlayerClass::neutral;
    Place place=Place::deck;
    int cost=0;
    QString name="";
    QString id="";
    std::vector<std::unique_ptr<IEffect>> effects;
};

#endif // CARD_H
