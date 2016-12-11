#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <QString>
#include <QObject>
#include <QtNetwork/QNetworkReply>
#include <QJsonObject>
#include <QUrlQuery>
#include <QJsonObject>
#include <QImage>

class APIHandler : public QObject
{
    Q_OBJECT

public:
    APIHandler();

    void setLogo(QString);
    QImage logo;
    QImage getLogo();

    int getUserID();
    QString getUsername();
    QString getCity();
    QString getEmail();
    QImage getImage();
    void setImage(QString);
    QString getSession();
    void setSession(QJsonObject);
    void destroySession();

    void doCheck();
    void doLogin(QString, QString);
    void doRegister(QString, QString, QString);
    void doLogout();
    void doPublish(QString);
    void doStatus();
    void doEditProfile(QString, QString);
    void doUploadImage(QString);
    void doGetUser(int);

private:
    QString baseURL;
    QJsonObject session;

    QNetworkAccessManager *manager;

    void get(QString);
    void post(QString, QUrlQuery);

public slots:
    void onReply(QNetworkReply *reply);

signals:
    void doneCheck(QJsonObject json);
    void doneLogin(QJsonObject json);
    void doneRegister(QJsonObject json);
    void doneLogout(QJsonObject json);
    void doneError(QJsonObject json);
    void donePublish(QJsonObject json);
    void doneStatus(QJsonObject json);
    void doneEditProfile(QJsonObject json);
    void doneGetUser(QJsonObject json);

};

#endif // APIHANDLER_H
