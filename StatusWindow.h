#ifndef STATUSWINDOW_H
#define STATUSWINDOW_H

#include <QWidget>
#include "APIHandler.h"
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
    class StatusWindow;
}

class StatusWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatusWindow(QWidget *parent = 0);
    ~StatusWindow();

    void loadProfile(APIHandler *api);
    void drawMessages(QJsonArray messages);
    void drawMessage(QJsonObject message);

private:
    Ui::StatusWindow *ui;
    QHash<int, int> messageUserIdList;

private slots:
    void showLogin();
    void publishMessage();
    void pressStatus();
    void showEdit();
    void pressedProfile();

signals:
    void closeSession();
    void doPublish(QString);
    void doStatus();
    void moveToEdit();
    void showProfile(int);
};

#endif // STATUSWINDOW_H
