//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_LOGINAPP_H
#define INC_345MF_LOGINAPP_H

#include <fstream>
#include <string>
#include <unistd.h>
#include <gtk/gtk.h>
#include <vector>
#include "postgres.h"

#define ERROR_LOGIN 11

#define CHECKPOINT 1
#define DIRECTOR 2
#define SYS_ADMIN 3
#define MOST_DIRECTOR 4
#define CLOSE_LOGIN_APP 0


//Виджеты окна авторизации
GtkWidget *windowA;
GtkWidget *LoginEntryA;
GtkWidget *PasswordEntryA;
GtkWidget *StatusLoginA;
GtkWidget *LoginButtonA;


int finish_program_lapp = 0;

bool flag = false;

/* создание окна авторизации*/
static void create_window_login();

int login_window(int argc, char *argv[], int& type_user);

G_MODULE_EXPORT void window_destroy_lapp(GtkWidget *object);

G_MODULE_EXPORT void authorizate_button (GtkWidget *object);

std::string name_role;

std::string login;

static void create_window_login()
{
    GtkBuilder *builder;
    GError* error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./LoginApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

    if(!(windowA = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LoginEntryA = GTK_WIDGET(gtk_builder_get_object(builder, "LoginEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PasswordEntryA = GTK_WIDGET(gtk_builder_get_object(builder, "PasswordEntry"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusLoginA = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLogin"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LoginButtonA = GTK_WIDGET(gtk_builder_get_object(builder, "LoginButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

int login_window(int argc, char *argv[], int& type_user){
    gtk_init(&argc, &argv);
    create_window_login();
    g_signal_connect(G_OBJECT(windowA), "destroy", G_CALLBACK(window_destroy_lapp), NULL);
    g_signal_connect(G_OBJECT(windowA), "destroy-event", G_CALLBACK(window_destroy_lapp), NULL);
    g_signal_connect(G_OBJECT(LoginButtonA), "clicked", G_CALLBACK(authorizate_button), NULL);
    gtk_widget_show(windowA);
    gtk_main ();
    if (flag) {
        if ((name_role == "controller_by_walk") || (name_role == "controller_car")) {
            type_user = CHECKPOINT;
        } else if (name_role == "cheif_admin") {
            type_user = DIRECTOR;
        } else if (name_role == "global_admin") {
            type_user = SYS_ADMIN;
        } else if (name_role == "most_cheif_admin") {
            type_user = MOST_DIRECTOR;
        } else {
            journal << (time(nullptr) % (24 * 3600)) / 3600 + 3 << ":"
                    << (time(nullptr) % (3600)) / 60 << ":" << (time(nullptr) % (60))
                    << ":  unknown role" << "\n";
            exit(ERROR_LOGIN);
        }
    } else {
        type_user = CLOSE_LOGIN_APP;
    }
    return 0;
}

void window_destroy_lapp(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_lapp = 1;
    gtk_main_quit();
}

void authorizate_button (GtkWidget *object){
    login = gtk_entry_get_text(GTK_ENTRY(LoginEntryA));
    std::string password = gtk_entry_get_text(GTK_ENTRY(PasswordEntryA));
    conn = PQsetdbLogin("localhost","5432","","",
                        "345MF",login.c_str(),password.c_str());
    if (PQstatus(conn) == CONNECTION_BAD) {
        gtk_label_set_text(GTK_LABEL(StatusLoginA),"Неверный логин или пароль");
    } else {
        std::stringstream query;
        query << "WITH RECURSIVE cte AS (SELECT oid FROM pg_roles WHERE rolname =\'" <<
        login << "\' UNION ALL SELECT m.roleid FROM   cte"
        <<" JOIN   pg_auth_members m ON m.member = cte.oid " <<
        ") SELECT oid, oid::regrole::text AS rolename FROM cte";
        std::string query_s = query.str();
        PGresult *rs_login = PQexec(conn, query_s.c_str());
        char* role_s = PQgetvalue(rs_login,1,1);
        if (role_s == nullptr) {
            journal << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                    << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60))
                    << ":  user isn't member anything role" << "\n";
            exit(ERROR_LOGIN);
        } else
        {
            name_role = std::string(role_s);
            flag = true;
            gtk_window_close(GTK_WINDOW(windowA));
        }
    }
}

#endif //INC_345MF_LOGINAPP_H
