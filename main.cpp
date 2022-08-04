#include "SecurityApp.h"
#include "LoginApp.h"
#include "DirectorApp.h"
#include "SysAdminApp.h"


int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Russian");
    journal_init();
    int type_user;
    login_window(argc,argv,type_user);
    switch (type_user) {
        case CHECKPOINT:
            checkpoint_unit(argc,argv);
            break;
        case DIRECTOR:
            director_window(argc,argv,false);
            break;
        case MOST_DIRECTOR:
            director_window(argc,argv,true);
            break;
        case SYS_ADMIN:
            sysadmin_window(argc,argv);
            break;
        case CLOSE_LOGIN_APP:
            exit(0);
            break;
        default:
            journal << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                    << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60)) <<
                    " development error: main.cpp:24" << "\n";
    }
    return 0;
}