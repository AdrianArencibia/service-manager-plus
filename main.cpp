#include <QCoreApplication>
#include <QDebug>
#include "service.h"
#include "command.h"
#include "iostream"
#include <string.h>
#include "favorite.h"
#include "favoritemanager.h"
#include <unistd.h>

#define ERR_OPTION "\033[1;41m*\033[0m Unrecognized option: "
#define MSG_OPTION_FAVORITE_ADD_OK " Added successfully. "
#define MSG_OPTION_FAVORITE_ADD_ERR " Key for favorite already exists. "

#define MSG_OPTION_FAVORITE_EDIT_OK " Edited successfully. "
#define MSG_OPTION_FAVORITE_EDIT_ERR " Key for favorite not exists. "

#define MSG_OPTION_FAVORITE_DEL_OK " Deleted successfully. "
#define MSG_OPTION_FAVORITE_DEL_ERR " Key for favorite not exists. "


#define HELP \
    "\nService Manager Plus"\
    "\nUSAGE: sm OPTION ARG"\
    "\nOPTION: "\
    "\n     For list (not need ARG): "\
    "\n         l: show all services."\
    "\n         lr: show all running services."\
    "\n         lr: show all stoped services."\
    "\n     For actions: ARG can be the services names or key from Favorites."\
    "\n         [1|s]: to start services(ARG)."\
    "\n         [0|st]: to stop services(ARG)."\
    "\n         [-1|r]: to restart services(ARG)."\
    "\n         i: to get information about services(ARG)."\
    "\n     For favorites:"\
    "\n         f: to list the favorite services."\
    "\n         fa: add service to favorites. ARG [name key]"\
    "\n             Example: fa cntlm c "\
    "\n         fr: modify key of a service in favorites. ARG [key newkey]"\
    "\n             Example: fr c cnt"\
    "\n         fd: delete service from favorites. ARG [key]"\
    "\n             Example: fd cnt"\
    "\n"\

/**
 * @brief main
 * @param argc
 * @param argv
 *
 */



/**
 * @brief processOption
 * @param service
 * @param cmd
 * Process option cmd for service.
 */
void processOption(char* services,char* cmd);

/**
 * @brief processSimpleCommand
 * @param cmd
 * Process simple command
 */
void processSimpleCommand(char* cmd);


/**
 * @brief showHelp
 * @param cmd
 * Show help and error about cmd
 */
void showHelp(QString cmd);

void showMSG(QString msg,bool state);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    if(argc>=3){
        if( strcmp(argv[1], FavoriteManager::OPTION_FAVORITE_ADD)==0 && argc==4){
            FavoriteManager fm;
            fm.loadFavorite();
            bool r= fm.addFavorite(Favorite(argv[3],argv[2]));
            fm.saveFavorite();

            showMSG(QString(argv[3]) +" -> "+ QString(argv[2])+(r?MSG_OPTION_FAVORITE_ADD_OK:MSG_OPTION_FAVORITE_ADD_ERR),r);
            return 0;
        }
        if( strcmp(argv[1], FavoriteManager::OPTION_FAVORITE_EDIT)==0 && argc==4){
            FavoriteManager fm;
            fm.loadFavorite();
            bool r=fm.editFavorite(argv[2], argv[3]);
            fm.saveFavorite();

            showMSG(QString(argv[3]) +" -> "+ QString(argv[2])+(r?MSG_OPTION_FAVORITE_EDIT_OK:MSG_OPTION_FAVORITE_EDIT_ERR),r);
            return 0;
        }

        for (int i = 2; i < argc; ++i) {
            processOption(argv[i],argv[1]);
        }
        return 0;
    }
    else if(argc==2){
        processSimpleCommand(argv[1]);
        return 0;
    }


    showHelp("-h");

    return 0;

}

void processOption(char* service,char* cmd){
    Service s;
    QString servName(service);
    FavoriteManager fm;
    fm.loadFavorite();
    Favorite fav= fm.getByFavorite(service);
    if( fav.id!=NULL){
        s.setServiceName(fav.serviceName);
    }
    else{
        s.setServiceName(servName);
    }

    if( strcmp(cmd, Service::OPTION_INFO)==0){
        std::cout << s.info().toStdString();
        return;
    }
    if( strcmp(cmd, Service::OPTION_START)==0 || strcmp(cmd, Service::OPTION_START1)==0){
        std::cout << s.start().toStdString();
        return;
    }
    if( strcmp(cmd, Service::OPTION_STOP)==0 || strcmp(cmd, Service::OPTION_STOP1)==0){
        std::cout << s.stop().toStdString();
        return;
    }
    if( strcmp(cmd, Service::OPTION_RESTART)==0 || strcmp(cmd, Service::OPTION_RESTART1)==0){
        std::cout << s.restart().toStdString();
        return;
    }

    if( strcmp(cmd, FavoriteManager::OPTION_FAVORITE_DEL)==0 ){
        bool r= fm.removeFavorite(service);
        fm.saveFavorite();
        showMSG(QString(cmd) +" -> "+ QString(service)+(r?MSG_OPTION_FAVORITE_DEL_OK:MSG_OPTION_FAVORITE_DEL_ERR),r);
        return ;
    }
    showHelp(QString(cmd));
}

void processSimpleCommand(char* cmd){

    Command c;
    if( strcmp(cmd, Command::CMD_LIST)==0 ){

        std::cout << c.list().toStdString();
        return ;
    }
    if( strcmp(cmd, Command::CMD_LIST_RUNNING)==0 ){
        std::cout << c.listRunning().toStdString();
        return ;
    }
    if( strcmp(cmd, Command::CMD_LIST_STOPED)==0 ){
        std::cout << c.listStoped().toStdString();
        return ;
    }
    if( strcmp(cmd, FavoriteManager::OPTION_FAVORITE)==0 ){
        FavoriteManager fm;
        fm.loadFavorite();
        QString r= fm.pritFavorites();
        std::cout << r.toStdString();
        return ;
    }
    showHelp(QString(cmd));

}

void showHelp(QString cmd){
    //Opción no reconocida

    if(cmd!="-h"&& cmd!="-help")
    std::cout << ERR_OPTION << cmd.toStdString() ;

    //Mostrar la Ayuda
    std::cout << HELP ;

}

void showMSG(QString msg, bool state){

    std::string color="";
    state?color="\033[1;42m● \033[0m":color="\033[1;41m● \033[0m";

    std::cout <<color << msg.toStdString();

}



