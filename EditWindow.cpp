#include "EditWindow.h"
#include "ui_EditWindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>

EditWindow::EditWindow(QWidget *parent) : QWidget(parent), ui(new Ui::EditWindow) {
    ui->setupUi(this);
    QObject::connect(ui->backButton,SIGNAL(pressed()),this,SLOT(showStatus()));
    QObject::connect(ui->editProfileButton,SIGNAL(pressed()),this,SLOT(pressedEditProfile()));
    QObject::connect(ui->selectImageButton,SIGNAL(pressed()),this,SLOT(pressedSelectImage()));
}

EditWindow::~EditWindow() {
    delete ui;
}

void EditWindow::setUsername(QString username) {
    ui->usernameLineEdit->setText(username);
}

QString EditWindow::getUsername() {
    return ui->usernameLineEdit->text();
}

void EditWindow::setCity(QString city) {
    ui->cityLineEdit->setText(city);
}

QString EditWindow::getCity() {
    return ui->cityLineEdit->text();
}

void EditWindow::setProfileImage(QImage profileImage) {
    ui->profileLabel->setPixmap(QPixmap::fromImage(profileImage));
}

QImage EditWindow::getProfileImage() {
    return ui->profileLabel->pixmap()->toImage();
}

void EditWindow::showStatus(){
    emit moveToStatus();
}

void EditWindow::pressedEditProfile() {
    emit doEditProfile();
}

void EditWindow::pressedSelectImage() {
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir Imagen"),"C:/",tr("Image PNG (*.png)"));
    /* Si el usuario pulsa Cancelar NO hay que cambiar ni subir la imagen */
    if (QString::compare(fileName, "", Qt::CaseInsensitive)!=0) {
        QPixmap image (fileName);
        ui->profileLabel->setPixmap(image);
        emit doUploadImage(fileName);
    }
}
