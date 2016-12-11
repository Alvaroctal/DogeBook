#include "RegisterWindow.h"
#include "ui_RegisterWindow.h"

RegisterWindow::RegisterWindow(QWidget *parent) : QWidget(parent), ui(new Ui::RegisterWindow)
{
    ui->setupUi(this);
    ui->pass1LineEdit->setEchoMode(QLineEdit::Password);
    ui->pass2LineEdit->setEchoMode(QLineEdit::Password);
    QObject::connect(ui->backButton,SIGNAL(pressed()),this,SLOT(showLogin()));
    QObject::connect(ui->registerButton,SIGNAL(pressed()),this,SLOT(pressedRegister()));
    /* Para que al pulsar ENTER haga login */
    QObject::connect(ui->userLineEdit,SIGNAL(returnPressed()),this,SLOT(pressedRegister()));
    QObject::connect(ui->emailLineEdit,SIGNAL(returnPressed()),this,SLOT(pressedRegister()));
    QObject::connect(ui->pass1LineEdit,SIGNAL(returnPressed()),this,SLOT(pressedRegister()));
    QObject::connect(ui->pass2LineEdit,SIGNAL(returnPressed()),this,SLOT(pressedRegister()));
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::showLogin() {
    emit moveToLogin();
}

void RegisterWindow::pressedRegister() {
    emit doRegister(ui->userLineEdit->text(), ui->pass1LineEdit->text(), ui->pass2LineEdit->text(), ui->emailLineEdit->text());
}
