#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"
#include "StatusWindow.h"
#include "ui_StatusWindow.h"
#include "EditWindow.h"
#include "ui_EditWindow.h"
#include "UserWindow.h"
#include "ui_UserWindow.h"
#include <QStackedWidget>
#include "APIHandler.h"
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Ui::LoginWindow *loginWindowUi;
    Ui::RegisterWindow *registerWindowUi;
    Ui::StatusWindow *statusWindowUi;
    Ui::EditWindow *editWindowUi;
    Ui::UserWindow *userWindowUi;

    QStackedWidget *stackedWidget;

    APIHandler *api;

    void adjustWindowSize();

private slots:
    void moveToLogin();
    void moveToRegister();
    void moveToStatus();
    void moveToEdit();
    void moveToProfile();
    void closeSession();

    void doLogin(QString user, QString passwd);
    void doRegister(QString user, QString passwd1, QString passwd2, QString email);
    void doPublish(QString message);
    void doEditProfile();
    void doUploadImage(QString profileImage);
    void doProfile(int);
    void doStatus();

    void responseCheck(QJsonObject json);
    void responseLogin(QJsonObject json);
    void responseRegister(QJsonObject json);
    void responseLogout(QJsonObject json);
    void responsePublish(QJsonObject json);
    void responseStatus(QJsonObject json);
    void responseEditProfile(QJsonObject json);
    void responseGetUser(QJsonObject json);
    void responseError(QJsonObject json);
};
#endif // MAINWINDOW_H
