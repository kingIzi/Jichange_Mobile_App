#pragma once
#include <QObject>
#include "entities/branch.h"
#include "setuprequests.h"

class SetupBranch : public SetupRequests
{
    Q_OBJECT
private:
    struct Endpoints {
        static constexpr const char* list = "/api/Branch/GetBranchLists";
    };
public:
    explicit SetupBranch(SetupRequests *parent = nullptr);
public:
    Q_INVOKABLE void requestBranchList(const QVariantMap body);
private slots:
    void onListReady(const QJsonArray branchList);
signals:
    void branchList(const QList<Branch*>);
};

