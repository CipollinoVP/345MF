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
GtkWidget *EnterAllSearchD;
GtkWidget *SurnameSearchD;
GtkWidget *NameSearchD;
GtkWidget *FathernameSearchD;
GtkWidget *PostSearchD;
GtkWidget *DivisionSearchD;
GtkWidget *ViewWorkersD;
GtkWidget *SurnameLabelD;
GtkWidget *NameLabelD;
GtkWidget *FathernameLabelD;
GtkWidget *PostLabelD;
GtkWidget *DivisionLabelD;
GtkWidget *CodeLabelD;
GtkWidget *TimeWorkOfficialD;
GtkWidget *TimeOutOfficialD;
GtkWidget *DaySkipNoOfficialD;
GtkWidget *FinishWorkD;
GtkWidget *TimeWorkOutD;
GtkWidget *TimeOutPersonalD;
GtkWidget *DaySkipOfficialD;
GtkWidget *SeansesViewD;
GtkWidget *StartWorkD;


int finish_program_Dapp = 0;

static void create_window_director();

int director_window(int argc, char *argv[]);

extern "C" void window_destroy_Dapp(GtkWidget *object);

extern "C" void Press_SearchButton(GtkWidget *object);

extern "C" void Press_GetReportButton(GtkWidget *object);

extern "C" void Press_official_memo_button(GtkWidget *object);

extern "C" void Press_Correct_button(GtkWidget *object);

extern "C" void Press_GetPass(GtkWidget *object);

extern "C" void Press_SinglePassButton(GtkWidget *object);

extern "C" void Press_EnterBigOut(GtkWidget *object);

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
    if(!(EnterAllSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "EnterAllSearch"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SurnameSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameSearch"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "NameSearch"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PostSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "PostSearch"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DivisionSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "DivisionSearch"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SurnameLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "NameLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FathernameLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PostLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "PostLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DivisionLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "DivisionLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CodeLabelD = GTK_WIDGET(gtk_builder_get_object(builder, "CodeLabel"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StartWorkD = GTK_WIDGET(gtk_builder_get_object(builder, "StartWork"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TimeWorkOfficialD = GTK_WIDGET(gtk_builder_get_object(builder, "TimeWorkOfficial"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TimeOutOfficialD = GTK_WIDGET(gtk_builder_get_object(builder, "TimeOutOfficial"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DaySkipNoOfficialD = GTK_WIDGET(gtk_builder_get_object(builder, "DaySkipNoOfficial"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FinishWorkD = GTK_WIDGET(gtk_builder_get_object(builder, "FinishWork"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TimeWorkOutD = GTK_WIDGET(gtk_builder_get_object(builder, "TimeWorkOut"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(TimeOutPersonalD = GTK_WIDGET(gtk_builder_get_object(builder, "TimeOutPersonal"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DaySkipOfficialD = GTK_WIDGET(gtk_builder_get_object(builder, "DaySkipOfficial"))))
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

void Press_SearchButton(GtkWidget *object){

};

void Press_GetReportButton(GtkWidget *object){

};

void Press_official_memo_button(GtkWidget *object){

};

void Press_Correct_button(GtkWidget *object){

};

void Press_GetPass(GtkWidget *object){

};

void Press_SinglePassButton(GtkWidget *object){

};

void Press_EnterBigOut(GtkWidget *object){

};

#endif //INC_345MF_DIRECTORAPP_H
