#pragma once

#include <QOAuth2AuthorizationCodeFlow>
#include <QByteArray>
#include "requests.h"

namespace Endpoints {
static constexpr const char* BaseUrl = "http://192.168.100.50:98";
struct Auth {
    static constexpr const char* AddLogin = "/api/LoginUser/AddLogins";
};
};

namespace Keys {
struct Login {
    static constexpr const char* check = "check";
    static constexpr const char* flogin = "flogin";
    static constexpr const char* InstID = "InstID";
    static constexpr const char* Usno = "Usno";
    static constexpr const char* role = "role";
    static constexpr const char* fullname = "fullname";
    static constexpr const char* Uname = "Uname";
    static constexpr const char* sessb = "sessb";
    static constexpr const char* Token = "Token";
};
};

class AuthRequests : public Requests
{
    Q_OBJECT
    Q_PROPERTY(bool isLoggedIn READ isLoggedIn WRITE setIsLoggedIn NOTIFY isLoggedInChanged FINAL)
//    Q_PROPERTY(bool isWorking READ isWorking WRITE setIsWorking NOTIFY isWorkingChanged)
private:
    std::unique_ptr<QOAuth2AuthorizationCodeFlow> google = nullptr;
    QVariantMap currentUser;
    bool loggedIn;
    //bool working;
private:
    const QStringList subtractItemInKeys(const QStringList& left,const QStringList& right) const;
private:
    //void parseRequestError(const QNetworkReply::NetworkError& error);
    void saveCurrentUser(const QVariantMap& obj) const;
    void storeCurrentUser();
    void changeUser();
    QByteArray loadGoogleOAuthCredentials() const;
public:
    explicit AuthRequests(QObject *parent = nullptr);
    const bool isLoggedIn() const;
    //const bool isWorking() const;
    Q_INVOKABLE const QVariantMap getCurrentUser() const;
public:
    //QNetworkReply* makeRequest(const QVariantMap& logins,const QString& path,const QList<QPair<QString,QString>> params = {},const QString baseUrl = "");
    void parseLoginRequest(QNetworkReply * reply);
    void clearCurrentUser();
public:
    Q_INVOKABLE void loginUser(const QVariantMap logins);
    Q_INVOKABLE void signInWithGoogle();
public slots:
    void setIsLoggedIn(const bool isLoggedIn);
    //void setIsWorking(const bool working);
signals:
    void isLoggedInChanged();
    void loginFailed(const QString);
    void loginSuccessfull();
    void signInWithGoogleUrl(const QUrl);
    void signInWithGoogleFailed();
    void signInWithGoogleSuccess();
    //void isWorkingChanged();
};

