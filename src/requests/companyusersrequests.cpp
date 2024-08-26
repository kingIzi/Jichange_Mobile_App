#include "requests/companyusersrequests.h"
#include <QFuture>
#include <QFutureWatcher>

void CompanyUsersRequests::parseCheckAccount(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        return;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    const auto exists = doc.object().value("response").toBool();
    emit CompanyUsersRequests::checkAccountExists(exists);
}

void CompanyUsersRequests::parseAddCompanyL(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        return;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.object().value("response").isBool() && doc.object().value("response").toBool()) {
        emit CompanyUsersRequests::addCompanyLFailed(QObject::tr("This Company already exists"));
    }
    else {
        const auto insertedId = static_cast<long long>(doc.object().value("response").toInt());
        emit CompanyUsersRequests::addCompanyLResponse(insertedId);
    }
}

void CompanyUsersRequests::parseCompanyUsersList(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        return;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.object().value(BaseKeys::response).isArray()) {
        emit CompanyUsersRequests::companyUsersList(doc.object().value(BaseKeys::response).toArray());
    }
    else {
        emit CompanyUsersRequests::companyUsersList(QJsonArray());
    }
}

CompanyUsersRequests::CompanyUsersRequests(Requests *parent)
    : Requests{parent}
{

}

void CompanyUsersRequests::requestCompanyUsersList(const QVariantMap &body)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> future = QtConcurrent::run([body,this](){
        return Requests::requestPostReply(body,Endpoints::companyUsersList);
    }).then([this](QNetworkReply* reply){
        this->parseCompanyUsersList(reply);
    });
    watcher.setFuture(future);
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    loop.exec();
    this->setIsWorking(false);
}

void CompanyUsersRequests::requestCheckAccount(const QVariantMap &body)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> future = QtConcurrent::run([body,this](){
        return Requests::requestPostReply(body,Endpoints::checkAccount);
    }).then([this](QNetworkReply* reply){
        this->parseCheckAccount(reply);
    });
    watcher.setFuture(future);
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    loop.exec();
    this->setIsWorking(false);
}

void CompanyUsersRequests::requestAddCompanyL(const QVariantMap &body)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> future = QtConcurrent::run([body,this] () {
        const auto payload = (QVariantMap) {std::make_pair("acc",body.value("accno").toString())};
        return Requests::requestPostReply(payload,Endpoints::checkAccount);
    }).then([this](QNetworkReply* reply){
        const auto doc = QJsonDocument::fromJson(reply->readAll());
        return doc.object().value("response").toBool();
    }).then([this,body](const bool exists){
        if (exists) {
            emit CompanyUsersRequests::addCompanyLFailed(QObject::tr("the account number you have entered is already in use"));
        }
        else {
            const auto reply = Requests::requestPostReply(body,Endpoints::addCompanyL);
            this->parseAddCompanyL(reply);
        }
    });
    watcher.setFuture(future);
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    loop.exec();
    this->setIsWorking(false);
}
