#include "ieffect.h"
#include<player.h>
#include<entity.h>
#include<battlefield.h>

IEffect::IEffect() {}

void ChangeLifeEffect::Execute(const EffectContext& ctx)
{
        for (auto target: ctx.targets) {
        target->changeLife(this->_amount);
    }
}

void DrawEffect::Execute(const EffectContext& ctx)
{
        for (auto target: ctx.targets) {
        if(auto player = dynamic_cast<Player*>(target))
        player->drawCard(this->_amount);
    }
}

void ExtraResourceEffect::Execute(const EffectContext& ctx)
{
        for (auto target: ctx.targets) {
        target->changeResource(this->_res,this->_amount);
    }
}
