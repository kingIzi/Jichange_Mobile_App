#pragma once
#include <QObject>
#include <QModelIndex>
#include "entities/branch.h"

class BranchListItems : public QObject
{
    Q_OBJECT
private:
    QList<Branch*> branches;
public:
    explicit BranchListItems(QObject *parent = nullptr);
    explicit BranchListItems(const QList<Branch*>& branches,QObject *parent = nullptr);
    const QList<Branch*>& getBranches() const;
    const QList<Branch*>& getBranchesModifiable();
    void setBranches(const QList<Branch*>& branches);
public slots:
    void setItemAt(Branch* admin,const QModelIndex & index = QModelIndex());
    void setItemAt(const int index,Branch* branch);
    void addItem(Branch* branch);
    void removeItem(const QModelIndex& index = QModelIndex());
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(const QModelIndex&);
    void postItemRemoved();
};

