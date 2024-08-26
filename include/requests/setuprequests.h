#pragma once
#include <QObject>
#include "requests.h"

class SetupRequests : public Requests
{
    Q_OBJECT
public:
    explicit SetupRequests(Requests *parent = nullptr);
    virtual void getList(const QString& path, const QVariantMap& body);
    virtual void parseList(QNetworkReply * reply);
signals:
    void listReady(const QJsonArray);
    void listNotFound();
};

