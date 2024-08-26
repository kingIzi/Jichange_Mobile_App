#pragma once
#include <QDate>
#include <QAbstractListModel>
#include <qqml.h>
#include <QModelIndex>
#include "forms/formvalidator.h"

struct ItemDetail {
    QString description;
    int quantity;
    double unitPrice;
    double totalPrice;
    QString remarks;
    ItemDetail(const QString& description,const int& quantity,const double& unitPrice,const double& totalPrice,const QString& remarks) :
        description(description),quantity(quantity),unitPrice(unitPrice),totalPrice(totalPrice),remarks(remarks)
    {}
    ItemDetail() = default;
    const bool operator!=(const ItemDetail& itemDetail) const {
        const auto matchDescription = this->description.toLower() != itemDetail.description.toLower();
        const auto matchQuantity = this->quantity != itemDetail.quantity;
        const auto matchUnitPrice = this->unitPrice != itemDetail.unitPrice;
        const auto matchTotalPrice = this->totalPrice != itemDetail.totalPrice;
        const auto matchRemarks = this->remarks.toLower() != itemDetail.remarks.toLower();
        return matchDescription && matchQuantity && matchUnitPrice && matchTotalPrice && matchRemarks;
    }
    const QVariantMap getItemDetailMap() const;
};

class ItemDetailListItem : public QObject {
    Q_OBJECT
private:
    QList<ItemDetail> itemDetails;
public:
    explicit ItemDetailListItem(QObject* parent = nullptr) : QObject{parent} {}
    const bool setItemAt(const int index,ItemDetail itemDetail) {
        if (index < 0 || index >= this->itemDetails.size()) { return false; }
        const auto curr = this->itemDetails.at(index);
        if (curr != itemDetail) {
            this->itemDetails.replace(index,itemDetail);
            return true;
        }
        return false;
    }
    void setItemDetails(const QList<ItemDetail>& itemDetails) {
        this->itemDetails = itemDetails;
    }
    QList<ItemDetail>& getItemDetails() {
        return this->itemDetails;
    }
    void addItem(ItemDetail itemDetail) {
        emit ItemDetailListItem::preItemAppended();
        this->itemDetails.emplaceBack(itemDetail);
        emit ItemDetailListItem::postItemAppended();
    }
    void removeItem(const int& index) {
        emit ItemDetailListItem::preItemRemoved(index);
        this->itemDetails.remove(index);
        emit ItemDetailListItem::postItemRemoved();
    }
signals:
    void preItemAppended();
    void postItemAppended();
    void preItemRemoved(const int&);
    void postItemRemoved();
    void addedItem();
    void itemRemoved();
};

class ItemDetailsListModel : public QAbstractListModel {
    Q_OBJECT
    QML_ELEMENT;
    QML_ADDED_IN_MINOR_VERSION(1);
private:
    std::unique_ptr<ItemDetailListItem> m_itemDetailListItem = nullptr;
public:
    explicit ItemDetailsListModel(QAbstractListModel *parent = nullptr)
        : QAbstractListModel{parent},m_itemDetailListItem(std::make_unique<ItemDetailListItem>())
    {
        this->beginResetModel();
        if (this->m_itemDetailListItem) {
            QObject::connect(this->m_itemDetailListItem.get(),&ItemDetailListItem::preItemAppended,this,[=]() {
                const auto index = this->m_itemDetailListItem->getItemDetails().size();
                this->beginInsertRows(QModelIndex(),index,index);
            });
            QObject::connect(this->m_itemDetailListItem.get(),&ItemDetailListItem::postItemAppended,this,[=](){
                this->endInsertRows();
                emit this->m_itemDetailListItem->addedItem();
            });
            QObject::connect(this->m_itemDetailListItem.get(),&ItemDetailListItem::preItemRemoved,this,[=](const int& index){
                this->beginRemoveRows(QModelIndex(),index,index);
            });
            QObject::connect(this->m_itemDetailListItem.get(),&ItemDetailListItem::postItemRemoved,this,[=](){
                this->endRemoveRows();
                emit this->m_itemDetailListItem->itemRemoved();
            });
        }
        this->endResetModel();
    }
    ItemDetailListItem* getItemDetailListItem() {
        return this->m_itemDetailListItem.get();
    }
    int rowCount(const QModelIndex & index = QModelIndex()) const override {
        if (!index.isValid() && this->m_itemDetailListItem)
            return this->m_itemDetailListItem->getItemDetails().size();
        return 0;
    }
    Qt::ItemFlags flags(const QModelIndex& index) const override {
        if (!index.isValid()) { return Qt::NoItemFlags; }
        return Qt::ItemIsEditable;
    }
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole) override {
        if (!this->m_itemDetailListItem.get()) { return false; }
        auto& item = this->m_itemDetailListItem->getItemDetails()[index.row()];
        switch (role) {
        case ItemDetailsListModel::DESCRIPTION:
            item.description = value.toString();
            break;
        case ItemDetailsListModel::QUANTITY:
            item.quantity = value.toUInt();
            break;
        case ItemDetailsListModel::UNIT_PRICE:
            item.unitPrice = value.toDouble();
            break;
        case ItemDetailsListModel::TOTAL_AMOUNT:
            item.totalPrice = value.toDouble();
        case ItemDetailsListModel::REMARKS:
            item.remarks = value.toString();
        default:
            break;
        }
        if (this->m_itemDetailListItem->setItemAt(index.row(),item)) {
            emit dataChanged(index,index,QList<int>() << role);
            return true;
        }
        return false;
    }
    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid() || !this->m_itemDetailListItem) { return QVariant(); }
        const auto& itemDetail = this->m_itemDetailListItem->getItemDetails().at(index.row());
        switch (role) {
        case ItemDetailsListModel::DESCRIPTION:
            return QVariant::fromValue(itemDetail.description);
        case ItemDetailsListModel::QUANTITY:
            return QVariant::fromValue(itemDetail.quantity);
        case ItemDetailsListModel::UNIT_PRICE:
            return QVariant::fromValue(itemDetail.unitPrice);
        case ItemDetailsListModel::TOTAL_AMOUNT:
            return QVariant::fromValue(itemDetail.totalPrice);
        case ItemDetailsListModel::REMARKS:
            return itemDetail.remarks;
        default:
            return QVariant();
        }
    }
    QHash<int, QByteArray> roleNames() const override {
        return {
            {DESCRIPTION,"item_description"},
            {QUANTITY,"item_qty"},
            {UNIT_PRICE,"item_unit_price"},
            {TOTAL_AMOUNT,"item_total_amount"},
            {REMARKS,"remarks"}
        };
    }
    const double getItemDetailsTotal() {
        const double total_sum = std::accumulate(this->m_itemDetailListItem->getItemDetails().begin(),
                                                 this->m_itemDetailListItem->getItemDetails().end(), 0,[](int sum, const ItemDetail& item) {
            return sum + item.totalPrice;
        });
        return total_sum;
    }
    enum {
        DESCRIPTION = Qt::UserRole + 1, QUANTITY,UNIT_PRICE,TOTAL_AMOUNT,REMARKS
    };
};

class InvoiceForm : public FormValidator
{
    Q_OBJECT
    Q_PROPERTY(ItemDetailsListModel* itemDetailsListModel READ itemDetailsListModel WRITE setItemDetailsListModel NOTIFY itemDetailsListModelChanged);
    Q_PROPERTY(int itemDetailsLength READ itemDetailsLength WRITE setItemDetailsLength NOTIFY itemDetailsLengthChanged);
public:
    struct Details {
        static constexpr const char* item_description = "item_description"; //item description
        static constexpr const char* item_qty = "item_qty"; //item quantity
        static constexpr const char* item_unit_price = "item_unit_price"; //item unit price
        static constexpr const char* item_total_amount = "item_total_amount"; //item total price
        static constexpr const char* remarks = "remarks"; //remarks
    };
private:
    QQmlListReference m_details;
    QList<QList<Validator*>> temp_details;
    std::unique_ptr<ItemDetailsListModel> m_itemDetailsListModel;
    int m_itemDetailLength;
private:
    const bool validateItemDetail(Validator const* validator);
public:
    struct FormKeys {
        static constexpr const char* invno = "invno"; //invoice number
        static constexpr const char* date = "date"; //invoice date
        static constexpr const char* edate = "edate"; //due date
        static constexpr const char* iedate = "iedate"; //expiry date
        static constexpr const char* chus = "chus"; //customer id
        static constexpr const char* ptype = "ptype"; //payment type
        static constexpr const char* ccode = "ccode"; //currency code
        static constexpr const char* Inv_remark = "Inv_remark"; //invoice remark
        static constexpr const char* user_id = "user_id"; //user id
        static constexpr const char* compid = "compid"; //company id
        static constexpr const char* comno = "comno";
        static constexpr const char* ctype = "ctype";
        static constexpr const char* cino = "cino";
        static constexpr const char* twvat = "twvat";
        static constexpr const char* vtamou = "vtamou";
        static constexpr const char* lastrow = "lastrow";
        static constexpr const char* total = "total";
        static constexpr const char* auname = "auname";
        static constexpr const char* details = "details"; //details
    };
private:
    void addArbitiaryAddInvoiceData(QVariantMap& form);
public:
    explicit InvoiceForm(QObject *parent = nullptr);
    ItemDetailsListModel* itemDetailsListModel();
    Q_INVOKABLE void validate() override;
    Q_INVOKABLE void qmlValidate() override;
    Q_INVOKABLE void appendItemDetail();
    Q_INVOKABLE void removeItemDetail(const int index);
    Q_INVOKABLE double getItemDetailsTotal() const;
    const int itemDetailsLength() const;
    QList<QList<Validator*>>& getTempDetails() {
        return temp_details;
    }
public:
    void setDetails(const QQmlListReference& details);
public slots:
    void setItemDetailsListModel(ItemDetailsListModel* itemDetailsListModel);
    void setItemDetailsLength(const int& length);
signals:
    void detailsChanged();
    void itemDetailsListModelChanged();
    void itemDetailsLengthChanged();
};

