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

#define ERROR_SORT 12

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
GtkWidget *SearchButtonD;
GtkWidget *GetReportButtonD;
GtkWidget *official_memo_buttonD;
GtkWidget *CorrectButtonD;
GtkWidget *GetPassD;
GtkWidget *SinglePassButtonD;
GtkWidget *EscapeButtonD;
GtkWidget *EnterBigOutD;
GObject *NumColumnD;

int status_sort_workers = -1;

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

extern "C" void Sort_workers(GtkWidget *object);

struct worker_info{
    int id = 0;
    std::string surname;
    std::string name;
    std::string fathername;
    std::string post;
    std::string division;
};

struct auth{
    int id = 0;
    std::string date;
    std::string time;
    bool status1{false};
    std::string status2;
};

struct session{
    int id = 0;
    std::string date1;
    std::string time1;
    std::string date2;
    std::string time2;
    std::string status1;
    std::string status2;
};

std::vector<worker_info> list_w;

std::vector<session> list_sessions;

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
    if(!(SearchButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "SearchButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(GetReportButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "GetReportButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(official_memo_buttonD = GTK_WIDGET(gtk_builder_get_object(builder, "official_memo_button"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CorrectButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "CorrectButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(GetPassD = GTK_WIDGET(gtk_builder_get_object(builder, "GetPass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SinglePassButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EscapeButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "EscapeButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EnterBigOutD = GTK_WIDGET(gtk_builder_get_object(builder, "EnterBigOut"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StartWorkD = GTK_WIDGET(gtk_builder_get_object(builder, "StartWork"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NumColumnD = G_OBJECT(gtk_builder_get_object(builder, "NColumn"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

int director_window(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    create_window_director();
    g_signal_connect(G_OBJECT(windowD), "destroy", G_CALLBACK(window_destroy_Dapp), NULL);
    g_signal_connect(G_OBJECT(windowD), "destroy-event", G_CALLBACK(window_destroy_Dapp), NULL);
    g_signal_connect(G_OBJECT(SearchButtonD), "clicked", G_CALLBACK(Press_SearchButton), NULL);
    g_signal_connect(G_OBJECT(GetPassD), "clicked", G_CALLBACK(Press_GetPass), NULL);
    g_signal_connect(G_OBJECT(official_memo_buttonD), "clicked", G_CALLBACK(Press_official_memo_button), NULL);
    g_signal_connect(G_OBJECT(GetReportButtonD), "clicked", G_CALLBACK(Press_GetReportButton), NULL);
    g_signal_connect(G_OBJECT(CorrectButtonD), "clicked", G_CALLBACK(Press_Correct_button), NULL);
    g_signal_connect(G_OBJECT(SinglePassButtonD), "clicked", G_CALLBACK(Press_SinglePassButton), NULL);
    g_signal_connect(G_OBJECT(EscapeButtonD), "clicked", G_CALLBACK(window_destroy_Dapp), NULL);
    g_signal_connect(G_OBJECT(EnterBigOutD), "clicked", G_CALLBACK(Press_EnterBigOut), NULL);
    g_signal_connect(G_OBJECT(ViewWorkersD), "cursor-changed", G_CALLBACK(out_info_worker), NULL);
    g_signal_connect(G_OBJECT(NumColumnD), "clicked", G_CALLBACK(Sort_workers), NULL);
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
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(ViewWorkersD),&path,&col);
    int* a = gtk_tree_path_get_indices(path);
    if (a == nullptr) {
        return;
    }
    std::stringstream query;
    std::stringstream  query_1;
    query << "SELECT authorizate.id,time_enter,date_enter,status_enter,status_memo FROM " <<
    "workers,authorizate WHERE ((idworker = workers.id) AND (workers.id ="<< list_w[*a].id <<"));";
    query_1 << "SELECT depature,arrival FROM workers WHERE id = " << list_w[*a].id << ";" ;
    PGresult *rs_b = PQexec(conn,query_1.str().c_str());
    PGresult *rs_a = PQexec(conn,query.str().c_str());
    int n = PQntuples(rs_a);
    gtk_label_set_text(GTK_LABEL(SurnameLabelD),list_w[*a].surname.c_str());
    gtk_label_set_text(GTK_LABEL(NameLabelD),list_w[*a].name.c_str());
    gtk_label_set_text(GTK_LABEL(FathernameLabelD),list_w[*a].fathername.c_str());
    gtk_label_set_text(GTK_LABEL(PostLabelD),list_w[*a].post.c_str());
    gtk_label_set_text(GTK_LABEL(DivisionLabelD),list_w[*a].division.c_str());
    char *dep_time = PQgetvalue(rs_b,0,0);
    std::string dep(dep_time);
    char *arr_time = PQgetvalue(rs_b,0,1);
    std::string arr(arr_time);
    gtk_label_set_text(GTK_LABEL(StartWorkD),dep.c_str());
    gtk_label_set_text(GTK_LABEL(FinishWorkD),arr.c_str());
    GtkTreeModel *ls = gtk_tree_view_get_model(GTK_TREE_VIEW(SeansesViewD));
    gtk_list_store_clear(GTK_LIST_STORE(ls));
    list_sessions.clear();
    std::vector<auth> list_auth(0);
    for (int i = 0; i < n; ++i) {
        auth one;
        one.id = std::stoi(std::string(PQgetvalue(rs_a,i,0)));
        one.date = std::string(PQgetvalue(rs_a,i,2));
        one.time = std::string(PQgetvalue(rs_a,i,1));
        if (PQgetvalue(rs_a,i,3)[0] == 'f') {
            one.status1 = false;
        } else {
            one.status1 = true;
        }
        list_auth.push_back(one);
    }
    int s = (int) list_auth.size();
    for (int j = 0; j < s-1; ++j) {
        for (int k = 0; k < s-1; ++k) {
            if (list_auth[k].id > list_auth[k+1].id) {
                auth c = list_auth[k];
                list_auth[k] = list_auth[k+1];
                list_auth[k+1] = c;
            }
        }
    }
    for (int i = 0; i < n/2; ++i) {
        session one;
        one.id = i;
        one.date1 = list_auth[2*i].date;
        one.time1 = list_auth[2*i].time;
        one.date2 = list_auth[2*i+1].date;
        one.time2 = list_auth[2*i+1].time;
        list_sessions.push_back(one);
        GtkTreeIter *iter;
        gtk_list_store_append(GTK_LIST_STORE(ls),iter);
        gtk_list_store_set(GTK_LIST_STORE(ls),iter,0,one.id,1,one.date1.c_str(),
                           2,one.time1.c_str(), 3,one.status1.c_str(),
                           4,one.date2.c_str(),5,one.time2.c_str(),6,one.status2.c_str());
    }
    if (n % 2 == 1) {
        session one;
        one.id = n/2 +1;
        one.date1 = list_auth[n-1].date;
        one.time1 = list_auth[n-1].time;
        list_sessions.push_back(one);
        GtkTreeIter *iter;
        gtk_list_store_append(GTK_LIST_STORE(ls),iter);
        gtk_list_store_set(GTK_LIST_STORE(ls),iter,0,one.id,1,one.date1.c_str(),
                           2,one.time1.c_str(), 3,one.status1.c_str(),
                           4,one.date2.c_str(),5,one.time2.c_str(),6,one.status2.c_str());
    }
}

void Sort_workers(GtkWidget *object){
    switch (status_sort_workers){
        case -1:
            status_sort_workers = 0;
            for (int i = 0; i < list_w.size()-1; ++i) {
                for (int j = 0; j < list_w.size()-1; ++j) {
                    if (list_w[j].id > list_w[j+1].id) {
                        worker_info c = list_w[j];
                        list_w[j] = list_w[j+1];
                        list_w[j+1] = c;
                    }
                }
            }
            break;
        case 0:
            status_sort_workers = 1;
            for (int i = 0; i < list_w.size()/2; ++i) {
                worker_info c = list_w[i];
                list_w[i] = list_w[list_w.size()-1-i];
                list_w[list_w.size()-1-i] = c;
            }
            break;
        case 1:
            status_sort_workers = 0;
            for (int i = 0; i < list_w.size()/2; ++i) {
                worker_info c = list_w[i];
                list_w[i] = list_w[list_w.size()-1-i];
                list_w[list_w.size()-1-i] = c;
            }
            break;
        default:
            journal << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                    << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60))
                    << ":  developmet error DirectorApp.h:381" << "\n";
            exit(ERROR_SORT);
    }
}

#endif //INC_345MF_DIRECTORAPP_H
