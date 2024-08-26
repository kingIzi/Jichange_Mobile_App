#include "requests/setupbranch.h"

SetupBranch::SetupBranch(SetupRequests *parent)
    : SetupRequests{parent}
{
    QObject::connect(this,&SetupRequests::listReady,this,&SetupBranch::onListReady);
}

void SetupBranch::requestBranchList(const QVariantMap body)
{
    SetupRequests::getList(Endpoints::list,body);
}

void SetupBranch::onListReady(const QJsonArray branchList)
{
    const auto branches = Branch::createList(branchList);
    emit SetupBranch::branchList(branches);
}
