#include "entities/branch.h"

QString Branch::getName() const
{
    return this->name;
}

void Branch::setName(const QString &newName)
{
    this->name = newName;
}

QString Branch::getLocation() const
{
    return this->location;
}

void Branch::setLocation(const QString &newLocation)
{
    this->location = newLocation;
}

QString Branch::getStatus() const
{
    return this->status;
}

void Branch::setStatus(const QString &newStatus)
{
    this->status = newStatus;
}

int Branch::getSno() const
{
    return this->sno;
}

void Branch::setSno(int newSno)
{
    this->sno = newSno;
}

int Branch::getBranchSno() const
{
    return this->branchSno;
}

void Branch::setBranchSno(int newBranchSno)
{
    this->branchSno = newBranchSno;
}

QString Branch::getAuditBy() const
{
    return this->auditBy;
}

void Branch::setAuditBy(const QString &newAuditBy)
{
    this->auditBy = newAuditBy;
}

QDateTime Branch::getAuditDate() const
{
    return this->auditDate;
}

void Branch::setAuditDate(const QDateTime &newAuditDate)
{
    this->auditDate = newAuditDate;
}

Branch::Branch(QObject *parent)
    : QObject{parent}
{

}

Branch::Branch(const QJsonObject &branch, QObject *parent)
    : QObject{parent},
      name(branch.value(Keys::Name).toString()),
      location(branch.value(Keys::Location).toString()),
      status(branch.value(Keys::Status).toString()),
      sno(branch.value(Keys::Sno).toInt()),
      branchSno(branch.value(Keys::Branch_Sno).toInt()),
      auditBy(branch.value(Keys::AuditBy).toString()),
      auditDate(QDateTime::fromString(branch.value(Keys::Audit_Date).toString(),Qt::ISODate))
{

}

const QList<Branch*> Branch::createList(const QJsonArray &branchList)
{
    QList<Branch*> branches;
    branches.reserve(branchList.size());
    for (const auto& branch : branchList) {
        if (!branch.isObject())
            continue;
        branches.emplaceBack(new Branch(branch.toObject()));
    }
    return branches;
}
