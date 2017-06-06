#ifndef COMMAND_H
#define COMMAND_H
#include <QString>

class Command
{


public:
    static const char* CMD_LIST;
    static const char* CMD_LIST_RUNNING;
    static const char* CMD_LIST_STOPED;
    static const char* CMD_RENAME;
    static const QString HEAD_TABLE;
    Command();
    QString list();
    QString listClean();
    QString listRunning();
    QString listStoped();
    QString rename(QString service,QString name);
};

#endif // COMMAND_H
