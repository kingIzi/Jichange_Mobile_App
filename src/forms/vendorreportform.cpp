#include "forms/vendorreportform.h"

VendorReportForm::VendorReportForm(QObject *parent)
    : FormValidator{parent}
{

}

const long long int VendorReportForm::Comp() const
{
    return static_cast<long long int>(this->getForm().value(FormKeys::Comp).toULongLong());
}

const long long VendorReportForm::reg() const
{
    return static_cast<long long int>(this->getForm().value(FormKeys::reg).toULongLong());
}

const long long VendorReportForm::dist() const
{
    return static_cast<long long int>(this->getForm().value(FormKeys::dist).toULongLong());
}

void VendorReportForm::setComp(const long long Comp)
{
    this->getModifiableForm().insert(FormKeys::Comp,Comp);
    emit VendorReportForm::CompChanged();
}

void VendorReportForm::setReg(const long long reg)
{
    this->getModifiableForm().insert(FormKeys::reg,reg);
    emit VendorReportForm::regChanged();
}

void VendorReportForm::setDist(const long long dist)
{
    this->getModifiableForm().insert(FormKeys::dist,dist);
    emit VendorReportForm::distChanged();
}
