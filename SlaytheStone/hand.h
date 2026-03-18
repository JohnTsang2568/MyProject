#ifndef HAND_H
#define HAND_H
#include<vector>
#include<memory>
#include<card.h>
#include<QRandomGenerator>

class Hand
{
public:
    Hand();
    void addCard(std::unique_ptr<Card>card)
    {
        m_card.push_back(std::move(card));
    }

    std::unique_ptr<Card> discard(int idx)
    {
        if(m_card.empty())return nullptr;
        auto card= std::move(m_card.at(idx));
        m_card.erase(m_card.begin()+idx);
        return card;
    }


    //index-based discard method,discard card(s)

    std::unique_ptr<Card> discard()
    {
        if(m_card.empty())return nullptr;
        int ranIdx= QRandomGenerator::global()->bounded(m_card.size());
        auto card=std::move(m_card.at(ranIdx));
        m_card.erase(m_card.begin()+ranIdx);
        return card;
    }

    //discard random card

    std::unique_ptr<Card> vannish(int idx)
    {
        if(m_card.empty())return nullptr;
        auto card= std::move(m_card.at(idx));
        m_card.erase(m_card.begin()+idx);
        return card;
    }

    std::unique_ptr<Card> vannish()
    {
        if(m_card.empty())return nullptr;
        int ranIdx= QRandomGenerator::global()->bounded(m_card.size());
        auto card=std::move(m_card.at(ranIdx));
        m_card.erase(m_card.begin()+ranIdx);
        return card;
    } //vannish random card

    //return unique_ptr<Card> so that you do not need to get the discarded card mannually

    const Card* getCard(int idx)
    {
        if(idx<0||idx>size())
        {
            return nullptr;
        }
        return m_card.at(idx).get();
    }

    int size() const
    {
    return static_cast<int>(m_card.size());
    }

    bool empty() const
    {
        return m_card.empty();
    }

private:
    std::vector<std::unique_ptr<Card>> m_card;
};

#endif // HAND_H
