//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_DIRECTORAPP_H
#define INC_345MF_DIRECTORAPP_H

#include <fstream>
#include <string>
#include <unistd.h>
#include <gtk/gtk.h>
#include <vector>
#include "postgres.h"

//Виджеты окна директора
GtkWidget *windowD;

int finish_program_Dapp = 0;

/* создание окна директора*/
static void create_window_director();

int director_window(int argc, char *argv[]);

extern "C" void window_destroy_Dapp(GtkWidget *object);

void window_destroy_Dapp(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_Dapp = 1;
    gtk_main_quit();
}

static void create_window_director()
{
    GtkBuilder *builder;
    GError* error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./AdminApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

    if(!(windowD = GTK_WIDGET(gtk_builder_get_object(builder, "WindowAdminDirector"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

int director_window(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    create_window_director();
    gtk_widget_show(windowD);
    gtk_main ();
    return 0;
}

#endif //INC_345MF_DIRECTORAPP_H
