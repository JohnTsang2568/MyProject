#include "mainwindow.h"
#include<jsonparser.h>
#include<ieffect.h>
#include<card.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QList<CardData> cardsData = JsonParser::parseCardsFromJson(":/cards.json");

    EffectFactory factory;

    QList<Card*> cards;
    for (const auto& cardData : std::as_const(cardsData)) {
        cards.append(new Card(cardData, factory));
    }


    return a.exec();
}
