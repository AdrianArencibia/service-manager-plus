#include "service.h"

#include <QProcess>
#include <QDebug>


const char* Service::OPTION_INFO = "i";
const char* Service::OPTION_START = "s";
const char* Service::OPTION_START1 = "1";
const char* Service::OPTION_STOP = "st";
const char* Service::OPTION_STOP1 = "0";
const char* Service::OPTION_RESTART = "r";
const char* Service::OPTION_RESTART1 = "-1";

Service::Service(){


}


QString Service::start(){

    QString output=this->info();
    if(output.indexOf("active (running)")>0){
        return "\033[1;42m● "+this->getServiceName()+" is active (running)\033[0m\n";
    }

    QProcess pingProcess;
    pingProcess.execute(SERVICE_EXE+this->getServiceName()+" start");
    output=this->info();

    if(output.indexOf("active (running)")>0){
         return "\033[1;42m● "+this->getServiceName()+" is active (running)\033[0m\n";

    }
    return "\033[1;41m● "+this->getServiceName()+" is inactive (dead)\033[0m\n";


}

QString Service::info(){
    QProcess pingProcess;
    pingProcess.start(SERVICE_EXE+this->getServiceName()+" status");
    pingProcess.waitForFinished();
    QString output(pingProcess.readAllStandardOutput());
    //Pintar de verde si esta activo el servicio o de rojo si no lo esta
    if(output.indexOf("active (running)")>0){
        output.replace("active (running)","\033[1;42m active (running) \033[0m");
        output.replace("●","\033[1;32m●\033[0m");
    }
    else{
        output.replace("inactive (dead)","\033[1;41m inactive (dead) \033[0m");
        output.replace("●","\033[1;31m●\033[0m");
    }
    return output;
}

QString Service::stop(){
    QString output=this->info();
    if(output.indexOf("active (running)")<0){
         return "\033[1;41m● "+this->getServiceName()+" is inactive (dead)\033[0m\n";
    }

    QProcess pingProcess;
    pingProcess.execute(SERVICE_EXE+this->getServiceName()+" stop");
    output=this->info();

    if(output.indexOf("active (running)")>0){
         return "\033[1;42m● "+this->getServiceName()+" is active (running)\033[0m\n";

    }
    return "\033[1;41m● "+this->getServiceName()+" is inactive (dead)\033[0m\n";
}
QString Service::restart(){

    QProcess pingProcess;
    pingProcess.execute(SERVICE_EXE+this->getServiceName()+" restart");

    return "\033[1;43m● "+this->getServiceName()+"  is restarting \033[0m\n";
}

void Service::setServiceName(QString serviceName){
    this->serviceName=serviceName;
}

QString Service::getServiceName(){
    return this->serviceName;
}
