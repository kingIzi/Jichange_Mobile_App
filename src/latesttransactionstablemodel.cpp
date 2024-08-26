#include "latesttransactionstablemodel.h"

void LatestTransactionsTableModel::setShowing(const int showingCount)
{
    if (this->showingCount != showingCount) {
        this->showingCount = showingCount;
        emit LatestTransactionsTableModel::showingChanged();
    }
}

void LatestTransactionsTableModel::setIsEmpty(const bool isEmpty)
{
    if (this->empty != isEmpty) {
        this->empty = isEmpty;
        emit LatestTransactionsTableModel::isEmptyChanged();
    }
}

const int &LatestTransactionsTableModel::showing() const
{
    return this->showingCount;
}

const bool &LatestTransactionsTableModel::isEmpty() const
{
    return this->empty;
}
