#include "ieffect.h"
#include<player.h>
#include<entity.h>
#include<battlefield.h>
#include<QRandomGenerator>

namespace
{
int Random_int()
{
    return QRandomGenerator::global()->bounded(100);
}
}
IEffect::IEffect() {}

void ChangeLifeEffect::Execute(const EffectContext& ctx)
{
        auto targets=resolveTargets(this->_target,ctx.field);
        for (auto target: targets) {
        target->changeLife(this->_amount);
    }
}

void DrawEffect::Execute(const EffectContext& ctx)
{
    if(ctx.player)
    {
        for(int i=0;i<this->_amount;++i)
        {
            ctx.player->drawCard();
        }
    }
}

void ExtraResourceEffect::Execute(const EffectContext& ctx)
{
        auto targets=resolveTargets(this->_target,ctx.field);
        for (auto target: targets) {
        target->changeResource(this->_res,this->_amount);
    }
}

//_target == enemy_single, player, all_enemies, random_enemy, etc.
std::vector<Entity*> IEffect::resolveTargets(QString target,BattleField* field)
{
    std::vector<Entity*> targets;

    if(target=="enemy_single")
    {
        Enemy* now=field->getEnemy(0);

        targets.push_back(now);
    }
    else if(target=="player")
    {
        Player* player=field->getPlayer();

        targets.push_back(player);
    }
    else if(target=="all_enemies")
    {
        auto now=field->getEnemies();

        for(auto v : std::as_const(now))
        {
            targets.push_back(v);
        };
    }
    else if(target=="random_enemy")
    {
        auto _size=field->getEnemies().size();

        auto i= Random_int()%_size;

        auto now=field->getEnemy(i);

        targets.push_back(now);
    }
    return targets;
}
