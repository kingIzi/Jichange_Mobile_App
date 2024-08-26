#include "forms/customerform.h"


CustomerForm::CustomerForm(QObject *parent) :
    FormValidator{{},parent}
{

}

const QString CustomerForm::cust_Name() const
{
    return this->getForm().value(FormKeys::Cust_Name).toString();
}

const QString CustomerForm::phone() const
{
    return this->getForm().value(FormKeys::Phone).toString();
}

const QString CustomerForm::email() const
{
    return this->getForm().value(FormKeys::Email).toString();
}

const QString &CustomerForm::phoneCountryCode() const
{
    return this->m_phoneCountryCode;
}

void CustomerForm::validate()
{
    auto form = this->getForm();
    for (const auto& value : this->validators()) {
        const auto key = value->name();
        if (value->required() && !form.contains(key)) {
            this->invalidValue(key,value->errors().at(0));
            return;
        }
        auto string = form.value(key).toString();
        if (value->required() && string.isEmpty()) {
            this->invalidValue(key,value->errors().at(0));
            return;
        }
        value->validator()->fixup(string);
        int pos = 0;
        const auto valid = value->validator()->validate(string,pos);
        if (valid == QValidator::Invalid) {
            this->invalidValue(key,value->errors().at(1));
            return;
        }
        if (key.compare(FormKeys::Phone,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_phoneCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::Phone,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_phoneCountryCode.isEmpty()) {
            form.insert(FormKeys::Phone,this->m_phoneCountryCode + string);
        }
    }
    emit FormValidator::isValidForm(form);
}

void CustomerForm::qmlValidate()
{
    const auto vals = this->getValidators();
    auto form = this->getForm();
    for (const auto& value : vals) {
        const auto key = value->name();
        if (value->required() && !form.contains(key)) {
            this->invalidValue(key,value->errors().at(0));
            return;
        }
        auto string = form.value(key).toString();
        if (value->required() && string.isEmpty()) {
            this->invalidValue(key,value->errors().at(0));
            return;
        }
        value->validator()->fixup(string);
        int pos = 0;
        const auto valid = value->validator()->validate(string,pos);
        if (valid == QValidator::Invalid) {
            this->invalidValue(key,value->errors().at(1));
            return;
        }
        if (key.compare(FormKeys::Phone,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_phoneCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::Phone,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_phoneCountryCode.isEmpty()) {
            form.insert(FormKeys::Phone,this->m_phoneCountryCode + string);
        }
    }
    emit FormValidator::isValidForm(form);
}

void CustomerForm::setCust_Name(const QString &Cust_Name)
{
    if (this->cust_Name().compare(Cust_Name,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::Cust_Name,Cust_Name.trimmed());
        emit CustomerForm::cust_NameChanged();
    }
}

void CustomerForm::setPhone(const QString &Phone)
{
    if (this->phone().compare(Phone,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::Phone,Phone.trimmed());
        emit CustomerForm::phoneChanged();
    }
}

void CustomerForm::setEmail(const QString &Email)
{
    if (this->email().compare(Email,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::Email,Email.trimmed());
        emit CustomerForm::emailChanged();
    }
}

void CustomerForm::setPhoneCountryCode(const QString &phoneCountryCode)
{
    if (this->m_phoneCountryCode.compare(phoneCountryCode,Qt::CaseSensitive) != 0) {
        this->m_phoneCountryCode = phoneCountryCode;
        emit CustomerForm::phoneCountryCodeChanged();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


