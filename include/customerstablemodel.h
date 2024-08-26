#pragma once
//#include <QObject>

//class CustomersTableModel : public QObject
//{
//    Q_OBJECT
//public:
//    explicit CustomersTableModel(QObject *parent = nullptr);

//signals:

//};

#include <QtQml/qqml.h>
#include <QAbstractTableModel>
#include <QStringList>

class CustomersTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_VERSION(1, 1)
    Q_PROPERTY(int showing READ showing WRITE setShowing NOTIFY showingChanged FINAL)
    Q_PROPERTY(bool isEmpty READ isEmpty WRITE setIsEmpty NOTIFY isEmptyChanged FINAL)
private:
    bool empty = true;
    int showingCount = 5;
    QStringList headers = {"Full name","Email","Mobile number","Action"};
public slots:
    void setShowing(const int showingCount);
    void setIsEmpty(const bool isEmpty);
public:
    const int& showing() const;
    const bool& isEmpty() const;
    int rowCount(const QModelIndex & index = QModelIndex()) const override
    {
        if (index.isValid()) { return 0; }
        return 1;
    }

    int columnCount(const QModelIndex & index = QModelIndex()) const override
    {
        if (index.isValid()) { return 0; }
        return this->headers.length();
    }

    QVariant data(const QModelIndex &index, int role) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString("%1, %2").arg(index.column()).arg(index.row());
        default:
            break;
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return this->headers.at(section);
            //return QString("Header #%1").arg(section);
        default:
            break;
        }
        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return { {Qt::DisplayRole, "display"} };
    }
signals:
    void showingChanged();
    void isEmptyChanged();
};

