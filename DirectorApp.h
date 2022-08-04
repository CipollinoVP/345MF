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
GtkWidget *ApprovalButtonD;


//Виджеты окна заказа пропусков
GtkWidget *windowO;
GtkWidget *SurnameEnterO;
GtkWidget *NameEnterO;
GtkWidget *FathernameEnterO;
GtkWidget *DocumentTypeEnterO;
GtkWidget *DocumentNumEnterO;
GtkWidget *DateEnterO;
GtkWidget *MonthEnterO;
GtkWidget *YearEnterO;
GtkWidget *CancelButtonO;
GtkWidget *HourEnterO;
GtkWidget *MinutEnterO;
GtkWidget *OrganizationEnterO;
GtkWidget *OrderButtonO;
GtkWidget *ShowSinglePassesButtonO;

//Необходимое для заказа пропусков
std::string surname;
std::string name;
std::string fathername;
std::string type_document;
std::string num_document;
std::string organization;
std::string date_pass;
std::string time_pass;
int id_director;

//Виджеты диалога
GtkWidget *DialogH;
GtkWidget *LabelH;
GtkWidget *CancelButtonH;
GtkWidget *AcceptButtonH;

//Виджеты окна согласования пропусков
GtkWidget *windowI;
GtkWidget *ViewPassesI;
GtkWidget *AcceptButtonI;
GtkWidget *DeclineButtonI;
GtkWidget *CancelButtonI;

bool m_status = false;

int status_sort_workers = -1;

int finish_program_Dapp = 0;

int select_single_pass = -1;

static void create_window_director();

static void create_window_single_pass_order();

static void create_window_single_pass_accept();

int director_window(int argc, char *argv[], bool status);

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

extern "C" void ApprovalButton_Press(GtkWidget *object);

extern "C" void CancelButtonO_press(GtkWidget *object);

extern "C" void CancelButtonH_press(GtkWidget *object);

extern "C" void Press_OrderButtonO(GtkWidget *object);

extern "C" void ApprovalButtonH_Press(GtkWidget *object);

extern "C" void CancelButtonI_press(GtkWidget *object);

extern "C" void AcceptButtonI_press(GtkWidget *object);

extern "C" void DeclineButtonI_press(GtkWidget *object);

extern "C" void SelectSinglePassI(GtkWidget *object);

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

struct single_pass{
    int id = 0;
    std::string name;
    std::string surname;
    std::string fathername;
    std::string type_document;
    std::string num_document;
    std::string organization;
    std::string date_pass;
    std::string time_pass;
    std::string status;
    std::string date_order;
    std::string time_order;
    std::string director_name;
};

std::vector<single_pass> list_single_passes;

std::vector<worker_info> list_w;

std::vector<session> list_sessions;

void list_passes_apology_refresh();


void window_destroy_Dapp(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_Dapp = 1;
    gtk_main_quit();
}

static void create_window_director()
{
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./AdminApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);

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
    if(!(SeansesViewD = GTK_WIDGET(gtk_builder_get_object(builder, "SeansesView"))))
        g_critical("Ошибка при получении виджета окна\n");
    if (m_status) {
        if(!(ApprovalButtonD = GTK_WIDGET(gtk_builder_get_object(builder, "AppologyButton"))))
            g_critical("Ошибка при получении виджета окна\n");
        gtk_widget_set_visible(ApprovalButtonD,true);
    }
    g_object_unref(builder);
}

int director_window(int argc, char *argv[], bool status){
    std::string query("SELECT id_workers FROM registers_user WHERE login_database = session_user;");
    PGresult *id_res = PQexec(conn,query.c_str());
    id_director = std::stoi(std::string(PQgetvalue(id_res,0,0)));
    m_status = status;
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
    if (m_status) {
        g_signal_connect(G_OBJECT(ApprovalButtonD), "clicked", G_CALLBACK(ApprovalButton_Press), NULL);
    }
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
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM"
        <<" workers,divisions WHERE ((division = divisions.id) AND (surname LIKE '" << SurnameS <<
              "%' ));";
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
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM divisions,workers WHERE"<<
        " ((division = divisions.id) AND (name LIKE '"
        << NameS <<
              "%' ));";
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
    if (!FathernameS.empty()) {
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM divisions,workers WHERE" <<
                 " ((division = divisions.id) AND (fathername LIKE '"
        << FathernameS << "%' ));";
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
    if (!PostS.empty()) {
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM divisions,workers WHERE "<<
                        "((division = divisions.id) AND (post LIKE '" << PostS <<
              "%' ));";
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
    if (!DivisionS.empty()) {
        query << "SELECT workers.id,name,surname,fathername,post,divisions_name FROM divisions,workers WHERE "<<
        "((division = divisions.id) AND (division_name LIKE '" << DivisionS <<
              "%' ));";
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
            GtkTreeIter iter;
            gtk_list_store_append(GTK_LIST_STORE(list),&iter);
            gtk_list_store_set(GTK_LIST_STORE(list),&iter,0,worker.id,1,worker.surname.c_str(),
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
    create_window_single_pass_order();
    g_signal_connect(G_OBJECT(CancelButtonO), "clicked", G_CALLBACK(CancelButtonO_press), NULL);
    g_signal_connect(G_OBJECT(CancelButtonH), "clicked", G_CALLBACK(CancelButtonH_press), NULL);
    g_signal_connect(G_OBJECT(OrderButtonO), "clicked", G_CALLBACK(Press_OrderButtonO), NULL);
    g_signal_connect(G_OBJECT(AcceptButtonH),"clicked", G_CALLBACK(ApprovalButtonH_Press),NULL);
    gtk_widget_show(windowO);
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
    GtkListStore *ls = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(SeansesViewD)));
    gtk_list_store_clear(ls);
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
        one.id = i+1;
        one.date1 = list_auth[2*i].date;
        one.time1 = list_auth[2*i].time;
        one.date2 = list_auth[2*i+1].date;
        one.time2 = list_auth[2*i+1].time;
        list_sessions.push_back(one);
        GtkTreeIter iter;
        gtk_list_store_append(ls,&iter);
        gtk_list_store_set(ls,&iter,0,one.id,1,one.date1.c_str(),
                           2,one.time1.c_str(), 3,one.status1.c_str(),
                           4,one.date2.c_str(),5,one.time2.c_str(),6,one.status2.c_str());
    }
    if (n % 2 == 1) {
        session one;
        one.id = n/2 +2;
        one.date1 = list_auth[n-1].date;
        one.time1 = list_auth[n-1].time;
        list_sessions.push_back(one);
        GtkTreeIter iter;
        gtk_list_store_append(ls,&iter);
        gtk_list_store_set(ls,&iter,0,one.id,1,one.date1.c_str(),
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

void ApprovalButton_Press(GtkWidget *object){
    create_window_single_pass_accept();
    g_signal_connect(G_OBJECT(CancelButtonI), "clicked", G_CALLBACK(CancelButtonI_press), NULL);
    g_signal_connect(G_OBJECT(ViewPassesI), "cursor-changed", G_CALLBACK(SelectSinglePassI), NULL);
    g_signal_connect(G_OBJECT(AcceptButtonI), "clicked", G_CALLBACK(AcceptButtonI_press), NULL);
    g_signal_connect(G_OBJECT(DeclineButtonI),"clicked", G_CALLBACK(DeclineButtonI_press),NULL);
    list_passes_apology_refresh();
    gtk_widget_show(windowI);
}

void list_passes_apology_refresh(){
    std::stringstream query;
    GtkListStore *ListApology = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(ViewPassesI)));
    gtk_list_store_clear(ListApology);
    query << "SELECT * FROM single_passes WHERE pass_using = false;";
    PGresult *res = PQexec(conn,query.str().c_str());
    int n = PQntuples(res);
    list_single_passes.clear();
    for (int i = 0; i < n; ++i) {
        single_pass pass;
        pass.surname = std::string(PQgetvalue(res,i,0));
        pass.name = std::string(PQgetvalue(res,i,1));
        pass.fathername = std::string(PQgetvalue(res,i,2));
        pass.id = std::stoi(std::string(PQgetvalue(res,i,3)));
        pass.type_document = std::string(PQgetvalue(res,i,6));
        pass.num_document = std::string(PQgetvalue(res,i,7));
        char *s = PQgetvalue(res,i,8);
        if (s[0] == 'f') {
            pass.status = "Не согласовано";
        } else {
            pass.status = "Согласовано";
        }
        pass.organization = std::string(PQgetvalue(res,i,9));
        pass.date_pass = std::string(PQgetvalue(res,i,12));
        pass.time_pass = std::string(PQgetvalue(res,i,13));
        pass.date_order = std::string(PQgetvalue(res,i,10));
        pass.time_order = std::string(PQgetvalue(res,i,11));
        int id_order_director = std::stoi(std::string(PQgetvalue(res,i,5)));
        std::stringstream query1;
        query1 << "SELECT surname,name,fathername FROM workers WHERE id =" << id_order_director << ";";
        PGresult *res1 = PQexec(conn,query1.str().c_str());
        std::stringstream director_name_s;
        director_name_s << std::string(PQgetvalue(res1,0,1)).substr(0,1) << "."
                        << std::string(PQgetvalue(res1,0,2)).substr(0,1) << ". "
                        << std::string(PQgetvalue(res1,0,0));
        pass.director_name = director_name_s.str();
        list_single_passes.push_back(pass);
        GtkTreeIter iter;
        gtk_list_store_append(ListApology,&iter);
        gtk_list_store_set(ListApology,&iter,0,pass.surname.c_str(),1,pass.name.c_str(),2,pass.fathername.c_str(),
                           3,pass.type_document.c_str(),4,pass.num_document.c_str(),5,pass.organization.c_str(),
                           6,pass.status.c_str(),7,pass.director_name.c_str(),8,pass.date_pass.c_str(),
                           9,pass.time_pass.c_str(),10,pass.date_order.c_str(),11,pass.time_order.c_str());
    }
}

static void create_window_single_pass_accept(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./AdminApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(windowI = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassAcceptWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ViewPassesI = GTK_WIDGET(gtk_builder_get_object(builder, "ViewSinglePass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AcceptButtonI = GTK_WIDGET(gtk_builder_get_object(builder, "AcceptButtonI"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DeclineButtonI = GTK_WIDGET(gtk_builder_get_object(builder, "DeclineButtonI"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonI = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonI"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

static void create_window_single_pass_order(){
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./AdminApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);
    if(!(windowO = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassOrderWindow"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SurnameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "NameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FathernameEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DocumentTypeEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "DocumentTypeEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DocumentNumEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "DocumentNumEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OrganizationEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "OrganizationEntryO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DateEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "DateComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(MonthEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "MonthComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(YearEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "YearComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(OrderButtonO = GTK_WIDGET(gtk_builder_get_object(builder, "OrderButtonO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonO = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonO"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ShowSinglePassesButtonO = GTK_WIDGET(gtk_builder_get_object(builder, "ShowSinglePassesButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DialogH = GTK_WIDGET(gtk_builder_get_object(builder, "DialogSinglePass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AcceptButtonH = GTK_WIDGET(gtk_builder_get_object(builder, "ButtonOkDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(LabelH = GTK_WIDGET(gtk_builder_get_object(builder, "LabelInfoDialog"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(HourEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "HourComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(MinutEnterO = GTK_WIDGET(gtk_builder_get_object(builder, "MinutComboBox"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

void CancelButtonO_press(GtkWidget *object){
    gtk_window_close(GTK_WINDOW(windowO));
}

void CancelButtonH_press(GtkWidget *object){
    gtk_widget_destroy(DialogH);
}

void Press_OrderButtonO(GtkWidget *object){
    surname = std::string(gtk_entry_get_text(GTK_ENTRY(SurnameEnterO)));
    name = std::string(gtk_entry_get_text(GTK_ENTRY(NameEnterO)));
    fathername = std::string(gtk_entry_get_text(GTK_ENTRY(FathernameEnterO)));
    type_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentTypeEnterO)));
    num_document = std::string(gtk_entry_get_text(GTK_ENTRY(DocumentNumEnterO)));
    organization = std::string(gtk_entry_get_text(GTK_ENTRY(OrganizationEnterO)));
    int day = gtk_combo_box_get_active(GTK_COMBO_BOX(DateEnterO))+1;
    int month = gtk_combo_box_get_active(GTK_COMBO_BOX(MonthEnterO))+1;
    int year = gtk_combo_box_get_active(GTK_COMBO_BOX(YearEnterO))+2022;
    int hour = gtk_combo_box_get_active(GTK_COMBO_BOX(HourEnterO));
    int minute = gtk_combo_box_get_active(GTK_COMBO_BOX(MinutEnterO));
    std::stringstream pass_date;
    pass_date << year << "-" << month << "-" << day;
    date_pass = pass_date.str();
    std::stringstream pass_time;
    pass_time << hour << ":" << minute << "+03:00";
    time_pass = pass_time.str();
    std::stringstream info_label;
    info_label << "Подтвердите заказ пропуска\n" << "Фамилия: " << surname << std::endl <<
    "Имя: " << name << std::endl << "Отчество: " << fathername << std::endl << "Тип документа: " <<
    type_document << std::endl << "Номер документа: " << num_document << std::endl <<
    "Организация: " << organization << std::endl << "Дата: " << date_pass << std::endl <<
    "Время: " << time_pass;
    gtk_label_set_text(GTK_LABEL(LabelH),info_label.str().c_str());
    gtk_dialog_run(GTK_DIALOG(DialogH));
}

void ApprovalButtonH_Press(GtkWidget *object){
    std::stringstream  query;
    query << "INSERT INTO single_passes "<< std::endl
    <<"(surname,name,fathername,type_document,number_document,organization,date_pass,"
    <<"time_pass,date_query,time_query,id_director)"<< std::endl
    <<" VALUES ('" << surname << "','" << name <<"','" << fathername << "','" <<
    type_document << "','" << num_document << "','" << organization << "','"<< date_pass << "','" <<
    time_pass << "',now(),now(),"<< id_director << ");";
    PQexec(conn,query.str().c_str());
    if (m_status) {
        std::stringstream query1;
        query1 << "UPDATE single_passes SET status_pass = true WHERE ((name = '" << name
        << "') AND (surname = '" << surname << "') AND (date_pass ='" << date_pass << "'));";
        PQexec(conn,query1.str().c_str());
    }
    gtk_widget_destroy(DialogH);
    gtk_window_close(GTK_WINDOW(windowO));
}

void CancelButtonI_press(GtkWidget *object){
    gtk_window_close(GTK_WINDOW(windowI));
}

void AcceptButtonI_press(GtkWidget *object){
    if (select_single_pass == -1) {
        return;
    }
    std::stringstream query;
    query << "UPDATE single_passes SET status_pass = true  WHERE id = " <<
    list_single_passes[select_single_pass].id << ";";
    PQexec(conn,query.str().c_str());
    list_passes_apology_refresh();
}

void DeclineButtonI_press(GtkWidget *object){
    if (select_single_pass == -1) {
        return;
    }
    std::stringstream query;
    query << "DELETE FROM single_passes WHERE id = " <<
          list_single_passes[select_single_pass].id << ";";
    PQexec(conn,query.str().c_str());
    list_passes_apology_refresh();
}

void SelectSinglePassI(GtkWidget *object){
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(ViewPassesI),&path,&col);
    int* a = gtk_tree_path_get_indices(path);
    if (a == nullptr) {
        select_single_pass = -1;
        return;
    }
    select_single_pass = *a;
}

#endif //INC_345MF_DIRECTORAPP_H
