#pragma once
#include <QObject>
#include <qqml.h>
#include <QAbstractListModel>
#include "models/branchlistitems.h"

class BranchListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT;
    QML_ADDED_IN_MINOR_VERSION(1);
    Q_PROPERTY(bool isEmpty READ isEmpty WRITE setIsEmpty NOTIFY isEmptyChanged);
    Q_PROPERTY(BranchListItems* branchListItems READ branchListItems NOTIFY branchListItemsChanged)
private:
    bool empty;
    std::unique_ptr<BranchListItems> listItems;
private:
    void populateSignals();
private slots:
    void onPopulate(const QList<Branch*> branches);
public:
    explicit BranchListModel(QAbstractListModel *parent = nullptr);
    ~BranchListModel();
    const bool isEmpty() const;
    BranchListItems* branchListItems() const;
    enum {
        SNO = Qt::UserRole + 1,BRANCH_SNO,NAME,LOCATION,STATUS,AUDIT_BY,AUDIT_DATE
    };
public:
    int rowCount(const QModelIndex & index = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
public slots:
    void setIsEmpty(const bool& empty);
signals:
    void isEmptyChanged();
    void branchListItemsChanged();
    void populate(const QList<Branch*>);
};

