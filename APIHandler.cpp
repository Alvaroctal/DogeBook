#include "APIHandler.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>
#include <QFile>

APIHandler::APIHandler()
{
    this->baseURL = "http://labs.octal.es/gpi/";
    this->manager = new QNetworkAccessManager(this);
    connect(this->manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReply(QNetworkReply*)));

    this->doCheck();
}

void APIHandler::setLogo(QString base64Image) {
    QByteArray imageArray (base64Image.toStdString().c_str());

    this->logo.loadFromData(QByteArray::fromBase64(imageArray));
}

QImage APIHandler::getLogo() {
    return this->logo;
}

int APIHandler::getUserID() {
    return this->session["id"].toInt();
}

QString APIHandler::getUsername() {
    return this->session["username"].toString();
}

QString APIHandler::getEmail() {
    return this->session["email"].toString();
}

QImage APIHandler::getImage() {
    QImage image;
    QByteArray imageArray (this->session["image"].toString().toStdString().c_str());
    image.loadFromData(QByteArray::fromBase64(imageArray));
    return image;
}

void APIHandler::setImage(QString base64Image) {
    this->session["image"].toObject().value(base64Image);
}

QString APIHandler::getSession() {
    return this->session["session"].toString();
}


QString APIHandler::getCity() {
    return this->session["city"].toString();
}

void APIHandler::setSession(QJsonObject json) {
    this->session = json;
}

void APIHandler::destroySession() {

}

//------------------------------------------------------------------------------
//  API Methods
//------------------------------------------------------------------------------

void APIHandler::doCheck() {
    this->get(this->baseURL);
}

void APIHandler::doLogin(QString user, QString passwd) {
    QUrlQuery postData;
    postData.addQueryItem("user", user);
    postData.addQueryItem("passwd", passwd);

    this->post(this->baseURL + "login/", postData);
}

void APIHandler::doRegister(QString user, QString passwd, QString email) {
    QUrlQuery postData;
    postData.addQueryItem("user", user);
    postData.addQueryItem("passwd", passwd);
    postData.addQueryItem("email", email);

    this->post(this->baseURL + "create/user/", postData);
}

void APIHandler::doLogout() {
    QUrlQuery postData;
    postData.addQueryItem("userID", QString::number(this->getUserID()));
    postData.addQueryItem("session", this->getSession());

    this->post(this->baseURL + "logout/", postData);
}

void APIHandler::doPublish(QString message){
    QUrlQuery postData;
    postData.addQueryItem("userID", QString::number(this->getUserID()));
    postData.addQueryItem("session", this->getSession());
    postData.addQueryItem("body", message);

    this->post(this->baseURL + "create/message/", postData);
}

void APIHandler::doStatus() {
    this->get(this->baseURL + "get/status/");
}

void APIHandler::doEditProfile(QString username, QString city) {
    QUrlQuery postData;
    postData.addQueryItem("userID", QString::number(this->getUserID()));
    postData.addQueryItem("session", this->getSession());
    postData.addQueryItem("username", username);
    postData.addQueryItem("city", city);

    this->post(this->baseURL + "edit/user/", postData);
}

void APIHandler::doUploadImage(QString imagePath) {
    QFile* file = new QFile(imagePath);
    file->open(QIODevice::ReadOnly);

    QUrlQuery postData;
    postData.addQueryItem("userID", QString::number(this->getUserID()));
    postData.addQueryItem("session", this->getSession());
    postData.addQueryItem("image", QString(file->readAll().toBase64()));

    this->post(baseURL + "edit/user/image/", postData);
}

void APIHandler::doGetUser(int UserID){
    this->get(this->baseURL + "get/user/" + QString::number(UserID) + "/");
}
//------------------------------------------------------------------------------
//  API Calls
//------------------------------------------------------------------------------

void APIHandler::get(QString url) {
    this->manager->get(QNetworkRequest(QUrl(url)));
}

void APIHandler::post(QString url, QUrlQuery postData) {
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    this->manager->post(request,postData.toString(QUrl::FullyEncoded).toUtf8());
}

//------------------------------------------------------------------------------
//  API Response
//------------------------------------------------------------------------------

void APIHandler::onReply(QNetworkReply* reply)
{
    QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll());
    QJsonObject json = jsonDocument.object();

    if (json["action"].toString() == "check") { emit doneCheck(json); }
    else if (json["action"].toString() == "login") { emit doneLogin(json); }
    else if (json["action"].toString() == "createUser") { emit doneRegister(json); }
    else if (json["action"].toString() == "logout") { emit doneLogout(json); }
    else if (json["action"].toString() == "createMessage") { emit donePublish(json); }
    else if (json["action"].toString() == "status") { emit doneStatus(json); }
    else if (json["action"].toString() == "editUser") { emit doneEditProfile(json); }
    else if (json["action"].toString() == "getUser") { emit doneGetUser(json); }
    else { emit doneError(json); }
}

