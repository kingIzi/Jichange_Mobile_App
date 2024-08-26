#include "models/branchlistitems.h"

BranchListItems::BranchListItems(QObject *parent)
    : QObject{parent}
{

}

BranchListItems::BranchListItems(const QList<Branch *> &branches, QObject *parent) :
    QObject{parent},
    branches(branches)
{

}

const QList<Branch *> &BranchListItems::getBranches() const
{
    return this->branches;
}

const QList<Branch *> &BranchListItems::getBranchesModifiable()
{
    return this->branches;
}

void BranchListItems::setBranches(const QList<Branch *> &branches)
{
    if (this->branches != branches) {
        this->branches = branches;
    }
}

void BranchListItems::setItemAt(Branch *branch, const QModelIndex &index)
{
    if (!index.isValid()) { return; }
    const auto currBranch = this->branches.at(index.row());
    if (currBranch == branch) { return; }
    this->branches.replace(index.row(),branch);
}

void BranchListItems::setItemAt(const int index, Branch *branch)
{
    if (index < 0 || index >= this->branches.size()) { return; }
    const auto currBranch = this->branches.at(index);
    if (currBranch == branch) { return; }
    this->branches.replace(index,branch);
}

void BranchListItems::addItem(Branch *branch)
{
    emit BranchListItems::preItemAppended();
    this->branches.emplaceBack(branch);
    emit BranchListItems::postItemAppended();
}

void BranchListItems::removeItem(const QModelIndex &index)
{
    emit BranchListItems::preItemRemoved(index);
    this->branches.remove(index.row());
    emit BranchListItems::postItemRemoved();
}
