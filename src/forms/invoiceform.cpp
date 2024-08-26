#include "forms/invoiceform.h"
#include <QMetaType>

const bool InvoiceForm::validateItemDetail(const Validator *ref)
{
    if (ref->required() && !ref->value().isValid()) {
        this->invalidValue(FormKeys::details,ref->errors().at(0));
        return false;
    }
    if (ref->required() && ref->value().typeId() == QMetaType::QString) {
        auto string = ref->value().toString();
        if (ref->required() && string.isEmpty()) {
            this->invalidValue(FormKeys::details,ref->errors().at(0));
            return false;
        }
        ref->validator()->fixup(string);
        int pos = 0;
        const auto valid = ref->validator()->validate(string,pos);
        if (valid == QValidator::Invalid) {
            this->invalidValue(FormKeys::details,ref->errors().at(1));
            return false;
        }
    }
    return true;
}

void InvoiceForm::addArbitiaryAddInvoiceData(QVariantMap &form)
{
    form.insert(InvoiceForm::FormKeys::total,this->getItemDetailsTotal());
    form.insert(InvoiceForm::FormKeys::auname,this->getItemDetailsTotal());
    form.insert(InvoiceForm::FormKeys::comno,0);
    form.insert(InvoiceForm::FormKeys::ctype,0);
    form.insert(InvoiceForm::FormKeys::cino,0);
    form.insert(InvoiceForm::FormKeys::twvat,0);
    form.insert(InvoiceForm::FormKeys::vtamou,0);
    form.insert(InvoiceForm::FormKeys::lastrow,0);
}

InvoiceForm::InvoiceForm(QObject *parent)
    : FormValidator{parent},
      m_itemDetailsListModel(std::make_unique<ItemDetailsListModel>())
{
    QObject::connect(this->m_itemDetailsListModel->getItemDetailListItem(),&ItemDetailListItem::addedItem,this,[=](){
        this->setItemDetailsLength(this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().length());
    });
    QObject::connect(this->m_itemDetailsListModel->getItemDetailListItem(),&ItemDetailListItem::itemRemoved,this,[=](){
        this->setItemDetailsLength(this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().length());
    });
}

ItemDetailsListModel *InvoiceForm::itemDetailsListModel()
{
    return this->m_itemDetailsListModel.get();
}

void InvoiceForm::validate()
{
    QVariantMap form;
    for (const auto& ref : this->validators()) {
        const auto key = ref->name();
        if (key.compare(FormKeys::details,Qt::CaseSensitive) != 0) {
            if (ref->required() && !ref->value().isValid()) {
                this->invalidValue(key,ref->errors().at(0));
                return;
            }
            if (ref->required() && ref->value().typeId() == QMetaType::QString) {
                auto string = ref->value().toString();
                if (ref->required() && string.isEmpty()) {
                    this->invalidValue(key,ref->errors().at(0));
                    return;
                }
                ref->validator()->fixup(string);
                int pos = 0;
                const auto valid = ref->validator()->validate(string,pos);
                if (valid == QValidator::Invalid) {
                    this->invalidValue(key,ref->errors().at(1));
                    return;
                }
                form.insert(key,string);
                continue;
            }
            if (!ref->required() && ref->value().isValid()) {
                auto string = ref->value().toString();
                ref->validator()->fixup(string);
                int pos = 0;
                const auto valid = ref->validator()->validate(string,pos);
                if (valid == QValidator::Invalid) {
                    this->invalidValue(key,ref->errors().at(1));
                    return;
                }
                form.insert(key,string);
                continue;
            }
        }
        else if (key.compare(FormKeys::details,Qt::CaseSensitive) == 0) {
            if (this->getTempDetails().isEmpty()) {
                this->invalidValue(key,ref->errors().at(0));
                return;
            }
            QVariantList item_details;
            item_details.reserve(this->getTempDetails().size());
            for (const auto& details_list : this->getTempDetails()) {
                QVariantMap item;
                for (const auto& detailRef : details_list) {
                    if (detailRef->required() && !detailRef->value().isValid()) {
                        this->invalidValue(key,detailRef->errors().at(0));
                        return;
                    }
                    else if (detailRef->required() && detailRef->value().isValid()) {
                        auto string = detailRef->value().toString();
                        if (string.isEmpty()) {
                            this->invalidValue(key,detailRef->errors().at(0));
                            return;
                        }
                        detailRef->validator()->fixup(string);
                        int pos = 0;
                        const auto valid = detailRef->validator()->validate(string,pos);
                        if (valid == QValidator::Invalid) {
                            this->invalidValue(key,ref->errors().at(1));
                            return;
                        }
                        item.insert(detailRef->name(),string);
                        continue;
                    }
                    else if (!detailRef->required() && detailRef->value().isValid()) {
                        auto string = detailRef->value().toString();
                        detailRef->validator()->fixup(string);
                        int pos = 0;
                        const auto valid = detailRef->validator()->validate(string,pos);
                        if (valid == QValidator::Invalid) {
                            this->invalidValue(key,ref->errors().at(1));
                            return;
                        }
                        item.insert(detailRef->name(),string);
                        continue;
                    }
                }
                item_details.emplaceBack(item);
            }
            ref->setValue(item_details);
            form.insert(key,ref->value());
        }
    }
    emit FormValidator::isValidForm(form);
}

void InvoiceForm::qmlValidate()
{
    QVariantMap form;
    const auto vals = this->getValidators();
    for (const auto& ref : vals) {
        const auto key = ref->name();
        if (key.compare(FormKeys::details,Qt::CaseSensitive) != 0) {
            if (ref->required() && !ref->value().isValid()) {
                this->invalidValue(key,ref->errors().at(0));
                return;
            }
            if (ref->required() && ref->value().typeId() == QMetaType::QString) {
                auto string = ref->value().toString();
                if (ref->required() && string.isEmpty()) {
                    this->invalidValue(key,ref->errors().at(0));
                    return;
                }
                ref->validator()->fixup(string);
                int pos = 0;
                const auto valid = ref->validator()->validate(string,pos);
                if (valid == QValidator::Invalid) {
                    this->invalidValue(key,ref->errors().at(1));
                    return;
                }
                form.insert(key,string);
                continue;
            }
            if (!ref->required() && ref->value().isValid()) {
                auto string = ref->value().toString();
                ref->validator()->fixup(string);
                int pos = 0;
                const auto valid = ref->validator()->validate(string,pos);
                if (valid == QValidator::Invalid) {
                    this->invalidValue(key,ref->errors().at(1));
                    return;
                }
                form.insert(key,string);
                continue;
            }
        }
    }
    if (this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().size() <= 0) {
        this->invalidValue(FormKeys::details,QObject::tr("You must add at least one item."));
        return;
    }
    QVariantList item_details;
    item_details.reserve(this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().length());
    for (auto i = 0; i < this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().length(); i++) {
        const auto itemDetail = this->m_itemDetailsListModel->getItemDetailListItem()->getItemDetails().at(i);
        if (itemDetail.description.isEmpty()) {
            emit FormValidator::isInvalidForm(QString("Please specify item %1 description.").arg(QString::number(i + 1)));
            return;
        }
        if (itemDetail.quantity == 0) {
            emit FormValidator::isInvalidForm(QString("Item %1 quantity cannot be 0.").arg(QString::number(i + 1)));
            return;
        }
        if (itemDetail.unitPrice == 0) {
            emit FormValidator::isInvalidForm(QString("Item %1 unit price cannot be 0.").arg(QString::number(i + 1)));
            return;
        }
        if (itemDetail.totalPrice == 0) {
            emit FormValidator::isInvalidForm(QString("Please specify item %1 unit price and quantity.").arg(QString::number(i + 1)));
            return;
        }
        item_details.emplaceBack(itemDetail.getItemDetailMap());
    }
    form.insert(InvoiceForm::FormKeys::details,item_details);
    this->addArbitiaryAddInvoiceData(form);
    emit FormValidator::isValidForm(form);
}

void InvoiceForm::appendItemDetail()
{
    this->m_itemDetailsListModel->getItemDetailListItem()->addItem(ItemDetail());
}

void InvoiceForm::removeItemDetail(const int index)
{
    this->m_itemDetailsListModel->getItemDetailListItem()->removeItem(index);
}

double InvoiceForm::getItemDetailsTotal() const
{
    return this->m_itemDetailsListModel->getItemDetailsTotal();
}

const int InvoiceForm::itemDetailsLength() const
{
    return this->m_itemDetailLength;
}

void InvoiceForm::setItemDetailsListModel(ItemDetailsListModel *itemDetailsListModel)
{
    if (this->m_itemDetailsListModel.get() != itemDetailsListModel) {
        emit InvoiceForm::itemDetailsListModelChanged();
    }
}

void InvoiceForm::setItemDetailsLength(const int &length)
{
    if (this->m_itemDetailLength != length) {
        this->m_itemDetailLength = length;
        emit InvoiceForm::itemDetailsLengthChanged();
    }
}

const QVariantMap ItemDetail::getItemDetailMap() const
{
    QVariantMap item;
    item.insert(InvoiceForm::Details::item_description,this->description);
    item.insert(InvoiceForm::Details::item_qty,this->quantity);
    item.insert(InvoiceForm::Details::item_unit_price,this->unitPrice);
    item.insert(InvoiceForm::Details::item_total_amount,this->unitPrice * this->quantity);
    item.insert(InvoiceForm::Details::remarks,this->remarks);
    return item;
}
