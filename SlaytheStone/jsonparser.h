#ifndef JSONPARSER_H
#define JSONPARSER_H
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonParseError>
#include<QFile>
#include<QJsonObject>
#include<QDebug>

struct EffectData
{
    QString type;
    QString target;
    QString resource;
    int amount;
};

struct CardData
{
    QString id;
    QString name;
    int cost;
    QList<EffectData> effects;
};

class JsonParser
{
public:
    JsonParser();
    static QList<CardData> parseCardsFromJson(const QString& filePath) {
        QList<CardData> cards;

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            qWarning() << "Cannot open file:" << file.errorString();
            return cards;
        }

        //open Json File
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (!doc.isArray()) {
            qWarning() << "JSON root is not an array";
            return cards;
        }

        QJsonArray cardArray = doc.array();
        for (const QJsonValue& cardVal : std::as_const(cardArray)) {
            QJsonObject cardObj = cardVal.toObject();

            CardData card;
            card.id = cardObj["id"].toString();
            card.name = cardObj["name"].toString();
            card.cost = cardObj["cost"].toInt();


            QJsonArray effectArray = cardObj["effects"].toArray();
            for (const QJsonValue& effectVal : std::as_const(effectArray)) {
                QJsonObject effectObj = effectVal.toObject();

                EffectData effect;
                effect.type = effectObj["type"].toString();
                effect.amount = effectObj["amount"].toInt();
                effect.target = effectObj["target"].toString();

                if (effectObj.contains("resource"))
                    effect.resource = effectObj["resource"].toString();

                card.effects.append(effect);
            }

            cards.append(card);
        }

        return cards;
    }
};

#endif // JSONPARSER_H
