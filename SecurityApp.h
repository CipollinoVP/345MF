//
// Created by vadik on 27.07.22.
//

#ifndef INC_345MF_SECURITYAPP_H
#define INC_345MF_SECURITYAPP_H

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <gtk/gtk.h>
#include <vector>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/videoio.hpp"
#include "postgres.h"
#include <filesystem>

#define NO_QR -1
#define EXACT_QR 0
#define ERR_PASS -1
#define NO_ERR_PASS 0
#define SIZE_PERSONAL_CODE 37
#define SIZE_FACTORY_CODE 32
#define FACTORY_PASSWORD "RuMosRegionBalashkihaCity345MZVP"

// Виджеты окна охраны
GtkWidget *windowM;
GtkWidget *SurnameLM;
GtkWidget *NameLM;
GtkWidget *FathernameLM;
GtkWidget *PostLM;
GtkWidget *DivisionLM;
GtkWidget *JournalTextM;
GtkWidget *AvatarImgM;
GtkWidget *EscapeButtonM;
GtkWidget *CancelButtonM;
GtkWidget *SinglePassButtonM;
GtkWidget *HandEnterButtonM;

//Виджеты окна разовых пропусков
GtkWidget *windowP;
GtkWidget *ViewPassesP;
GtkWidget *CancelButtonP;
GtkWidget *AcceptButtonP;
GtkWidget *StatusLabelP;

//Выводимые данные о сотруднике
std::vector<std::string> personal_data_s;

//Флаг завершения работы программы 
int finish_program_s = 0;

int choosing = -1;

bool flag_image = false;

//Проверка на QR-код
void QR_Scan(int& param, std::string& password);

//Авторизация сотрудника при обнаружении QR-кода
std::string auhtorizate_appear(int& err, std::string const& password_worker, std::vector<std::string>& worker_data);

//Функция таймерв: установка периодичности проверки QR-кода
gboolean TimerFunc(gpointer data);

extern "C" void window_destroy_security(GtkWidget *object);

extern "C" void single_pass_button(GtkWidget *object);

extern "C" void hand_enter_button(GtkWidget *object);

extern "C" void cancel_button_m(GtkWidget *object);

extern "C" void cancel_button_p(GtkWidget *object);

extern "C" void accept_button(GtkWidget *object);

extern "C" void choose_passes(GtkWidget *object);

static void create_window_single_passes();

static void create_window_checkpoint();

void single_pass_refresh();

struct pass_data{
    int id = 0;
    std::string surname;
    std::string name;
    std::string fathername;
    std::string doc_type;
    std::string doc_num;
    std::string organization;
    bool status = false;
    std::string director_name;
    std::string pass_time;
};

std::vector<pass_data> passes_data(0);

void QR_Scan(int& param, std::string& password) {
    cv::VideoCapture cap;
    cv::Mat frame;
    cap.open(0);
    cap >> frame;
    cv::QRCodeDetector qrDecoder = cv::QRCodeDetector();
    cv::Mat bbox, rectifiedImage;
    std::string data = qrDecoder.detectAndDecode(frame, bbox, rectifiedImage);
    if (data.length() > 0) {
        param = EXACT_QR;
        std::cout << '\a';
        password = data;
    } else {
        param = NO_QR;
    }
}

gboolean TimerFunc(gpointer data)
{
    if (finish_program_s == 1) {
        return FALSE;
    }
    int res = 1;
    std::string personal_password;
    QR_Scan(res,personal_password);
    if (res == EXACT_QR) {
        int result_authorizate;
        std::string result_report = auhtorizate_appear(result_authorizate,
                                                       personal_password,personal_data_s);
        std::string journalL = gtk_label_get_text(GTK_LABEL(JournalTextM));
        journalL.append(result_report);
        gtk_label_set_text(GTK_LABEL(JournalTextM),journalL.c_str());
        if (result_authorizate == NO_ERR_PASS) {
            gtk_label_set_text(GTK_LABEL(SurnameLM),personal_data_s[0].c_str());
            gtk_label_set_text(GTK_LABEL(NameLM),personal_data_s[1].c_str());
            gtk_label_set_text(GTK_LABEL(FathernameLM),personal_data_s[2].c_str());
            gtk_label_set_text(GTK_LABEL(PostLM),personal_data_s[4].c_str());
            if (personal_data_s[3].empty()) {
                gtk_label_set_text(GTK_LABEL(DivisionLM),"Директор");
            } else {
                gtk_label_set_text(GTK_LABEL(DivisionLM),personal_data_s[3].c_str());
            }
        }
    }
    return TRUE;
}

static void create_window_checkpoint()
{
    GtkBuilder *builder;
    GError* error = nullptr;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./CheckpointApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, nullptr);

    if(!(windowM = GTK_WIDGET(gtk_builder_get_object(builder, "window"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SurnameLM = GTK_WIDGET(gtk_builder_get_object(builder, "SurnameL"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(NameLM = GTK_WIDGET(gtk_builder_get_object(builder, "NameL"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(FathernameLM = GTK_WIDGET(gtk_builder_get_object(builder, "FathernameL"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(PostLM = GTK_WIDGET(gtk_builder_get_object(builder, "PostL"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(JournalTextM = GTK_WIDGET(gtk_builder_get_object(builder, "JournalText"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(DivisionLM = GTK_WIDGET(gtk_builder_get_object(builder, "DivisionL"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AvatarImgM = GTK_WIDGET(gtk_builder_get_object(builder, "AvatarImg"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(EscapeButtonM = GTK_WIDGET(gtk_builder_get_object(builder, "ExitButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(SinglePassButtonM = GTK_WIDGET(gtk_builder_get_object(builder, "SinglePassButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(HandEnterButtonM = GTK_WIDGET(gtk_builder_get_object(builder, "HandEnter"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonM = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

static void create_window_single_passes(){
    GtkBuilder *builder;
    GError* error = nullptr;
    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./CheckpointApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }
    if(!(windowP = GTK_WIDGET(gtk_builder_get_object(builder, "Single_Pass_Dialog_window"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(ViewPassesP = GTK_WIDGET(gtk_builder_get_object(builder, "ViewSinglePass"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(CancelButtonP = GTK_WIDGET(gtk_builder_get_object(builder, "CancelButtonP"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(AcceptButtonP = GTK_WIDGET(gtk_builder_get_object(builder, "AcceptButton"))))
        g_critical("Ошибка при получении виджета окна\n");
    if(!(StatusLabelP = GTK_WIDGET(gtk_builder_get_object(builder, "StatusLabelP"))))
        g_critical("Ошибка при получении виджета окна\n");
    g_object_unref(builder);
}

void do_exit(PGconn *pgConn) {
    PQfinish(pgConn);
    exit(1);
}

std::string auhtorizate_appear(int& err, std::string const& password_worker, std::vector<std::string>& worker_data) {
    if (password_worker.size() != SIZE_PERSONAL_CODE) {
        err = ERR_PASS;
        return "Ошибка QR-кода, не является пропуском предприятия\n";
    } else {
        std::string factory_password;
        for (int i = 0; i < SIZE_FACTORY_CODE; ++i) {
            factory_password.push_back(password_worker[i]);
        }
        if (factory_password != FACTORY_PASSWORD) {
            err = ERR_PASS;
            return "Ошибка QR-кода, не является пропуском предприятия\n";
        } else {
            std::string num_s;

            for (int i = SIZE_FACTORY_CODE; i < SIZE_PERSONAL_CODE; ++i) {
                num_s.push_back(password_worker[i]);
            }
            int num = std::stoi(num_s);
            if (num < 10000) {
                std::stringstream command;
                command << "SELECT status FROM workers WHERE id = ";
                command << num;
                command << ";";
                std::string command_s = command.str();
                PGresult *res_id = PQexec(conn, command_s.c_str());
                char* n_s = PQgetvalue(res_id,0,0);
                if (n_s == nullptr) {
                    err = ERR_PASS;
                    return "Ошибка: неверный номер пропуска\n";
                } else {
                    if (flag_image) {
                        std::filesystem::remove("ava.jpg");
                    }
                    flag_image = true;
                    if (n_s[0] == 'f') {
                        std::stringstream command1;
                        command1 << "UPDATE workers SET status = true WHERE id = ";
                        command1 << num;
                        command1 << ";";
                        std::string command_s1 = command1.str();
                        PGresult *rs = PQexec(conn,command_s1.c_str());
                        if (PQresultStatus(rs) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream  command_autho;
                        command_autho << "INSERT INTO authorizate (idworker,time_enter,date_enter,status_enter) VALUES ( "
                        << num << " ,current_timestamp,current_timestamp,true);";
                        std::string command_autho_s = command_autho.str();
                        PGresult *rs_a = PQexec(conn,command_autho_s.c_str());
                        if (PQresultStatus(rs_a) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs_a);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream command2;
                        command2 << "SELECT surname FROM workers WHERE id = ";
                        command2 << num;
                        command2 << ";";
                        std::string command_s2 = command2.str();
                        PGresult *rs_surname = PQexec(conn, command_s2.c_str());
                        char* surname_s = PQgetvalue(rs_surname,0,0);
                        worker_data.resize(5);
                        worker_data[0] = std::string(surname_s);
                        std::stringstream command3;
                        command3 << "SELECT name FROM workers WHERE id = ";
                        command3 << num;
                        command3 << ";";
                        std::string command_s3 = command3.str();
                        PGresult *rs_name = PQexec(conn, command_s3.c_str());
                        char* name_s = PQgetvalue(rs_name,0,0);
                        worker_data[1] = std::string(name_s);
                        std::stringstream command4;
                        command4 << "SELECT fathername FROM workers WHERE id = ";
                        command4 << num;
                        command4 << ";";
                        std::string command_s4 = command4.str();
                        PGresult *rs_fathername = PQexec(conn, command_s4.c_str());
                        char* fathername_s = PQgetvalue(rs_fathername,0,0);
                        worker_data[2] = std::string(fathername_s);
                        std::stringstream command5;
                        command5 << "SELECT divisions_name FROM workers, divisions"
                             << " WHERE ((divisions.id = division) AND (workers.id = ";
                        command5 << num;
                        command5 << "));";
                        std::string command_s5 = command5.str();
                        PGresult *rs_division = PQexec(conn, command_s5.c_str());
                        char* division_s = PQgetvalue(rs_division,0,0);
                        if (division_s != nullptr) {
                            worker_data[3] = std::string(division_s);
                        } else {worker_data[3] = "";}
                        std::stringstream command6;
                        command6 << "SELECT post FROM workers WHERE id = ";
                        command6 << num;
                        command6 << ";";
                        std::string command_s6 = command6.str();
                        PGresult *rs_post = PQexec(conn, command_s6.c_str());
                        char* post_s = PQgetvalue(rs_post,0,0);
                        worker_data[4] = std::string(post_s);
                        std::string curr_path = std::filesystem::current_path().string();
                        std::stringstream command7;
                        command7 << "SELECT lo_export(workers.avatar, '" << curr_path
                        <<"\\ava.jpg') FROM workers WHERE id = ";
                        command7 << num;
                        command7 << ";";
                        std::string command_s7 = command7.str();
                        PGresult *rs_avatar = PQexec(conn, command_s7.c_str());
                        gtk_image_set_from_file(GTK_IMAGE(AvatarImgM),"ava.jpg");
                        err = NO_ERR_PASS;
                        std::stringstream result_stream;
                        result_stream << "Авторизован вход: " << worker_data[1] << " "
                                  << worker_data[2] << " " <<
                                  worker_data[0] << "  " << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                                  << (time(nullptr) % (3600))/60 << ":" << (time(nullptr) % (60))
                                  << "\n";
                        return result_stream.str();
                    } else {
                        std::stringstream command1;
                        command1 << "UPDATE workers SET status = false WHERE id = ";
                        command1 << num;
                        command1 << ";";
                        std::string command_s1 = command1.str();
                        PGresult *rs = PQexec(conn,command_s1.c_str());
                        if (PQresultStatus(rs) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream  command_autho;
                        command_autho << "INSERT INTO authorizate (idworker,time_enter,date_enter,status_enter) VALUES ("
                                  << num << ",current_timestamp,current_timestamp,false);";
                        std::string command_autho_s = command_autho.str();
                        PGresult *rs_a = PQexec(conn,command_autho_s.c_str());
                        if (PQresultStatus(rs_a) != PGRES_COMMAND_OK) {
                            for (int i = 0; i < 5; ++i) {
                                rs_a = PQexec(conn, command_autho_s.c_str());
                                if (PQresultStatus(rs_a) == PGRES_COMMAND_OK) {
                                    break;
                                }
                            }
                            if (PQresultStatus(rs_a) != PGRES_COMMAND_OK) {
                                printf("Error update status\n");
                                PQclear(rs_a);
                                do_exit(conn);
                                return "1";
                            }
                        }
                        std::stringstream command2;
                        command2 << "SELECT surname FROM workers WHERE id = ";
                        command2 << num;
                        command2 << ";";
                        std::string command_s2 = command2.str();
                        PGresult *rs_surname = PQexec(conn, command_s2.c_str());
                        char* surname_s = PQgetvalue(rs_surname,0,0);
                        worker_data.resize(5);
                        worker_data[0] = std::string(surname_s);
                        std::stringstream command3;
                        command3 << "SELECT name FROM workers WHERE id = ";
                        command3 << num;
                        command3 << ";";
                        std::string command_s3 = command3.str();
                        PGresult *rs_name = PQexec(conn, command_s3.c_str());
                        char* name_s = PQgetvalue(rs_name,0,0);
                        worker_data[1] = std::string(name_s);
                        std::stringstream command4;
                        command4 << "SELECT fathername FROM workers WHERE id = ";
                        command4 << num;
                        command4 << ";";
                        std::string command_s4 = command4.str();
                        PGresult *rs_fathername = PQexec(conn, command_s4.c_str());
                        char* fathername_s = PQgetvalue(rs_fathername,0,0);
                        worker_data[2] = std::string(fathername_s);
                        std::stringstream command5;
                        command5 << "SELECT divisions_name FROM workers, divisions"
                             << " WHERE ((divisions.id = division) AND (workers.id = ";
                        command5 << num;
                        command5 << "));";
                        std::string command_s5 = command5.str();
                        PGresult *rs_division = PQexec(conn, command_s5.c_str());
                        char* division_s = PQgetvalue(rs_division,0,0);
                        if (division_s != NULL) {
                            worker_data[3] = std::string(division_s);
                        } else {worker_data[3] = "";}
                        std::stringstream command6;
                        command6 << "SELECT post FROM workers WHERE id = ";
                        command6 << num;
                        command6 << ";";
                        std::string command_s6 = command6.str();
                        PGresult *rs_post = PQexec(conn, command_s6.c_str());
                        char* post_s = PQgetvalue(rs_post,0,0);
                        worker_data[4] = std::string(post_s);
                        std::string curr_path = std::filesystem::current_path().string();
                        std::stringstream command7;
                        command7 << "SELECT lo_export(workers.avatar, '" << curr_path
                                 <<"\\ava.jpg') FROM workers WHERE id = ";
                        command7 << num;
                        command7 << ";";
                        std::string command_s7 = command7.str();
                        PGresult *rs_avatar = PQexec(conn, command_s7.c_str());
                        gtk_image_set_from_file(GTK_IMAGE(AvatarImgM),"ava.jpg");
                        err = NO_ERR_PASS;
                        std::stringstream result_stream;
                        result_stream << "Авторизован выход: " << worker_data[1] <<" "
                                    << worker_data[2] << " " <<
                                    worker_data[0] << "  " << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                                    << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60))
                                    << "\n";
                        return result_stream.str();
                    }
                }
            }
            else {
                std::stringstream result_stream;
                result_stream << "Ошибка: неверный номер пропуска\n";
                return result_stream.str();
            }
                /* {
                num = num - 10000;
                std::stringstream command_check;
                command_check << "SELECT status_pass FROM single_passes WHERE id =" << num <<";";
                std::string command_check_s = command_check.str();
                PGresult *rs_a = PQexec(conn,command_check_s.c_str());
                char* s = PQgetvalue(rs_a,0,0);
                if (s == nullptr) {
                    err = ERR_PASS;
                    return "Ошибка: неверный номер пропуска\n";
                } else {
                    if (s[0] == 'f') {
                        return "Ошибка: пропуск использован\n";
                    }
                    std::stringstream  command_enter;
                    command_enter << "SELECT status_factory FROM single_passes WHERE id=" << num <<";";
                    std::string command_enter_s = command_enter.str();
                    PGresult *rs_b = PQexec(conn,command_enter_s.c_str());
                    char* st = PQgetvalue(rs_b,0,0);
                    if (st[0] == 'f') {
                        std::stringstream command1;
                        command1 << "UPDATE single_passes SET status_factory = true WHERE id = ";
                        command1 << num;
                        command1 << ";";
                        std::string command_s1 = command1.str();
                        PGresult *rs = PQexec(conn,command_s1.c_str());
                        if (PQresultStatus(rs) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream command2;
                        command2 << "SELECT surname FROM single_passes WHERE id = ";
                        command2 << num;
                        command2 << ";";
                        std::string command_s2 = command2.str();
                        PGresult *rs_surname = PQexec(conn, command_s2.c_str());
                        char* surname_s = PQgetvalue(rs_surname,0,0);
                        worker_data.resize(5);
                        worker_data[0] = std::string(surname_s);
                        std::stringstream command3;
                        command3 << "SELECT name FROM single_passes WHERE id = ";
                        command3 << num;
                        command3 << ";";
                        std::string command_s3 = command3.str();
                        PGresult *rs_name = PQexec(conn, command_s3.c_str());
                        char* name_s = PQgetvalue(rs_name,0,0);
                        worker_data[1] = std::string(name_s);
                        std::stringstream command4;
                        command4 << "SELECT fathername FROM single_passes WHERE id = ";
                        command4 << num;
                        command4 << ";";
                        std::string command_s4 = command4.str();
                        PGresult *rs_fathername = PQexec(conn, command_s4.c_str());
                        char* fathername_s = PQgetvalue(rs_fathername,0,0);
                        worker_data[2] = std::string(fathername_s);
                        worker_data[4] = "Разовый пропуск";
                        std::stringstream command5;
                        command5 << "SELECT workers.surname FROM workers, single_passes"
                                 << " WHERE ((workers.id = single_passes.id_director) AND (single_passes.id = ";
                        command5 << num;
                        command5 << "));";
                        std::string command_s5 = command5.str();
                        PGresult *rs_division = PQexec(conn, command_s5.c_str());
                        char* division_s = PQgetvalue(rs_division,0,0);
                        worker_data[3] = std::string(division_s);
                        err = NO_ERR_PASS;
                        std::stringstream result_stream;
                        result_stream << "Авторизован вход: " << worker_data[1] <<" "
                                      << worker_data[2] << " " <<
                                      worker_data[0] << "  " << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                                      << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60))
                                      << "\n";
                        return result_stream.str();
                    } else {
                        std::stringstream command1;
                        command1 << "UPDATE single_passes SET status_factory = false WHERE id = ";
                        command1 << num;
                        command1 << ";";
                        std::string command_s1 = command1.str();
                        PGresult *rs = PQexec(conn,command_s1.c_str());
                        if (PQresultStatus(rs) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream command_cancel;
                        command_cancel << "UPDATE single_passes SET status_pass = false WHERE id = ";
                        command_cancel << num;
                        command_cancel << ";";
                        std::string command_cancel1 = command_cancel.str();
                        PGresult *rs_cancel = PQexec(conn,command_cancel1.c_str());
                        if (PQresultStatus(rs_cancel) != PGRES_COMMAND_OK) {
                            printf("Error update status\n");
                            PQclear(rs);
                            do_exit(conn);
                            return "1";
                        }
                        std::stringstream command2;
                        command2 << "SELECT surname FROM single_passes WHERE id = ";
                        command2 << num;
                        command2 << ";";
                        std::string command_s2 = command2.str();
                        PGresult *rs_surname = PQexec(conn, command_s2.c_str());
                        char* surname_s = PQgetvalue(rs_surname,0,0);
                        worker_data.resize(5);
                        worker_data[0] = std::string(surname_s);
                        std::stringstream command3;
                        command3 << "SELECT name FROM single_passes WHERE id = ";
                        command3 << num;
                        command3 << ";";
                        std::string command_s3 = command3.str();
                        PGresult *rs_name = PQexec(conn, command_s3.c_str());
                        char* name_s = PQgetvalue(rs_name,0,0);
                        worker_data[1] = std::string(name_s);
                        std::stringstream command4;
                        command4 << "SELECT fathername FROM single_passes WHERE id = ";
                        command4 << num;
                        command4 << ";";
                        std::string command_s4 = command4.str();
                        PGresult *rs_fathername = PQexec(conn, command_s4.c_str());
                        char* fathername_s = PQgetvalue(rs_fathername,0,0);
                        worker_data[2] = std::string(fathername_s);
                        worker_data[4] = "Разовый пропуск";
                        std::stringstream command5;
                        command5 << "SELECT workers.surname FROM workers, single_passes"
                                 << " WHERE ((workers.id = single_passes.id_director) AND (single_passes.id = ";
                        command5 << num;
                        command5 << "));";
                        std::string command_s5 = command5.str();
                        PGresult *rs_division = PQexec(conn, command_s5.c_str());
                        char* division_s = PQgetvalue(rs_division,0,0);
                        worker_data[3] = std::string(division_s);
                        err = NO_ERR_PASS;
                        std::stringstream result_stream;
                        result_stream << "Авторизован выход: " << worker_data[1] <<" "
                                      << worker_data[2] << " " <<
                                      worker_data[0] << "  " << (time(nullptr) % (24*3600))/3600 + 3 <<":"
                                      << (time(nullptr) % (3600))/60  << ":" << (time(nullptr) % (60))
                                      << "\n";
                        return result_stream.str();
                    }
                }
            }*/
        }
    }
}

int checkpoint_unit(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    create_window_checkpoint();
    g_signal_connect(G_OBJECT(windowM), "destroy", G_CALLBACK(window_destroy_security), NULL);
    g_signal_connect(G_OBJECT(windowM), "destroy-event", G_CALLBACK(window_destroy_security), NULL);
    g_signal_connect(G_OBJECT(EscapeButtonM), "clicked", G_CALLBACK(window_destroy_security), NULL);
    g_signal_connect(G_OBJECT(SinglePassButtonM), "clicked", G_CALLBACK(single_pass_button), NULL);
    g_signal_connect(G_OBJECT(HandEnterButtonM), "clicked", G_CALLBACK(hand_enter_button), NULL);
    g_signal_connect(G_OBJECT(CancelButtonM), "clicked", G_CALLBACK(cancel_button_m), NULL);
    gtk_widget_show(windowM);
    g_timeout_add(2000,TimerFunc,(gpointer) windowM);
    /* передаём управление GTK+ */
    gtk_main ();
    return 0;
}

void single_pass_button(GtkWidget *object){
    create_window_single_passes();
    g_signal_connect(G_OBJECT(CancelButtonP), "clicked", G_CALLBACK(cancel_button_p), NULL);
    g_signal_connect(G_OBJECT(AcceptButtonP), "clicked", G_CALLBACK(accept_button), NULL);
    g_signal_connect(G_OBJECT(ViewPassesP), "cursor-changed", G_CALLBACK(choose_passes), NULL);
    single_pass_refresh();
    gtk_widget_show(windowP);
}

void single_pass_refresh(){
    std::stringstream query;
    query << "SELECT single_passes.id,"
    <<"single_passes.surname,single_passes.name,single_passes.fathername,single_passes.type_document" <<
          ",single_passes.status_factory,single_passes.number_document,workers.name,workers.surname,workers.fathername,"
          << "single_passes.organization, single_passes.time_pass"
          <<" FROM single_passes,workers WHERE" <<
          " ((single_passes.status_pass = true) AND (single_passes.id_director = workers.id) AND "
          <<"(single_passes.date_pass = now()));";
    PGresult *res = PQexec(conn,query.str().c_str());
    int n = PQntuples(res);
    GtkListStore *list = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(ViewPassesP)));
    gtk_list_store_clear(list);
    passes_data.clear();
    for (int i = 0; i < n; ++i) {
        pass_data dat;
        dat.id = std::stoi(std::string(PQgetvalue(res,i,0)));
        dat.surname = std::string(PQgetvalue(res,i,1));
        dat.name = std::string(PQgetvalue(res,i,2));
        dat.fathername = std::string(PQgetvalue(res,i,3));
        dat.doc_type = std::string(PQgetvalue(res,i,4));
        dat.doc_num = std::string(PQgetvalue(res,i,5));
        dat.pass_time = std::string(PQgetvalue(res,i,11));
        char* t = PQgetvalue(res,i,6);
        if (t[0] == 'f') {
            dat.status = false;
        } else {
            dat.status = true;
        }
        std::string director_surname(PQgetvalue(res,i,7));
        std::string director_name(PQgetvalue(res,i,8));
        std::string director_fathername(PQgetvalue(res,i,9));
        std::stringstream dir_init;
        dir_init << director_name.substr(0,1) << "." << director_fathername.substr(0,1) << "." <<
        director_surname;
        dat.director_name = dir_init.str();
        dat.organization = std::string(PQgetvalue(res,i,10));
        GtkTreeIter iter;
        gtk_list_store_append(list,&iter);
        gtk_list_store_set(list,&iter,0,dat.surname.c_str(),1,dat.name.c_str(),
                           2,dat.fathername.c_str(), 3,dat.doc_type.c_str(),
                           4, dat.doc_num.c_str(),5,dat.organization.c_str(),6,dat.status,7,dat.director_name.c_str(),
                           8,dat.pass_time.c_str());
        passes_data.push_back(dat);
    }
}

void hand_enter_button(GtkWidget *object){

}

void cancel_button_m(GtkWidget *object){

}

void cancel_button_p(GtkWidget *object){
    gtk_window_close(GTK_WINDOW(windowP));
}

void accept_button(GtkWidget *object){
    if (choosing == -1) {
        gtk_label_set_text(GTK_LABEL(StatusLabelP),"Не выбран пропуск");
        return;
    }
    std::stringstream query;
    query << "SELECT status_factory FROM single_passes WHERE id = " << passes_data[choosing].id << ";";
    PGresult *res = PQexec(conn,query.str().c_str());
    char *sf = PQgetvalue(res,0,0);
    if (sf[0] == 'f') {
        std::stringstream query1;
        query1 << "UPDATE single_passes SET pass_using = true WHERE id = "<< passes_data[choosing].id << "; \n" <<
        "UPDATE single_passes SET status_factory = true WHERE id = "<< passes_data[choosing].id << "; \n" <<
        "UPDATE single_passes SET enter_time = now() WHERE id = "<< passes_data[choosing].id << ";";
        PQexec(conn,query1.str().c_str());
    } else {
        std::stringstream query1;
        query1 << "UPDATE single_passes SET pass_using = true WHERE id = "<< passes_data[choosing].id << "; \n" <<
               "UPDATE single_passes SET status_factory = false WHERE id = "<< passes_data[choosing].id << "; \n" <<
               "UPDATE single_passes SET status_pass = false WHERE id = "<< passes_data[choosing].id << "; \n" <<
               "UPDATE single_passes SET exit_time = now() WHERE id = "<< passes_data[choosing].id << ";";
        PQexec(conn,query1.str().c_str());
    }
    single_pass_refresh();
}

void choose_passes(GtkWidget *object){
    GtkTreePath *path;
    GtkTreeViewColumn *col;
    gtk_widget_set_visible(AcceptButtonP,true);
    gtk_tree_view_get_cursor(GTK_TREE_VIEW(ViewPassesP),&path,&col);
    int* a = gtk_tree_path_get_indices(path);
    if (a != nullptr) {
        choosing = *a;
    } else {
        choosing = -1;
    }
}

void window_destroy_security(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_s = 1;
    gtk_main_quit();
}

#endif //INC_345MF_SECURITYAPP_H
