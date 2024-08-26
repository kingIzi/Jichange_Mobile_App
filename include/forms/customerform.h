#pragma once

#include "forms/formvalidator.h"

class CustomerForm : public FormValidator {
    Q_OBJECT
    Q_PROPERTY(QString cust_Name READ cust_Name WRITE setCust_Name NOTIFY cust_NameChanged)
    Q_PROPERTY(QString phone READ phone WRITE setPhone NOTIFY phoneChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString phoneCountryCode READ phoneCountryCode WRITE setPhoneCountryCode NOTIFY phoneCountryCodeChanged)
private:
    QString m_phoneCountryCode;
public:
    explicit CustomerForm(QObject *parent = nullptr);
    const QString cust_Name() const;
    const QString phone() const;
    const QString email() const;
    const QString& phoneCountryCode() const;
public slots:
    void setCust_Name(const QString& Cust_Name);
    void setPhone(const QString& Phone);
    void setEmail(const QString& Email);
    void setPhoneCountryCode(const QString& phoneCountryCode);
public:
    struct FormKeys {
        static constexpr const char* Cust_Name = "Cust_Name";
        static constexpr const char* Phone = "Phone";
        static constexpr const char* Email = "Email";
    };
    Q_INVOKABLE void validate() override;
    Q_INVOKABLE void qmlValidate() override;
signals:
    void cust_NameChanged();
    void phoneChanged();
    void emailChanged();
    void phoneCountryCodeChanged();
};
