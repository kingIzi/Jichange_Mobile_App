#include "requests/authrequests.h"
#include <QUrlQuery>
#include <QtConcurrent/QtConcurrent>
#include <QSettings>
#include <QDesktopServices>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QOAuthHttpServerReplyHandler>
#include <QAbstractOAuth>
#include <QMultiMap>

//adds 2 lists as a set, then subtracts the set 1 from set 2
const QStringList AuthRequests::subtractItemInKeys(const QStringList& left, const QStringList& right) const
{
    if (left == right) { return QStringList(); }
    QSet set1(left.begin(),left.end());
    const QSet set2(right.begin(),right.end());
    set1 = set1.subtract(set2);
    return (QStringList) set1.values();
}

//saves user credentials to QSettings
void AuthRequests::saveCurrentUser(const QVariantMap &obj) const
{
    QSettings settings("Biz Logic Solutions","Jichange");
    settings.setValue(Keys::Login::check,obj.value(Keys::Login::check).toString());
    settings.setValue(Keys::Login::flogin,obj.value(Keys::Login::flogin).toString());
    settings.setValue(Keys::Login::InstID,obj.value(Keys::Login::InstID).toInt());
    settings.setValue(Keys::Login::Usno,obj.value(Keys::Login::Usno).toInt());
    settings.setValue(Keys::Login::role,obj.value(Keys::Login::role).toString());
    settings.setValue(Keys::Login::fullname,obj.value(Keys::Login::fullname).toString());
    settings.setValue(Keys::Login::Uname,obj.value(Keys::Login::Uname).toString());
    settings.setValue(Keys::Login::sessb,obj.value(Keys::Login::sessb).toString());
    settings.setValue(Keys::Login::Token,obj.value(Keys::Login::Token).toString());
}

//reads data from QSettings and stores it in map
void AuthRequests::storeCurrentUser()
{
    QSettings settings("Biz Logic Solutions","Jichange");
    this->clearCurrentUser();
    this->currentUser.insert(Keys::Login::check,settings.value(Keys::Login::check).toString());
    this->currentUser.insert(Keys::Login::flogin,settings.value(Keys::Login::flogin).toString());
    this->currentUser.insert(Keys::Login::InstID,settings.value(Keys::Login::InstID).toInt());
    this->currentUser.insert(Keys::Login::Usno,settings.value(Keys::Login::Usno).toInt());
    this->currentUser.insert(Keys::Login::role,settings.value(Keys::Login::role).toString());
    this->currentUser.insert(Keys::Login::fullname,settings.value(Keys::Login::fullname).toString());
    this->currentUser.insert(Keys::Login::Uname,settings.value(Keys::Login::Uname).toString());
    this->currentUser.insert(Keys::Login::sessb,settings.value(Keys::Login::sessb).toString());
    this->currentUser.insert(Keys::Login::Token,settings.value(Keys::Login::Token).toString());
}

QByteArray AuthRequests::loadGoogleOAuthCredentials() const
{
    try {
        if (!QFileInfo::exists(CLIENT_SECRET_CONFIGURATION)) {
            throw std::invalid_argument("Failed to find client secret json file.");
        }
        QFile file(CLIENT_SECRET_CONFIGURATION);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            const auto data = file.readAll();
            file.close();
            return data;
        }
    } catch (const std::exception& err) {
        qDebug() << err.what();
    }
    return QByteArray();
}

AuthRequests::AuthRequests(QObject *parent)
    : Requests{parent},
    currentUser(QVariantMap()),
    loggedIn(false)
{
    this->google = std::make_unique<QOAuth2AuthorizationCodeFlow>(this);
    this->google->setScope("email");
    QObject::connect(this->google.get(), &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,&QDesktopServices::openUrl);
    const auto doc = QJsonDocument::fromJson(this->loadGoogleOAuthCredentials());
    const auto object = doc.object();
    const auto settingsObject = object["web"].toObject();
    const QUrl authUri(settingsObject["auth_uri"].toString());
    const auto clientId = settingsObject["client_id"].toString();
    const QUrl tokenUri(settingsObject["token_uri"].toString());
    const auto clientSecret(settingsObject["client_secret"].toString());
    const auto redirectUris = settingsObject["redirect_uris"].toArray();
    const QUrl redirectUri(redirectUris[0].toString());
    const auto port = static_cast<quint16>(redirectUri.port());

    this->google->setAuthorizationUrl(authUri);
    this->google->setClientIdentifier(clientId);
    this->google->setAccessTokenUrl(tokenUri);
    this->google->setClientIdentifierSharedKey(clientSecret);

    this->google->setModifyParametersFunction([](QAbstractOAuth::Stage stage,QMultiMap<QString,QVariant>* parameters){
        if (stage == QAbstractOAuth::Stage::RequestingAuthorization)
        {
            parameters->insert("access_type", "offline");
            parameters->insert("prompt", "consent");
        }
        else if (stage == QAbstractOAuth::Stage::RequestingAccessToken) {
            const auto code = parameters->value("code").toByteArray();
            parameters->replace("code",QUrl::fromPercentEncoding(code));
        }
    });

    auto replyHandler = new QOAuthHttpServerReplyHandler(port, this);
    this->google->setReplyHandler(replyHandler);

    QObject::connect(this->google.get(), &QOAuth2AuthorizationCodeFlow::granted, [=](){
        qDebug() << __FUNCTION__ << __LINE__ << "Access Granted!";
        auto reply = this->google->get(QUrl("https://www.googleapis.com/plus/v1/people/me"));
        connect(reply, &QNetworkReply::finished, [reply](){
            qDebug() << "REQUEST FINISHED. Error? " << (reply->error() != QNetworkReply::NoError);
            qDebug() << reply->readAll();
            //replyHandler->deleteLater();
        });
        replyHandler->deleteLater();
    });
}

const bool AuthRequests::isLoggedIn() const
{
    return this->loggedIn;
}

const QVariantMap AuthRequests::getCurrentUser() const
{
    return this->currentUser;
}

//verifies login request was successful, if it is it stores the current user and sets isLoggedIn to true and emits login successful signal
void AuthRequests::parseLoginRequest(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        this->setIsLoggedIn(false);
        return;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.object().value("response").isObject()) {
        this->setIsLoggedIn(false);
        emit AuthRequests::loginFailed(doc.object().value("response").toString());
        return;
    }
    else {
        this->saveCurrentUser(doc.object().value("response").toObject().toVariantMap());
        this->storeCurrentUser();
        this->setIsLoggedIn(true);
        emit AuthRequests::loginSuccessfull();
    }
}

//cleans QSetting and removes current user data
void AuthRequests::clearCurrentUser()
{
    if (!this->currentUser.isEmpty()) {
        QSettings settings("Biz Logic Solutions","Jichange");
        settings.clear();
        this->currentUser = QVariantMap();
    }
}

void AuthRequests::loginUser(const QVariantMap logins)
{
    QEventLoop loop;
    const auto reply = Requests::peformPost(logins,Endpoints::Auth::AddLogin);
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    const auto future = QtConcurrent::run([reply,this](){
        while (!reply->isFinished()) {
            this->setIsWorking(true);
            QThread::sleep(1);
        }
    });
    loop.exec();
    this->setIsWorking(false);
    this->parseLoginRequest(reply);
}

void AuthRequests::signInWithGoogle()
{
    this->google->grant();
}

void AuthRequests::setIsLoggedIn(const bool isLoggedIn)
{
    if (this->loggedIn != isLoggedIn) {
        this->loggedIn = isLoggedIn;
        emit AuthRequests::isLoggedInChanged();
    }
}
