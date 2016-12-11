#include "StatusWindow.h"
#include "ui_StatusWindow.h"
#include "APIHandler.h"

StatusWindow::StatusWindow(QWidget *parent) : QWidget(parent), ui(new Ui::StatusWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->closeButton,SIGNAL(pressed()),this,SLOT(showLogin()));
    QObject::connect(ui->publishButton,SIGNAL(pressed()),this,SLOT(publishMessage()));
    QObject::connect(ui->refreshButton,SIGNAL(pressed()),this,SLOT(pressStatus()));
    QObject::connect(ui->editButton,SIGNAL(pressed()),this,SLOT(showEdit()));
    QObject::connect(ui->messagesListWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(pressedProfile()));
}

StatusWindow::~StatusWindow()
{
    delete this->ui;
}

void StatusWindow::loadProfile(APIHandler *api) {

    this->ui->userLabel->setText(api->getUsername());
    this->ui->imageLabel->setPixmap(QPixmap::fromImage(api->getImage()));

    emit doStatus();
}

void StatusWindow::drawMessages(QJsonArray messages) {
    this->ui->messagesListWidget->clear();
    int messagesCount = messages.count();
    for (int i = 0; i < messagesCount; i++) {
        this->drawMessage(messages.at(i).toObject());
    }
}

void StatusWindow::drawMessage(QJsonObject message) {
    QString item = QString(message["username"].toString() + ":" + "\n" + message["body"].toString() + "\n---------------------------- " + message["time"].toString() + "\n");
    this->ui->messagesListWidget->addItem(item);
    // Con esto podemos saber que userID tiene cada mensaje
    int ix = ui->messagesListWidget->count() - 1;
    messageUserIdList.insert(ix, message["userID"].toInt());
}

void StatusWindow::publishMessage(){
    emit doPublish(ui->messageText->toPlainText());
    ui->messageText->setPlainText("");
}

void StatusWindow::showLogin() {
    emit closeSession();
}

void StatusWindow::pressStatus() {
    emit doStatus();
}

void StatusWindow::showEdit() {
    emit moveToEdit();
}

void StatusWindow::pressedProfile() {
    emit showProfile(messageUserIdList.value(ui->messagesListWidget->currentIndex().row()));
}
