#pragma once
#include "forms/formvalidator.h"

class CompanyUserForm : public FormValidator
{
    Q_OBJECT
    Q_PROPERTY(QString chname READ chname WRITE setChname NOTIFY chnameChanged)
    Q_PROPERTY(QString auname READ auname WRITE setAuname NOTIFY aunameChanged)
    Q_PROPERTY(QString mob READ mob WRITE setMob NOTIFY mobChanged)
    Q_PROPERTY(QString mail READ mail WRITE setMail NOTIFY mailChanged)
    Q_PROPERTY(QString uname READ uname WRITE setUname NOTIFY unameChanged)
    Q_PROPERTY(long long int sno READ sno WRITE setSno NOTIFY snoChanged)
    Q_PROPERTY(long long int pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(long long int userid READ userid WRITE setUserid NOTIFY useridChanged)
    Q_PROPERTY(long long int compid READ compid WRITE setCompid NOTIFY compidChanged)
    Q_PROPERTY(QString mobCountryCode READ mobCountryCode WRITE setMobCountryCode NOTIFY mobCountryCodeChanged)
public:
    struct FormKeys
    {
        static constexpr const char* chname = "chname";
        static constexpr const char* auname = "auname";
        static constexpr const char* mob = "mob";
        static constexpr const char* mail = "mail";
        static constexpr const char* uname = "uname";
        static constexpr const char* sno = "sno";
        static constexpr const char* pos = "pos";
        static constexpr const char* userid = "userid";
        static constexpr const char* compid = "compid";
    };
private:
    QString m_mobCountryCode;
public:
    explicit CompanyUserForm(QObject *parent = nullptr);
    const QString chname() const;
    const QString auname() const;
    const QString mob() const;
    const QString mail() const;
    const QString uname() const;
    const long long int sno() const;
    const long long int pos() const;
    const long long int userid() const;
    const long long int compid() const;
    const QString& mobCountryCode() const;
public:
    Q_INVOKABLE void validate() override;
public slots:
    void setChname(const QString& chname);
    void setAuname(const QString& auname);
    void setMob(const QString& mob);
    void setMail(const QString& mail);
    void setUname(const QString& uname);
    void setSno(const long long int& sno);
    void setPos(const long long int& pos);
    void setUserid(const long long int& userid);
    void setCompid(const long long int& compid);
    void setMobCountryCode(const QString& mobCountryCode);
signals:
    void chnameChanged();
    void aunameChanged();
    void mobChanged();
    void mailChanged();
    void unameChanged();
    void snoChanged();
    void posChanged();
    void useridChanged();
    void compidChanged();
    void mobCountryCodeChanged();
};

