#include "forms/formvalidator.h"
#include <QVariant>
#include <QMetaType>

const QList<Validator *> FormValidator::getValidators() const
{
    QList<Validator*> validatorList;
    validatorList.reserve(this->m_validatorListReference.count());
    for (int i = 0; i < this->m_validatorListReference.count(); i++) {
        const auto ref = this->m_validatorListReference.at(i);
        const auto validator = qobject_cast<Validator*>(ref);
        if (validator) {
            validatorList.emplaceBack(validator);
        }
    }
    return validatorList;
}

const QList<Validator *> FormValidator::getValidators(const QQmlListReference &leftRef) const
{
    QList<Validator*> validatorList;
    validatorList.reserve(leftRef.count());
    for (int i = 0; i < leftRef.count(); i++) {
        const auto ref = leftRef.at(i);
        const auto validator = qobject_cast<Validator*>(ref);
        if (validator) {
            validatorList.emplaceBack(validator);
        }
    }
    return validatorList;
}

FormValidator::FormValidator(QObject *parent)
    : QObject{parent},
      form(),
      m_validators(),
      m_requiredSet()
{

}

FormValidator::FormValidator(const QStringList &requiredSet, QObject *parent) :
    QObject{parent},
    form(),
    m_validators(),
    m_requiredSet(requiredSet)
{

}

const QVariantMap &FormValidator::getForm() const
{
    return this->form;
}

QVariantMap &FormValidator::getModifiableForm()
{
    return this->form;
}

const QList<Validator*> &FormValidator::validators() const
{
    return this->m_validators;
}

QList<Validator*> &FormValidator::getModifiableValidators()
{
    return this->m_validators;
}

const QStringList &FormValidator::getRequiredSet() const
{
    return this->m_requiredSet;
}

void FormValidator::invalidValue(const QString &key, const QString &message)
{
    if (this->m_requiredSet.contains(key)) {
        emit FormValidator::unexpectedError(message);
    }
    else {
        emit FormValidator::isInvalidForm(message);
    }
}

QQmlListReference FormValidator::validatorListReference() const
{
    return this->m_validatorListReference;
}

void FormValidator::validate()
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
    }
    emit FormValidator::isValidForm(form);
}

void FormValidator::qmlValidate()
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
    }
    emit FormValidator::isValidForm(form);
}

void FormValidator::setValidators(const QList<Validator*> &validators)
{
    if (this->m_validators != validators) {
        this->m_validators = validators;
        emit FormValidator::validatorsChanged();
    }
}

void FormValidator::setValidatorListReference(QQmlListReference listRef)
{
    this->m_validatorListReference = listRef;
    emit FormValidator::validatorListReferenceChanged();
}
