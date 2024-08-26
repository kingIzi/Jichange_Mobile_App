#pragma once

#include <QObject>
#include <QVariantMap>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QByteArray>
#include <QThread>
#include <QVariantMap>
#include <QVariant>
#include <QVariantList>
#include <QStringList>
#include <QPair>
#include <QList>
#include <memory>

class Requests : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isWorking READ isWorking WRITE setIsWorking NOTIFY isWorkingChanged)
private:
    std::unique_ptr<QNetworkAccessManager> manager;
    bool working;
private:
    void appendUrlQueryItems(QUrl& url,const QList<QPair<QString,QString>>& params) const;
public:
    explicit Requests(QObject *parent = nullptr);
    struct BaseKeys {
        static constexpr const char* response = "response";
    };
public:
    static constexpr const char* BaseUrl = "http://192.168.100.50:98";
public:
    QNetworkReply* peformPost(const QVariantMap& body,const QString& path,const QList<QPair<QString,QString>> params = {},const QString baseUrl = "");
    QNetworkReply* peformGet(const QString& path,const QList<QPair<QString,QString>> params = {},const QString baseUrl = "");
    QNetworkReply* requestPostReply(const QVariantMap& body,const QString& path);
    QNetworkReply* requestGetReply(const QString& path,const QList<QPair<QString,QString>> params = {});
    virtual void parseRequestError(const QNetworkReply::NetworkError &error);
    const bool isWorking() const;
public slots:
    void setIsWorking(const bool working);
signals:
    void timeoutError(const QString);
    void connectionRefusedError(const QString);
    void internalServerError(const QString);
    void requestFailedError(const QString);
    void isWorkingChanged();
};

