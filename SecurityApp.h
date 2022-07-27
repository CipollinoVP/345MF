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

//Выводимые данные о сотруднике
std::vector<std::string> personal_data_s;

//Флаг завершения работы программы 
int finish_program_s = 0;

//Проверка на QR-код
void QR_Scan(int& param, std::string& password);

//Авторизация сотрудника при обнаружении QR-кода
std::string auhtorizate_appear(int& err, std::string const& password_worker, std::vector<std::string>& worker_data);

//Функция таймерв: установка периодичности проверки QR-кода
gboolean TimerFunc(gpointer data);

extern "C" void window_destroy_security(GtkWidget *object);

static void create_window_checkpoint();

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
        std::string journal = gtk_label_get_text(GTK_LABEL(JournalTextM));
        journal.append(result_report);
        gtk_label_set_text(GTK_LABEL(JournalTextM),journal.c_str());
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
    GError* error = NULL;

    builder = gtk_builder_new();
    if(!gtk_builder_add_from_file(builder, "./CheckpointApp.glade", &error)){
        g_critical("Не могу загрузить файл: %s", error->message);
        g_error_free(error);
    }

    gtk_builder_connect_signals(builder, NULL);

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
            std::stringstream command;
            command << "SELECT status FROM workers WHERE id = ";
            command << num;
            command << ";";
            std::string command_s = command.str();
            PGresult *res_id = PQexec(conn, command_s.c_str());
            if (res_id == NULL) {
                err = ERR_PASS;
                return "Ошибка: неверный номер пропуска\n";
            } else {
                char* n_s = PQgetvalue(res_id,0,0);
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
                    std::stringstream command7;
                    command7 << "SELECT avatar FROM workers WHERE id = ";
                    command7 << num;
                    command7 << ";";
                    std::string command_s7 = command7.str();
                    PGresult *rs_avatar = PQexec(conn, command_s7.c_str());
                    char* avatar_s = PQgetvalue(rs_avatar,0,0);
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
                    std::stringstream command7;
                    command7 << "SELECT avatar FROM workers WHERE id = ";
                    command7 << num;
                    command7 << ";";
                    std::string command_s7 = command7.str();
                    PGresult *rs_avatar = PQexec(conn, command_s7.c_str());
                    char* avatar_s = PQgetvalue(rs_avatar,0,0);
                    std::ofstream jp("ava.jpg",std::ios::binary);
                    jp << std::string(avatar_s);
                    jp.close();
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
    }
}

int checkpoint_unit(int argc, char *argv[]){
    gtk_init(&argc, &argv);
    create_window_checkpoint();
    gtk_widget_show(windowM);
    g_timeout_add(2000,TimerFunc,(gpointer) windowM);
    /* передаём управление GTK+ */
    gtk_main ();
    return 0;
}

void window_destroy_security(GtkWidget *object)
{
    // завершаем главный цикл приложения
    finish_program_s = 1;
    gtk_main_quit();
}

#endif //INC_345MF_SECURITYAPP_H
