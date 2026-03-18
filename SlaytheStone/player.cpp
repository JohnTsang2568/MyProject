#include "player.h"
#include <battlefield.h>
#include <card.h>


void Player::play(int idx)
{
    auto card=this->m_hand.discard(idx);
    if(!card)return;

    card->play(this->m_field);
    this->discardCard(idx);
}
