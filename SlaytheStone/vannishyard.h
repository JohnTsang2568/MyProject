#ifndef VANNISHYARD_H
#define VANNISHYARD_H
#include<vector>
#include<card.h>
#include<QRandomGenerator>
#include<memory>

class Vannishyard
{
public:
    Vannishyard();
    using cards= std::vector<std::unique_ptr<Card>>;
    void addCard(std::unique_ptr<Card> card)
    {
        m_card.push_back(std::move(card));
    }

    std::unique_ptr<Card> removeCard()
    {
        if(m_card.empty())return nullptr;
        auto card=std::move(m_card.back());
        m_card.pop_back();
        return card;
    }
    //return removed card

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

#endif // VANNISHYARD_H
