#ifndef IEFFECT_H
#define IEFFECT_H
#include<vector>
#include<memory>
#include<jsonparser.h>
#include<resource.h>

class BattleField;
class Entity;
class Player;

struct EffectContext
{
    EffectContext();
    using Targets = std::vector<Entity*>;
    Player* player;
    Targets targets;
    BattleField* field;
};



class IEffect
{
public:
    IEffect();
    virtual ~IEffect() = default;
    virtual void Execute(const EffectContext& context)=0;
};

class ChangeLifeEffect : public IEffect
{
private:
    int _amount;
public:
    ChangeLifeEffect(int amount): _amount(amount){};
    void Execute(const EffectContext& ctx) override;
};

class DrawEffect : public IEffect
{
private:
    int _amount;
public:
    DrawEffect(int amount): _amount(amount){};
    void Execute(const EffectContext& ctx) override;
};

class ExtraResourceEffect : public IEffect
{
private:
    Resource::ExtraResource _res;
    int _amount;
public:
    ExtraResourceEffect(Resource::ExtraResource type, int amt):_res(type),_amount(amt){};
    void Execute(const EffectContext& ctx) override;
};



class EffectFactory
{
public:
    Resource::ExtraResource Str2Enum(QString t) const
    {
        if(t=="block")return Resource::ExtraResource::block;
        if(t=="soul")return Resource::ExtraResource::soul;
        return Resource::ExtraResource::block;
    }

    std::unique_ptr<IEffect> MakeCard (const EffectData& data) const
    {
        if(data.type=="Change_life")
        {
            return std::make_unique<ChangeLifeEffect>(data.amount);
        }

        else if(data.type=="Draw")
        {
             return std::make_unique<DrawEffect>(data.amount);
        }

        else if(data.type=="ExtraResource")
        {
            return std::make_unique<ExtraResourceEffect>(Str2Enum(data.resource),data.amount);
        }
        return nullptr;
    }
};

#endif // IEFFECT_H
