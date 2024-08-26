#pragma once
#include <QObject>
#include <QString>
#include <QVariantMap>
#include <QVariantList>
#include <QValidator>
#include <QList>
#include <QStringList>
#include <QQmlListReference>
#include <QVariant>

class Validator : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QValidator* validator READ validator WRITE setValidator NOTIFY validatorChanged)
    Q_PROPERTY(QStringList errors READ errors WRITE setErrors NOTIFY errorsChanged)
    Q_PROPERTY(bool required READ required WRITE setRequired NOTIFY requiredChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
private:
    QString m_name;
    QValidator* m_validator;
    QStringList m_errors;
    bool m_required;
    QVariant m_value;
public:
    explicit Validator(QObject *parent = nullptr) :
        QObject{parent},
        m_name(""),
        m_validator(nullptr),
        m_errors({}),
        m_required(false),
        m_value()
    {}
//    explicit Validator(const QString& name,QValidator* validator,const QStringList& errors,const bool required = false,QObject *parent = nullptr) :
//        QObject{parent},
//        m_name(name),
//        m_validator(validator),
//        m_errors(errors),
//        m_required(required)
//    {}
    explicit Validator(const QString& name,QValidator* validator,const QStringList& errors,const bool required = false,const QVariant& value = QVariant(),QObject *parent = nullptr) :
        QObject{parent},
        m_name(name),
        m_validator(validator),
        m_errors(errors),
        m_required(required),
        m_value(value)
    {}
public:
    const QString& name() const {
        return this->m_name;
    }
    QValidator* validator() const {
        return this->m_validator;
    }
    const QStringList& errors() const {
        return this->m_errors;
    }
    const bool& required() const {
        return this->m_required;
    }
    const QVariant& value() const {
        return this->m_value;
    }
public slots:
    void setName(const QString& name) {
        if (this->m_name.compare(name,Qt::CaseSensitive) != 0) {
            this->m_name = name;
            emit Validator::nameChanged();
        }
    }
    void setValidator(QValidator* validator) {
        if (this->m_validator != validator) {
            this->m_validator = validator;
            emit Validator::validatorChanged();
        }
    }
    void setErrors(const QStringList& errors) {
        if (this->m_errors != errors) {
            this->m_errors = errors;
            emit Validator::errorsChanged();
        }
    }
    void setRequired(const bool& required) {
        if (this->m_required != required) {
            this->m_required = required;
            emit Validator::requiredChanged();
        }
    }
    void setValue(const QVariant& value) {
        this->m_value = value;
        emit Validator::valueChanged();
    }
signals:
    void nameChanged();
    void validatorChanged();
    void errorsChanged();
    void requiredChanged();
    void valueChanged();
};

class FormValidator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<Validator*> validators READ validators WRITE setValidators NOTIFY validatorsChanged)
    Q_PROPERTY(QQmlListReference validatorListReference READ validatorListReference WRITE setValidatorListReference NOTIFY validatorListReferenceChanged)
private:
    QVariantMap form;
    QList<Validator*> m_validators;
    const QStringList m_requiredSet;
    QQmlListReference m_validatorListReference;
private:
public:
    explicit FormValidator(QObject *parent = nullptr);
    explicit FormValidator(const QStringList& requiredSet, QObject *parent = nullptr);
    const QVariantMap& getForm() const;
    QVariantMap& getModifiableForm();
    const QList<Validator*>& validators() const;
    QList<Validator*>& getModifiableValidators();
    const QStringList& getRequiredSet() const;
    void invalidValue(const QString& key,const QString& message);
    QQmlListReference validatorListReference() const;
    const QList<Validator*> getValidators() const;
    const QList<Validator*> getValidators(const QQmlListReference& leftRef) const;
public:
    Q_INVOKABLE virtual void validate();
    Q_INVOKABLE virtual void qmlValidate();
public slots:
    void setValidators(const QList<Validator*>& validators);
    void setValidatorListReference(QQmlListReference listRef);
signals:
    void validatorsChanged();
    void isInvalidForm(const QString);
    void isValidForm(const QVariantMap);
    void unexpectedError(const QString);
    void validatorListReferenceChanged();
};

