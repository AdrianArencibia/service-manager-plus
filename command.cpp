#include "command.h"
#include <QString>
#include <QProcess>
#include <QDebug>
#include <QStringList>
#include "service.h"

const char* Command::CMD_LIST = "l";
const char* Command::CMD_LIST_RUNNING = "lr";
const char* Command::CMD_LIST_STOPED = "ls";
const char* Command::CMD_RENAME = "r";
const QString Command::HEAD_TABLE = "[ ID ] [ STATUS ] [ NAME ]\n";


Command::Command()
{

}

QString Command::list(){
    QProcess pingProcess;
    pingProcess.start(SERVICE_EXE" --status-all");
    pingProcess.waitForFinished();
    QString output(pingProcess.readAllStandardOutput());
    output.replace("[ + ]","\033[1;42m[ + ]\033[0m");
    output.replace("[ - ]","\033[1;41m[ - ]\033[0m");



    return output;

}
QString Command::listClean(){
    QProcess pingProcess;
    pingProcess.start(SERVICE_EXE" --status-all");
    pingProcess.waitForFinished();
    QString output(pingProcess.readAllStandardOutput());
    output.replace("[ + ]","");
    output.replace("[ - ]","");
    output.replace(" ","");
    return output;

}
QString Command::listRunning(){
    QString output= this->list();
    QStringList list = output.split('\n', QString::SkipEmptyParts);
    QString result=this->HEAD_TABLE;
    foreach (const QString &str, list) {
        if (str.contains("[ + ]"))
            result += str+"\n";
    }

    return result;
}
QString Command::listStoped(){
    QString output= this->list();
    QStringList list = output.split('\n', QString::SkipEmptyParts);
    QString result=this->HEAD_TABLE;
    foreach (const QString &str, list) {
        if (str.contains("[ - ]"))
            result += str+"\n";
    }

    return result;
}
QString Command::rename(QString service,QString name){
    return "";
}



