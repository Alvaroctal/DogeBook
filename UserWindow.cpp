#include "UserWindow.h"
#include "ui_UserWindow.h"

UserWindow::UserWindow(QWidget *parent) : QWidget(parent), ui(new Ui::UserWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->backButton,SIGNAL(pressed()),this,SLOT(showStatus()));
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::setUsername(QString username)
{
    ui->usernameLabel->setText(username);
}

void UserWindow::setCity(QString city)
{
    ui->cityLabel->setText(city);
}

void UserWindow::setEmail(QString email)
{
    ui->emailLabel->setText(email);
}

void UserWindow::setProfileImage(QString base64Image)
{
    QImage profileImage;
    QByteArray imageArray (base64Image.toStdString().c_str());
    profileImage.loadFromData(QByteArray::fromBase64(imageArray), "PNG");
    ui->profileLabel->setPixmap(QPixmap::fromImage(profileImage));
}

void UserWindow::showStatus(){
    emit moveToStatus();
}
