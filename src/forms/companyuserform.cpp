#include "forms/companyuserform.h"
#include <QRegularExpression>
#include <QStringList>

CompanyUserForm::CompanyUserForm(QObject *parent)
    : FormValidator{{FormKeys::userid,FormKeys::compid,FormKeys::sno},parent}
{

}

const QString CompanyUserForm::chname() const
{
    return this->getForm().value(FormKeys::chname).toString();
}

const QString CompanyUserForm::auname() const
{
    return this->getForm().value(FormKeys::auname).toString();
}

const QString CompanyUserForm::mob() const
{
    return this->getForm().value(FormKeys::mob).toString();
}

const QString CompanyUserForm::mail() const
{
    return this->getForm().value(FormKeys::mail).toString();
}

const QString CompanyUserForm::uname() const
{
    return this->getForm().value(FormKeys::uname).toString();
}

const long long int CompanyUserForm::sno() const
{
    return static_cast<unsigned long long int>(this->getForm().value(FormKeys::sno).toInt());
}

const long long int CompanyUserForm::pos() const
{
    return static_cast<unsigned long long int>(this->getForm().value(FormKeys::pos).toInt());
}

const long long int CompanyUserForm::userid() const
{
    return static_cast<unsigned long long int>(this->getForm().value(FormKeys::userid).toInt());
}

const long long int CompanyUserForm::compid() const
{
    return static_cast<unsigned long long int>(this->getForm().value(FormKeys::compid).toInt());
}

const QString &CompanyUserForm::mobCountryCode() const
{
    return this->m_mobCountryCode;
}

void CompanyUserForm::validate()
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
        if (key.compare(FormKeys::mob,Qt::CaseSensitive) == 0 && !string.isEmpty() && !this->m_mobCountryCode.isEmpty()) {
            form.insert(FormKeys::mob,this->m_mobCountryCode + string);
        }
    }
    emit FormValidator::isValidForm(form);
}

void CompanyUserForm::setChname(const QString &chname)
{
    if (this->chname().compare(chname,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::chname,chname.trimmed());
        emit CompanyUserForm::chnameChanged();
    }

}

void CompanyUserForm::setAuname(const QString &auname)
{
    if (this->auname().compare(auname,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::auname,auname.trimmed());
        emit CompanyUserForm::aunameChanged();
    }
}

void CompanyUserForm::setMob(const QString &mob)
{
    if (this->mob().compare(mob,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::mob,mob.trimmed());
        emit CompanyUserForm::mobChanged();
    }
}

void CompanyUserForm::setMail(const QString &mail)
{
    if (this->mail().compare(mail,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::mail,mail.trimmed());
        emit CompanyUserForm::mailChanged();
    }
}

void CompanyUserForm::setUname(const QString &uname)
{
    if (this->uname().compare(uname,Qt::CaseInsensitive) != 0) {
        this->getModifiableForm().insert(FormKeys::uname,uname.trimmed());
        emit CompanyUserForm::unameChanged();
    }
}

void CompanyUserForm::setSno(const long long int &sno)
{
    this->getModifiableForm().insert(FormKeys::sno,sno);
    emit CompanyUserForm::snoChanged();
}

void CompanyUserForm::setPos(const long long int &pos)
{
    this->getModifiableForm().insert(FormKeys::pos,pos);
    emit CompanyUserForm::posChanged();
}

void CompanyUserForm::setUserid(const long long int &userid)
{
    this->getModifiableForm().insert(FormKeys::userid,userid);
    emit CompanyUserForm::useridChanged();
}

void CompanyUserForm::setCompid(const long long int &compid)
{
    this->getModifiableForm().insert(FormKeys::compid,compid);
    emit CompanyUserForm::compidChanged();
}

void CompanyUserForm::setMobCountryCode(const QString &mobCountryCode)
{
    if (this->m_mobCountryCode.compare(mobCountryCode,Qt::CaseSensitive) != 0) {
        this->m_mobCountryCode = mobCountryCode;
        emit CompanyUserForm::mobCountryCodeChanged();
    }
}
