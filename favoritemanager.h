#ifndef FAVORITEMANAGER_H
#define FAVORITEMANAGER_H
#include <QJsonObject>
#include <QString>
#include <QList>
#include "favorite.h"

class FavoriteManager
{

public:
    static const char* OPTION_FAVORITE;
    static const char* OPTION_FAVORITE_ADD;
    static const char* OPTION_FAVORITE_DEL;
    static const char* OPTION_FAVORITE_EDIT;
    FavoriteManager();
    bool loadFavorite();
    bool saveFavorite() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    bool addFavorite(Favorite fav);
    bool removeFavorite(Favorite fav);
    bool removeFavorite(QString id);
    bool editFavorite(QString id,QString new_id);
    QString pritFavorites();
    Favorite getByFavorite(QString id);

private:
    QList<Favorite> mFavorites;
};

#endif // FAVORITEMANAGER_H
