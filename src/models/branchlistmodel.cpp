#include "models/branchlistmodel.h"

void BranchListModel::populateSignals()
{
    if (!this->listItems)
        return;
    QObject::connect(this->listItems.get(),&BranchListItems::postItemAppended,this,[this](){
        const auto index = this->listItems->getBranches().size();
        QAbstractItemModel::beginInsertRows(QModelIndex(),index,index);
    });
    QObject::connect(this->listItems.get(),&BranchListItems::postItemAppended,this,[this](){
        QAbstractItemModel::endInsertRows();
    });
    QObject::connect(this->listItems.get(),&BranchListItems::preItemRemoved,this,[this](QModelIndex index){
        QAbstractItemModel::beginRemoveRows(QModelIndex(),index.row(),index.row());
    });
    QObject::connect(this->listItems.get(),&BranchListItems::postItemRemoved,this,[this](){
        this->endRemoveRows();
    });
}

void BranchListModel::onPopulate(const QList<Branch *> branches)
{
    QAbstractItemModel::beginResetModel();
    this->listItems->setBranches(branches);
    QAbstractItemModel::endResetModel();
}

BranchListModel::BranchListModel(QAbstractListModel *parent)
    : QAbstractListModel{parent},
      empty(true),
      listItems(std::make_unique<BranchListItems>())
      //listItems(nullptr)
{
    QObject::connect(this,&BranchListModel::populate,this,&BranchListModel::onPopulate);
}

BranchListModel::~BranchListModel()
{
    qDebug() << "Branch list model destroyed";
}

const bool BranchListModel::isEmpty() const
{
    return this->empty;
}

BranchListItems *BranchListModel::branchListItems() const
{
    return this->listItems.get();
}

int BranchListModel::rowCount(const QModelIndex &index) const
{
    if (!index.isValid() && this->listItems)
        return this->listItems->getBranches().length();
    return 0;
}

QVariant BranchListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !this->listItems)
        return QVariant();
    const auto& branch = this->listItems->getBranches().at(index.row());
    switch (role) {
    case SNO:
        return branch->getSno();
    case BRANCH_SNO:
        return branch->getBranchSno();
    case NAME:
        return branch->getName();
    case LOCATION:
        return branch->getLocation();
    case STATUS:
        return branch->getStatus();
    case AUDIT_BY:
        return branch->getAuditBy();
    case AUDIT_DATE:
        return branch->getAuditDate().toString("dd MMM yyyy");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> BranchListModel::roleNames() const
{
    return {
        {SNO,Branch::Keys::Sno},
        {BRANCH_SNO,Branch::Keys::Branch_Sno},
        {NAME,Branch::Keys::Name},
        {LOCATION,Branch::Keys::Location},
        {STATUS,Branch::Keys::Status},
        {AUDIT_BY,Branch::Keys::AuditBy},
        {AUDIT_DATE,Branch::Keys::Audit_Date}
    };
}

void BranchListModel::setIsEmpty(const bool &empty)
{
    if (this->empty != empty) {
        this->empty = empty;
        emit BranchListModel::isEmptyChanged();
    }
}
