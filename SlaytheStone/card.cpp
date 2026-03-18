#include "card.h"
#include <ieffect.h>
#include <battlefield.h>
#include<player.h>
#include<memory>

Card::Card() {}


void Card::play(BattleField * field) {
    EffectContext ctx(field,field->getPlayer());

    for(const auto & v: effects)
    {
        v->Execute(ctx);
    }

}
