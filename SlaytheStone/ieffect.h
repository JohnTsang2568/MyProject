#ifndef IEFFECT_H
#define IEFFECT_H
#include<vector>
#include<memory>
#include<jsonparser.h>
#include<resource.h>
#include<QString>

class BattleField;
class Entity;
class Player;

struct EffectContext
{
    EffectContext();
    EffectContext(BattleField* fd, Player* p):field(fd),player(p){};
    using Targets = std::vector<Entity*>;
    BattleField* field;
    Player * player;
};



class IEffect
{
public:
    IEffect();
    virtual ~IEffect() = default;
    virtual void Execute(const EffectContext& context)=0;
    using Targets=std::vector<Entity*>;
    Targets resolveTargets(QString target,BattleField* field);
};

class ChangeLifeEffect : public IEffect
{
private:
    int _amount;
    QString _target; //_target == enemy_single, player, all_enemies, random_enemy, etc.
public:
    ChangeLifeEffect(int amount,QString target): _amount(amount),_target(target){};
    void Execute(const EffectContext& ctx) override;
};

class DrawEffect : public IEffect
{
private:
    int _amount;
    QString _target;
public:
    DrawEffect(int amount,QString target): _amount(amount),_target(target){};
    void Execute(const EffectContext& ctx) override;
};

class ExtraResourceEffect : public IEffect
{
private:
    Resource::ExtraResource _res;
    int _amount;
    QString _target;
public:
    ExtraResourceEffect(Resource::ExtraResource type, int amt,QString target):_res(type),_amount(amt),_target(target){};
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
            return std::make_unique<ChangeLifeEffect>(data.amount,data.target);
        }

        else if(data.type=="Draw")
        {
             return std::make_unique<DrawEffect>(data.amount,data.target);
        }

        else if(data.type=="ExtraResource")
        {
            return std::make_unique<ExtraResourceEffect>(Str2Enum(data.resource),data.amount,data.target);
        }
        return nullptr;
    }
};

#endif // IEFFECT_H
