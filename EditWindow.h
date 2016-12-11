#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>

namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = 0);
    ~EditWindow();
    void setUsername(QString);
    QString getUsername();
    void setCity(QString);
    QString getCity();
    void setProfileImage(QImage);
    QImage getProfileImage();

private:
    Ui::EditWindow *ui;

private slots:
    void showStatus();
    void pressedEditProfile();
    void pressedSelectImage();

signals:
    void moveToStatus();
    void doEditProfile();
    void doUploadImage(QString);
};

#endif // EDITWINDOW_H
