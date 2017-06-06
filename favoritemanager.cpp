#include "favoritemanager.h"
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDir>
#include "command.h"


#define FAVORITE_FILE "/favorites.json"
#define APP_FOLDER "/.service_manager_aah"

const char* FavoriteManager::OPTION_FAVORITE = "f";
const char* FavoriteManager::OPTION_FAVORITE_ADD = "fa";
const char* FavoriteManager::OPTION_FAVORITE_DEL = "fd";
const char* FavoriteManager::OPTION_FAVORITE_EDIT = "fr";

FavoriteManager::FavoriteManager()
{

}

bool FavoriteManager::loadFavorite(){
    QDir d;

    if( !QDir(d.homePath()+APP_FOLDER).exists() && !d.mkdir(d.homePath()+APP_FOLDER)){
        qWarning("Couldn't create folder.");
        return false;
    }

    QFile loadFile(d.homePath()+APP_FOLDER+FAVORITE_FILE);
    if(!loadFile.exists()){
        loadFile.open(QIODevice::ReadWrite | QIODevice::Text);
        loadFile.close();
    }

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc( QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool FavoriteManager::saveFavorite() const{
    QDir d;

    if( !QDir(d.homePath()+APP_FOLDER).exists() && !d.mkdir(d.homePath()+APP_FOLDER)){
        qWarning("Couldn't create folder.");
        return false;
    }

    QFile saveFile(d.homePath()+APP_FOLDER+FAVORITE_FILE);
    if(!saveFile.exists()){
        saveFile.open(QIODevice::ReadWrite | QIODevice::Text);
        saveFile.close();
    }

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject favManager;
    this->write(favManager);
    QJsonDocument saveDoc(favManager);
    saveFile.write( saveDoc.toJson());

    return true;
}

void FavoriteManager::read(const QJsonObject &json){
    this->mFavorites.clear();
    QJsonArray favoriteArray = json["favorites"].toArray();
    for (int favoriteIndex = 0; favoriteIndex < favoriteArray.size(); ++favoriteIndex) {
        QJsonObject favoriteObject = favoriteArray[favoriteIndex].toObject();
        Favorite fav;
        fav.read(favoriteObject);
        this->mFavorites.append(fav);
    }
}
void FavoriteManager::write(QJsonObject &json) const{
    QJsonArray favoriteArray ;
    foreach (const Favorite fav, this->mFavorites) {
        QJsonObject favoriteObject ;
        fav.write(favoriteObject);
        favoriteArray.append(favoriteObject);
    }
    json["favorites"]=favoriteArray;
}

bool FavoriteManager::addFavorite(Favorite fav){

    bool esta=false;
    foreach (const Favorite favorite, this->mFavorites) {
        if(fav.id==favorite.id){
            esta=true;
            break;
        }
    }
    if(!esta){
        this->mFavorites.append(fav);
    }
    return !esta;
}
bool FavoriteManager::editFavorite(QString id,QString new_id){

    bool esta=false;
    foreach ( Favorite favorite, this->mFavorites) {
        if(id==favorite.id){
            removeFavorite(favorite);
            favorite.id=new_id;
            addFavorite(favorite);
            esta=true;
            break;
        }
    }
    return esta;
}
bool FavoriteManager::removeFavorite(Favorite fav){

    return this->mFavorites.removeOne(fav);
}
bool FavoriteManager::removeFavorite(QString id){
    bool esta=false;
    foreach ( Favorite favorite, this->mFavorites) {
        if(id==favorite.id){
            removeFavorite(favorite);
            esta=true;
            break;
        }
    }
    return esta;
}

Favorite FavoriteManager::getByFavorite(QString id){

    foreach ( Favorite favorite, this->mFavorites) {
        if(id==favorite.id){
            return favorite;
            break;
        }
    }
    return Favorite(NULL,NULL);
}

QString FavoriteManager::pritFavorites(){
    Command c;
   QString output= c.list();
   QStringList list = output.split('\n', QString::SkipEmptyParts);

   QString print="[STATUS] [SERVICE] [ID]\n";

   foreach (const QString &str, list) {
        foreach ( Favorite favorite, this->mFavorites) {
            if(str.indexOf(favorite.serviceName)>=0)
                print+= str+"  "+favorite.id +"\n";

        }
    }
    return print;
}
