#include <QtConcurrent/QtConcurrent>
#include "requests/setuprequests.h"


SetupRequests::SetupRequests(Requests *parent)
    : Requests{parent}
{

}

void SetupRequests::getList(const QString& path, const QVariantMap& body)
{
    QEventLoop loop;
    const auto reply = Requests::peformPost(body,path);
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    const auto future = QtConcurrent::run([reply,this](){
        while (!reply->isFinished()) {
            this->setIsWorking(true);
            QThread::sleep(1);
        }
    });
    loop.exec();
    this->setIsWorking(false);
    this->parseList(reply);
}

void SetupRequests::parseList(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        return;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.object().value("response").isArray()) {
        emit SetupRequests::listNotFound();
    }
    else {
        const auto branchList = doc.object().value("response").toArray();
        emit SetupRequests::listReady(branchList);
    }
}
