#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>

namespace Ui {
class RegisterWindow;
}

class RegisterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();

private:
    Ui::RegisterWindow *ui;

private slots:
    void showLogin();
    void pressedRegister();

signals:
    void moveToLogin();
    void doRegister(QString, QString, QString, QString);
};

#endif // REGISTERWINDOW_H
