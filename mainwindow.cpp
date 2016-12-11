#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QDesktopWidget>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Init Status Bar

    ui->statusBar->showMessage("Comprobando conexion con la API...");

    // Init Windows

    this->stackedWidget = new QStackedWidget();

    this->loginWindowUi = new Ui::LoginWindow;
    stackedWidget->addWidget(new LoginWindow);

    this->registerWindowUi = new Ui::RegisterWindow;
    stackedWidget->addWidget(new RegisterWindow);

    this->statusWindowUi = new Ui::StatusWindow;
    stackedWidget->addWidget(new StatusWindow);

    this->editWindowUi = new Ui::EditWindow;
    stackedWidget->addWidget(new EditWindow);

    this->userWindowUi = new Ui::UserWindow;
    stackedWidget->addWidget(new UserWindow);

    // Init API

    this->api = new APIHandler();

    // Signals

    QObject::connect(this->api,SIGNAL(doneCheck(QJsonObject)),this,SLOT(responseCheck(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(0),SIGNAL(moveToRegister()),this,SLOT(moveToRegister()));
    QObject::connect(this->stackedWidget->widget(0),SIGNAL(doLogin(QString, QString)),this,SLOT(doLogin(QString, QString)));
    QObject::connect(this->api,SIGNAL(doneLogin(QJsonObject)),this,SLOT(responseLogin(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(1),SIGNAL(moveToLogin()),this,SLOT(moveToLogin()));
    QObject::connect(this->stackedWidget->widget(1),SIGNAL(doRegister(QString, QString, QString, QString)),this,SLOT(doRegister(QString, QString, QString, QString)));
    QObject::connect(this->api,SIGNAL(doneRegister(QJsonObject)),this,SLOT(responseRegister(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(2),SIGNAL(closeSession()),this,SLOT(closeSession()));
    QObject::connect(this->api,SIGNAL(doneLogout(QJsonObject)),this,SLOT(responseLogout(QJsonObject)));

    QObject::connect(this->api,SIGNAL(doneError(QJsonObject)),this,SLOT(responseError(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(2),SIGNAL(doPublish(QString)),this,SLOT(doPublish(QString)));
    QObject::connect(this->api, SIGNAL(donePublish(QJsonObject)), this, SLOT(responsePublish(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(2),SIGNAL(doStatus()),this,SLOT(doStatus()));
    QObject::connect(this->api, SIGNAL(doneStatus(QJsonObject)), this, SLOT(responseStatus(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(2),SIGNAL(moveToEdit()),this,SLOT(moveToEdit()));
    QObject::connect(this->stackedWidget->widget(3),SIGNAL(moveToStatus()),this,SLOT(moveToStatus()));
    QObject::connect(this->stackedWidget->widget(3),SIGNAL(doEditProfile()),this,SLOT(doEditProfile()));
    QObject::connect(this->stackedWidget->widget(3),SIGNAL(doUploadImage(QString)),this,SLOT(doUploadImage(QString)));
    QObject::connect(this->api, SIGNAL(doneEditProfile(QJsonObject)), this, SLOT(responseEditProfile(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(2),SIGNAL(showProfile(int)),this,SLOT(doProfile(int)));
    QObject::connect(this->api, SIGNAL(doneGetUser(QJsonObject)), this, SLOT(responseGetUser(QJsonObject)));

    QObject::connect(this->stackedWidget->widget(4), SIGNAL(moveToStatus()), this, SLOT(moveToStatus()));

    // Set all Widgets

    this->setCentralWidget(this->stackedWidget);
    this->stackedWidget->setCurrentIndex(0);
    this->adjustSize();

    // Load stored data

    QSettings settings("RedSocial", "GPI");
    qobject_cast<LoginWindow *>(this->stackedWidget->widget(0))->drawData(settings.value("user").toString(), settings.value("passwd").toString());
}

MainWindow::~MainWindow()
{
    this->closeSession();
    delete ui;
}

//------------------------------------------------------------------------------
//  Change Window Widget
//------------------------------------------------------------------------------

void MainWindow::moveToLogin(){
    this->stackedWidget->setCurrentIndex(0);
    this->adjustWindowSize();
}

void MainWindow::moveToRegister(){
    this->stackedWidget->setCurrentIndex(1);
    this->adjustWindowSize();
}

void MainWindow::moveToStatus(){
    this->stackedWidget->setCurrentIndex(2);
    this->adjustWindowSize();

    qobject_cast<StatusWindow *>(this->stackedWidget->widget(2))->loadProfile(this->api);
}

void MainWindow::moveToEdit(){
    qobject_cast<EditWindow *>(this->stackedWidget->widget(3))->setUsername(this->api->getUsername());
    qobject_cast<EditWindow *>(this->stackedWidget->widget(3))->setCity(this->api->getCity());
    qobject_cast<EditWindow *>(this->stackedWidget->widget(3))->setProfileImage(this->api->getImage());

    this->stackedWidget->setCurrentIndex(3);
    this->adjustWindowSize();
}

void MainWindow::moveToProfile() {
    this->stackedWidget->setCurrentIndex(4);
    this->adjustWindowSize();
}

void MainWindow::closeSession(){
    this->api->doLogout();
}

//------------------------------------------------------------------------------
//  API Calls
//------------------------------------------------------------------------------

void MainWindow::doLogin(QString user, QString passwd){
    this->api->doLogin(user, passwd);
}

void MainWindow::doRegister(QString user, QString passwd1, QString passwd2, QString email){
    if (passwd1 == passwd2) {
        this->api->doRegister(user, passwd1, email);
    }
    else {
        ui->statusBar->showMessage("Las contraseñas no coinciden", 3000);
    }
}

void MainWindow::doPublish(QString message){
    this->api->doPublish(message);
}

void MainWindow::doStatus() {
    this->api->doStatus();
}

void MainWindow::doEditProfile() {
    QString username = qobject_cast<EditWindow *>(this->stackedWidget->widget(3))->getUsername();
    QString city = qobject_cast<EditWindow *>(this->stackedWidget->widget(3))->getCity();

    this->api->doEditProfile(username, city);
}

void MainWindow::doUploadImage(QString profileImage) {
    ui->statusBar->showMessage("Cargando imagen...");
    this->api->doUploadImage(profileImage);
}

void MainWindow::doProfile(int userID) {
    this->moveToProfile();
    this->api->doGetUser(userID);
    ui->statusBar->showMessage("Cargando perfil...");
}

//------------------------------------------------------------------------------
//  API Responses
//------------------------------------------------------------------------------

void MainWindow::responseCheck(QJsonObject json) {
    if (json["status"].toInt() == 1) {
        this->api->setLogo(json["return"].toString());
        qobject_cast<LoginWindow *>(this->stackedWidget->widget(0))->setLogo(this->api->getLogo());
        ui->statusBar->showMessage("Conexion exitosa", 3000);
    }
    else {
        ui->statusBar->showMessage("Error de Conexion");
    }
}

void MainWindow::responseLogin(QJsonObject json) {
    if (json["status"].toInt() == 1) {
        this->api->setSession(json["return"].toObject());
        ui->statusBar->showMessage("Login autorizado", 3000);

        // Save login data

        QSettings settings("RedSocial", "GPI");
        settings.setValue("user", qobject_cast<LoginWindow *>(this->stackedWidget->widget(0))->getUser());
        settings.setValue("passwd", qobject_cast<LoginWindow *>(this->stackedWidget->widget(0))->getPasswd());

        this->moveToStatus();
    }
    else {
        ui->statusBar->showMessage("Login incorrecto");
    }
}

void MainWindow::responseRegister(QJsonObject json) {
    if (json["status"].toInt() == 1) {
        ui->statusBar->showMessage("Registro completado", 3000);
    }
    else {
        if (json["code"].toString() == "no-email-valid") {
            ui->statusBar->showMessage("Registro fallido: email no valido");
        }
        else if (json["code"].toString() == "no-user-minlen") {
            ui->statusBar->showMessage("Registro fallido: usuario muy corto");
        }
        else if (json["code"].toString() == "no-passwd-minlen") {
            ui->statusBar->showMessage("Registro fallido: contraseña muy corta");
        }
        else if (json["code"].toString() == "no-create-user") {
            ui->statusBar->showMessage("Registro fallido: user or mail existent");
        }
        else {
            ui->statusBar->showMessage("Registro fallido: error desconocido");
        }
    }
}

void MainWindow::responseLogout(QJsonObject json) {
    if (json["status"].toInt() == 1) {
        this->api->destroySession();
        ui->statusBar->showMessage("Sesion cerrada", 3000);
    }
    else {
        ui->statusBar->showMessage("Error al cerrar sesion", 3000);
    }
    this->moveToLogin();
}

void MainWindow::responsePublish(QJsonObject json){
    if (json["status"].toInt() == 1) {
        ui->statusBar->showMessage("Mensaje Publicado", 3000);
        this->doStatus();
    }
    else {
        if (json["code"].toString() == "no-session") {
            ui->statusBar->showMessage("Publicacion fallida: Sesion invalida");
            this->moveToLogin();
        }
        else if (json["code"].toString() == "no-body-minlen") {
            ui->statusBar->showMessage("Publicacion fallida: Mensaje vacio");
        }
        else {
            ui->statusBar->showMessage("Publicacion fallida: error de conexion");
        }
    }
}

void MainWindow::responseStatus(QJsonObject json){
    if (json["status"].toInt() == 1) {
        qobject_cast<StatusWindow *>(this->stackedWidget->widget(2))->drawMessages(json["return"].toArray());
        ui->statusBar->showMessage("Actualizado", 3000);
    }
    else {
        ui->statusBar->showMessage("Error al actualizar");
    }
}

void MainWindow::responseEditProfile(QJsonObject json){
    if (json["status"].toInt() == 1) {
        ui->statusBar->showMessage("Perfil editado", 3000);
    }
    else {
        ui->statusBar->showMessage("Error al actualizar");
    }
}

void MainWindow::responseGetUser(QJsonObject json){
    if (json["status"].toInt() == 1){
        QJsonObject user = json["return"].toObject();
        ui->statusBar->showMessage("Perfil cargado", 3000);
        qobject_cast<UserWindow *>(this->stackedWidget->widget(4))->setUsername(user["username"].toString());
        qobject_cast<UserWindow *>(this->stackedWidget->widget(4))->setCity(user["city"].toString());
        qobject_cast<UserWindow *>(this->stackedWidget->widget(4))->setEmail(user["email"].toString());
        qobject_cast<UserWindow *>(this->stackedWidget->widget(4))->setProfileImage(user["image"].toString());
    }
    else{
        ui->statusBar->showMessage("Error al obtener el usuario");
    }
}

void MainWindow::responseError(QJsonObject json) {
    ui->statusBar->showMessage("Error inesperado");
    qDebug() << json;
}

//------------------------------------------------------------------------------
//  Window Operations
//------------------------------------------------------------------------------

void MainWindow::adjustWindowSize() {
    QSize windowSize = this->stackedWidget->currentWidget()->minimumSize();
    windowSize.setHeight(this->stackedWidget->currentWidget()->minimumHeight() + 20);
    this->setMinimumSize(windowSize);
    this->setMaximumSize(windowSize);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

