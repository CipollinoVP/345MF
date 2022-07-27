//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_SYSADMINAPP_H
#define INC_345MF_SYSADMINAPP_H

#include <fstream>
#include <string>
#include <unistd.h>
#include <gtk/gtk.h>
#include <vector>
#include "postgres.h"

//Виджеты окна администратора
GtkWidget *windowS;

int finish_program_sys = 0;

/* создание окна директора*/
static void create_window_sys();

int sysadmin_window(int argc, char *argv[]);

extern "C" void window_destroy_SAapp(GtkWidget *object);

void window_destroy_SAapp(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_sys = 1;
    gtk_main_quit();
}

static void create_window_sys()
{
    GtkBuilder *builder;
    GError* error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./SysAdminApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

    if(!(windowS = GTK_WIDGET(gtk_builder_get_object(builder, "windowSysAdmin"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

int sysadmin_window(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    create_window_sys();
    gtk_widget_show(windowS);
    gtk_main ();
    return 0;
}

#endif //INC_345MF_SYSADMINAPP_H
