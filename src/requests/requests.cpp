#include "requests/requests.h"
#include <QEventLoop>
#include <QUrl>
#include <QUrlQuery>

void Requests::appendUrlQueryItems(QUrl &url, const QList<QPair<QString, QString> > &params) const
{
    if (!params.isEmpty()){
        QUrlQuery query;
        query.setQueryItems(params);
        url.setQuery(query);
    }
}

Requests::Requests(QObject *parent) :
    QObject{parent},
    manager(std::make_unique<QNetworkAccessManager>(this)),
    working(false)
{
}

//determines the base url, sets the path and query params of the url and peforms the post requests with the payload
QNetworkReply* Requests::peformPost(const QVariantMap& body,const QString& path,const QList<QPair<QString,QString>> params,const QString baseUrl)
{
    const auto rootPath = baseUrl.isEmpty() ? Requests::BaseUrl : baseUrl;
    QUrl url(rootPath);
    url.setPath(path);
    this->appendUrlQueryItems(url,params);
    auto request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    const auto doc = QJsonDocument::fromVariant(body);
    this->manager->setTransferTimeout(60000);
    return this->manager->post(request,doc.toJson());
}

QNetworkReply *Requests::peformGet(const QString &path, const QList<QPair<QString, QString> > params,const QString baseUrl)
{
    const auto rootPath = baseUrl.isEmpty() ? Requests::BaseUrl : baseUrl;
    QUrl url(rootPath);
    url.setPath(path);
    this->appendUrlQueryItems(url,params);
    auto request = QNetworkRequest(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    this->manager->setTransferTimeout(60000);
    return this->manager->get(request);
}

QNetworkReply* Requests::requestPostReply(const QVariantMap &body, const QString &path)
{
    QEventLoop loop;
    const auto reply = Requests::peformPost(body,path);
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    return reply;
}

QNetworkReply *Requests::requestGetReply(const QString &path,const QList<QPair<QString,QString>> params)
{
    QEventLoop loop;
    const auto reply = Requests::peformGet(path);
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    return reply;
}

//verifies if the network reply contains any error
void Requests::parseRequestError(const QNetworkReply::NetworkError &error)
{
    switch (error) {
    case QNetworkReply::TimeoutError:
        emit Requests::timeoutError(QObject::tr("Request timed out. Please verify your connection or try again."));
        break;
    case QNetworkReply::ConnectionRefusedError:
        emit Requests::connectionRefusedError(QObject::tr("Please, verify your connection or try again."));
        break;
    case QNetworkReply::InternalServerError:
        emit Requests::internalServerError(QObject::tr("An unexpected error occurred, please try again or contact support."));
        break;
    default:
        emit Requests::requestFailedError("Request Failed error");
        break;
    }
}

const bool Requests::isWorking() const
{
    return this->working;
}

void Requests::setIsWorking(const bool working)
{
    if (this->working != working) {
        this->working = working;
        emit Requests::isWorkingChanged();
    }
}
