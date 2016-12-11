#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QString>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void drawData(QString, QString);
    QString getUser();
    QString getPasswd();
    void setLogo(QImage);

private:
    Ui::LoginWindow *ui;

private slots:
    void showRegister();
    void pressedLogin();

signals:
    void moveToRegister();
    void doLogin(QString, QString);
};

#endif // LOGINWINDOW_H
