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

extern "C" void out_info_worker(GtkWidget *object);

struct worker_info{
    int id = 0;
    std::string surname;
    std::string name;
    std::string fathername;
    std::string post;
    std::string division;
};

std::vector<worker_info> list_w;

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
    if(!(FathernameSearchD = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameSearch"))))
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
    if(!(ViewWorkersD = GTK_WIDGET(gtk_builder_get_object(builder, "ViewWorkers"))))
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
    GtkTreeModel *list = gtk_tree_view_get_model(GTK_TREE_VIEW(ViewWorkersD));
    gtk_list_store_clear(GTK_LIST_STORE(list));
    std::string AllS(gtk_entry_get_text(GTK_ENTRY(EnterAllSearchD)));
    std::string SurnameS(gtk_entry_get_text(GTK_ENTRY(SurnameSearchD)));
    std::string NameS(gtk_entry_get_text(GTK_ENTRY(NameSearchD)));
    std::string FathernameS(gtk_entry_get_text(GTK_ENTRY(FathernameSearchD)));
    std::string PostS(gtk_entry_get_text(GTK_ENTRY(PostSearchD)));
    std::string DivisionS(gtk_entry_get_text(GTK_ENTRY(DivisionSearchD)));
    std::stringstream query;
    if (!AllS.empty()) {
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM workers,divisions"
        <<" WHERE ((division = divisions.id) AND ((surname LIKE '" << AllS <<
              "%') OR (name LIKE '" << AllS << "%') OR (fathername LIKE '" <<
              AllS << "%') OR (post LIKE '" << AllS << "%') OR (divisions_name LIKE '" <<
              AllS << "%')));";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,1));
            worker.surname = std::string(PQgetvalue(rs_q,i,2));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter iter;
            gtk_list_store_append(GTK_LIST_STORE(list),&iter);
            gtk_list_store_set(GTK_LIST_STORE(list),&iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
    if (!SurnameS.empty()) {
        query << "SELECT id,name,surname,fathername,post,division FROM workers WHERE (surname LIKE '" << SurnameS <<
              "%' );";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,1));
            worker.surname = std::string(PQgetvalue(rs_q,i,2));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter *iter;
            gtk_list_store_append(GTK_LIST_STORE(list),iter);
            gtk_list_store_set(GTK_LIST_STORE(list),iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
    if (!NameS.empty()) {
        query << "SELECT id,name,surname,fathername,post,division FROM workers WHERE (name LIKE '" << NameS <<
              "%' );";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,1));
            worker.surname = std::string(PQgetvalue(rs_q,i,2));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter *iter;
            gtk_list_store_append(GTK_LIST_STORE(list),iter);
            gtk_list_store_set(GTK_LIST_STORE(list),iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
    if (!FathernameS.empty()) {
        query << "SELECT id,name,surname,fathername,post,division FROM workers WHERE (fathername LIKE '"
        << FathernameS << "%' );";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,1));
            worker.surname = std::string(PQgetvalue(rs_q,i,2));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter *iter;
            gtk_list_store_append(GTK_LIST_STORE(list),iter);
            gtk_list_store_set(GTK_LIST_STORE(list),iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
    if (!PostS.empty()) {
        query << "SELECT id,name,surname,fathername,post,division FROM workers WHERE (post LIKE '" << PostS <<
              "%' );";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,1));
            worker.surname = std::string(PQgetvalue(rs_q,i,2));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter *iter;
            gtk_list_store_append(GTK_LIST_STORE(list),iter);
            gtk_list_store_set(GTK_LIST_STORE(list),iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
    if (!DivisionS.empty()) {
        query << "SELECT id,name,surname,fathername,post,division FROM workers WHERE (division LIKE '" << DivisionS <<
              "%' );";
        std::string query_s = query.str();
        PGresult *rs_q = PQexec(conn,query_s.c_str());
        int n = PQntuples(rs_q);
        list_w = std::vector<worker_info>(0);
        for (int i = 0; i < n; ++i) {
            worker_info worker;
            worker.id = std::stoi(std::string(PQgetvalue(rs_q,i,0)));
            worker.name = std::string(PQgetvalue(rs_q,i,2));
            worker.surname = std::string(PQgetvalue(rs_q,i,1));
            worker.fathername = std::string(PQgetvalue(rs_q,i,3));
            worker.post = std::string(PQgetvalue(rs_q,i,4));
            worker.division = std::string(PQgetvalue(rs_q,i,5));
            GtkTreeIter *iter;
            gtk_list_store_append(GTK_LIST_STORE(list),iter);
            gtk_list_store_set(GTK_LIST_STORE(list),iter,0,worker.id,1,worker.surname.c_str(),
                               2,worker.name.c_str(), 3,worker.fathername.c_str(),
                               4, worker.post.c_str(),5, worker.division.c_str());
            list_w.push_back(worker);
        }
        return;
    };
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

void out_info_worker(GtkWidget *object){
   GtkTreeIter iter;
   GtkTreePath *path;
   GtkTreeViewColumn *column;
   gtk_tree_view_get_cursor(GTK_TREE_VIEW(ViewWorkersD),&path,&column);
   gtk_tree_model_get_iter(gtk_tree_view_get_model(GTK_TREE_VIEW(ViewWorkersD)),&iter,path);
   int a =  *(int*) iter.user_data;
   std::cout << a << std::endl;
}

#endif //INC_345MF_DIRECTORAPP_H
