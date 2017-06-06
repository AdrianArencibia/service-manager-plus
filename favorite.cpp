#include "favorite.h"


Favorite::Favorite(QString id,QString serviceName)
{
    this->id=id;
    this->serviceName=serviceName;
}
Favorite::Favorite()
{

}

void Favorite::read(const QJsonObject &json)
{
    this->serviceName = json["name"].toString();
    this->id = json["id"].toString();

}
void Favorite::write(QJsonObject &json) const
{
    json["name"] = this->serviceName;
    json["id"] = this->id ;

}

bool Favorite::operator ==(const Favorite & r) const
{
return(r.id == this->id && r.serviceName==this->serviceName);
}
