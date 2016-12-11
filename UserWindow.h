#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>

namespace Ui {
class UserWindow;
}

class UserWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = 0);
    ~UserWindow();
    void setUsername(QString);
    void setCity(QString);
    void setEmail(QString);
    void setProfileImage(QString);

private:
    Ui::UserWindow *ui;

private slots:
    void showStatus();

signals:
    void moveToStatus();

};

#endif // USERWINDOW_H
