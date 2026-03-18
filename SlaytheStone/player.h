#ifndef PLAYER_H
#define PLAYER_H
#include<vannishyard.h>
#include <card.h>
#include <entity.h>
#include<hand.h>
#include<deck.h>
#include<graveyard.h>

class BattleField;

class Player : public Entity
{
public:
    Player() :_mana(0) {};

    void drawCard()
    {
        auto card=m_deck.drawCard();
        if(card)
        {
            m_hand.addCard(std::move(card));
        }
        return;
    }
    void discardCard(int idx)
    {
        auto now = m_hand.discard(idx);
        if(now)
        {
            m_graveyard.addCard(std::move(now));
        }
    }

    void discardCard()
    {
        auto now = m_hand.discard();
        if(now)
        {
            m_graveyard.addCard(std::move(now));
        }
    }

    //discard from hand methods
    //note that when called without parameter, call random discard method

    void discardCardFromDeck(int idx)
    {
        auto now = m_deck.discard(idx);
        if(now)
        {
            m_graveyard.addCard(std::move(now));
        }
    }

    void discardCardFromDeck()
    {
        auto now = m_deck.discard();
        if(now)
        {
            m_graveyard.addCard(std::move(now));
        }
    }

    void discardCardFromTopofDeck()
    {
        auto now = m_deck.discardFromTop();
        if(now)
        {
            m_graveyard.addCard(std::move(now));
        }
    }

    //discard from deck methods
    //note that when called without parameter, call random discard method

    void sendToGraveyard(std::unique_ptr<Card>card)
    {
        if(card)
        {
            m_graveyard.addCard(std::move(card));
        }
    }

    //automatically called when a card is used

    void vanishCard(int idx)
    {
        auto now=m_hand.vannish(idx);
        if(now)
        {
            m_vannishyard.addCard(std::move(now));
        }
    }

    void vanishCard()
    {
        auto now=m_hand.vannish();
        if(now)
        {
            m_vannishyard.addCard(std::move(now));
        }
    }

    void vanishCardFromDeck(int idx)
    {
        auto now=m_deck.vannish(idx);
        if(now)
        {
            m_vannishyard.addCard(std::move(now));
        }
    }

    void vanishCardFromDeck()
    {
        auto now=m_deck.vannish();
        if(now)
        {
            m_vannishyard.addCard(std::move(now));
        }
    }

    void vanishCardFromTopofDeck()
    {
        auto now=m_deck.vannishFromTop();
        if(now)
        {
            m_vannishyard.addCard(std::move(now));
        }
    }

    void sendToVannishyard(std::unique_ptr<Card>card)
    {
        if(card)
        {
            m_vannishyard.addCard(std::move(card));
        }
    }

    void play(int idx);

    int getMana(){return this->_mana;};


private:
    int _mana=0;
    Deck m_deck;
    Hand m_hand;
    Graveyard m_graveyard;
    Vannishyard m_vannishyard;
    BattleField* m_field;
};

#endif // PLAYER_H
