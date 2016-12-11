#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "RegisterWindow.h"
#include <QByteArray>
#include <QImage>
#include <QString>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->passwdLineEdit->setEchoMode(QLineEdit::Password);
    QObject::connect(ui->registerButton,SIGNAL(pressed()),this,SLOT(showRegister()));
    QObject::connect(ui->loginButton,SIGNAL(pressed()),this,SLOT(pressedLogin()));
    /* Para que al pulsar ENTER haga login */
    QObject::connect(ui->userLineEdit,SIGNAL(returnPressed()),this,SLOT(pressedLogin()));
    QObject::connect(ui->passwdLineEdit,SIGNAL(returnPressed()),this,SLOT(pressedLogin()));

}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::drawData(QString user, QString passwd) {
    this->ui->userLineEdit->setText(user);

    if (passwd.size() != 0) {
        this->ui->passwdLineEdit->setText(passwd);
        this->ui->remmemberCheckBox->setChecked(true);
    }
}

void LoginWindow::setLogo(QImage image) {
    ui->logoLabel->setPixmap(QPixmap::fromImage(image));
}

QString LoginWindow::getUser() {
    return this->ui->userLineEdit->text();
}

QString LoginWindow::getPasswd() {
    return (this->ui->remmemberCheckBox->isChecked() ? this->ui->passwdLineEdit->text() : "");
}

void LoginWindow::showRegister(){
    emit moveToRegister();
}
void LoginWindow::pressedLogin(){
    emit doLogin(ui->userLineEdit->text(), ui->passwdLineEdit->text());
}
