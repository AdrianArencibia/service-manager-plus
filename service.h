#ifndef SERVICE_H
#define SERVICE_H
#include <QString>


#define SERVICE_EXE "/usr/sbin/service "
class Service
{
 QString serviceName;


public:
    static const char* OPTION_INFO;
    static const char* OPTION_START;
    static const char* OPTION_START1;
    static const char* OPTION_STOP;
    static const char* OPTION_STOP1;
    static const char* OPTION_RESTART;
    static const char* OPTION_RESTART1;

    Service();
    //Acciones
    QString start();
    QString stop();
    QString restart();
    QString info();

    //set y get
    void setServiceName(QString serviceName);
    QString getServiceName();

};

#endif // SERVICE_H
