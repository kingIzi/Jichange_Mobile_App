#include "customerstablemodel.h"

//CustomersTableModel::CustomersTableModel(QObject *parent)
//    : QObject{parent}
//{

//}

void CustomersTableModel::setShowing(const int showingCount)
{
    if (this->showingCount != showingCount) {
        this->showingCount = showingCount;
        emit CustomersTableModel::showingChanged();
    }
}

void CustomersTableModel::setIsEmpty(const bool isEmpty)
{
    if (this->empty != isEmpty) {
        this->empty = isEmpty;
        emit CustomersTableModel::isEmptyChanged();
    }
}

const int &CustomersTableModel::showing() const
{
    return this->showingCount;
}

const bool &CustomersTableModel::isEmpty() const
{
    return this->empty;
}
