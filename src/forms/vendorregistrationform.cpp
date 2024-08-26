#include "forms/vendorregistrationform.h"
#include <QRegularExpression>

VendorRegistrationForm::VendorRegistrationForm(QObject *parent)
    : FormValidator{{FormKeys::rsno,FormKeys::dsno,FormKeys::wsno,FormKeys::compsno},parent}
{

}

const int VendorRegistrationForm::compsno() const
{
    return this->getForm().value(FormKeys::compsno).toInt();
}

const QString VendorRegistrationForm::compname() const
{
    return this->getForm().value(FormKeys::compname).toString();
}

const QString VendorRegistrationForm::mob() const
{
    return this->getForm().value(FormKeys::mob).toString();
}

const int VendorRegistrationForm::branch() const
{
    return this->getForm().value(FormKeys::branch).toInt();
}

const QString VendorRegistrationForm::check_status() const
{
    return this->getForm().value(FormKeys::check_status).toString();
}

const QString VendorRegistrationForm::fax() const
{
    return this->getForm().value(FormKeys::fax).toString();
}

const QString VendorRegistrationForm::pbox() const
{
    return this->getForm().value(FormKeys::pbox).toString();
}

const QString VendorRegistrationForm::addr() const
{
    return this->getForm().value(FormKeys::addr).toString();
}

const int VendorRegistrationForm::rsno() const
{
    return this->getForm().value(FormKeys::rsno).toInt();
}

const int VendorRegistrationForm::dsno() const
{
    return this->getForm().value(FormKeys::dsno).toInt();
}

const int VendorRegistrationForm::wsno() const
{
    return this->getForm().value(FormKeys::wsno).toInt();
}

const QString VendorRegistrationForm::tin() const
{
    return this->getForm().value(FormKeys::tin).toString();
}

const QString VendorRegistrationForm::vat() const
{
    return this->getForm().value(FormKeys::vat).toString();
}

const QString VendorRegistrationForm::dname() const
{
    return this->getForm().value(FormKeys::dname).toString();
}

const QString VendorRegistrationForm::telno() const
{
    return this->getForm().value(FormKeys::telno).toString();
}

const QString VendorRegistrationForm::email() const
{
    return this->getForm().value(FormKeys::email).toString();
}

const bool VendorRegistrationForm::dummy() const
{
    return this->getForm().value(FormKeys::dummy).toBool();
}

const QString VendorRegistrationForm::accno() const
{
    return this->getForm().value(FormKeys::accno).toString();
}

const QString &VendorRegistrationForm::mobCountryCode() const
{
    return this->m_mobCountryCode;
}

const QString &VendorRegistrationForm::telnoCountryCode() const
{
    return this->m_telnoCountryCode;
}

void VendorRegistrationForm::setCompsno(const int &compsno)
{
    this->getModifiableForm().insert(FormKeys::compsno,compsno);
    emit VendorRegistrationForm::compsnoChanged();
}

void VendorRegistrationForm::setCompname(const QString &compname)
{
    if (this->compname().compare(compname,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::compname,compname.trimmed());
        emit VendorRegistrationForm::compnameChanged();
    }
}

void VendorRegistrationForm::setMob(const QString &mob)
{
    if (this->mob().compare(mob,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::mob,mob.trimmed());
        emit VendorRegistrationForm::mobChanged();
    }
}

void VendorRegistrationForm::setBranch(const int &branch)
{
    if (this->branch() != branch) {
        this->getModifiableForm().insert(FormKeys::branch,branch);
        emit VendorRegistrationForm::branchChanged();
    }
}

void VendorRegistrationForm::setCheck_status(const QString &check_status)
{
    if (this->check_status().compare(check_status,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::check_status,check_status.trimmed());
        emit VendorRegistrationForm::check_statusChanged();
    }
}

void VendorRegistrationForm::setFax(const QString &fax)
{
    if (this->fax().compare(fax,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::fax,fax.trimmed());
        emit VendorRegistrationForm::faxChanged();
    }
}

void VendorRegistrationForm::setPbox(const QString &pbox)
{
    if (this->pbox().compare(pbox,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::pbox,pbox.trimmed());
        emit VendorRegistrationForm::pboxChanged();
    }
}

void VendorRegistrationForm::setAddr(const QString &addr)
{
    if (this->addr().compare(addr,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::addr,addr.trimmed());
        emit VendorRegistrationForm::addrChanged();
    }
}

void VendorRegistrationForm::setRsno(const int &rsno)
{
    this->getModifiableForm().insert(FormKeys::rsno,rsno);
    emit VendorRegistrationForm::rsnoChanged();
}

void VendorRegistrationForm::setDsno(const int &dsno)
{
    this->getModifiableForm().insert(FormKeys::dsno,dsno);
    emit VendorRegistrationForm::dsnoChanged();
}

void VendorRegistrationForm::setWsno(const int &wsno)
{
    this->getModifiableForm().insert(FormKeys::wsno,wsno);
    emit VendorRegistrationForm::wsnoChanged();
}

void VendorRegistrationForm::setTin(const QString &tin)
{
    if (this->tin().compare(tin,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::tin,tin.trimmed());
        emit VendorRegistrationForm::tinChanged();
    }
}

void VendorRegistrationForm::setVat(const QString &vat)
{
    if (this->vat().compare(vat,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::vat,vat.trimmed());
        emit VendorRegistrationForm::vatChanged();
    }
}

void VendorRegistrationForm::setDname(const QString &dname)
{
    if (this->dname().compare(dname,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::dname,dname.trimmed());
        emit VendorRegistrationForm::dnameChanged();
    }
}

void VendorRegistrationForm::setTelno(const QString &telno)
{
    if (this->telno().compare(telno,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::telno,telno.trimmed());
        emit VendorRegistrationForm::telnoChanged();
    }
}

void VendorRegistrationForm::setEmail(const QString &email)
{
    if (this->email().compare(email,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::email,email.trimmed());
        emit VendorRegistrationForm::emailChanged();
    }
}

void VendorRegistrationForm::setDummy(const bool &dummy)
{
    this->getModifiableForm().insert(FormKeys::dummy,dummy);
    emit VendorRegistrationForm::dummyChanged();
}

void VendorRegistrationForm::setAccno(const QString &accno)
{
    if (this->accno().compare(accno,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::accno,accno.trimmed());
        emit VendorRegistrationForm::accnoChanged();
    }
}

void VendorRegistrationForm::setMobCountryCode(const QString &countryCode)
{
    if (this->m_mobCountryCode.compare(countryCode,Qt::CaseSensitive) != 0) {
        this->m_mobCountryCode = countryCode;
        emit VendorRegistrationForm::mobCountryCodeChanged();
    }
}

void VendorRegistrationForm::setTelnoCountryCode(const QString &countryCode)
{
    if (this->m_telnoCountryCode.compare(countryCode,Qt::CaseSensitive) != 0) {
        this->m_telnoCountryCode = countryCode;
        emit VendorRegistrationForm::telnoCountryCodeChanged();
    }
}

void VendorRegistrationForm::validate()
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
        if (key.compare(FormKeys::mob,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_mobCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::telno,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_telnoCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::mob,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_mobCountryCode.isEmpty()) {
            form.insert(FormKeys::mob,this->m_mobCountryCode + string);
        }
        if (key.compare(FormKeys::telno,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_telnoCountryCode.isEmpty()) {
            form.insert(FormKeys::telno,this->m_telnoCountryCode + string);
        }
    }
    emit FormValidator::isValidForm(form);
}

void VendorRegistrationForm::qmlValidate()
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
        if (key.compare(FormKeys::mob,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_mobCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::telno,Qt::CaseSensitive) == 0 && !string.isEmpty() && this->m_telnoCountryCode.isEmpty()) {
            this->invalidValue(key,value->errors().at(2));
            return;
        }
        if (key.compare(FormKeys::mob,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_mobCountryCode.isEmpty()) {
            form.insert(FormKeys::mob,this->m_mobCountryCode + string);
        }
        if (key.compare(FormKeys::telno,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_telnoCountryCode.isEmpty()) {
            form.insert(FormKeys::telno,this->m_telnoCountryCode + string);
        }
    }
    emit FormValidator::isValidForm(form);
}
