//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_POSTGRES_H
#define INC_345MF_POSTGRES_H

#include <libpq-fe.h>
#include "fstream"

std::ofstream journal("./log.txt",std::ios::app);

void journal_init(){
    if (!journal) {
        journal = std::ofstream("./log.txt");
    }
}

//Основное соединение приложения
PGconn* conn;

#endif //INC_345MF_POSTGRES_H
