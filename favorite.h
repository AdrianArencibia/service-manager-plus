#ifndef FAVORITE_H
#define FAVORITE_H
#include <QJsonObject>
#include <QString>

class Favorite
{

public:
    QString serviceName;
    QString id;
    Favorite(QString id, QString serviceName);
    Favorite();
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    bool operator ==(const Favorite &r) const;
};

#endif // FAVORITE_H
