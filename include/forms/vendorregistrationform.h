#pragma once
#include "forms/formvalidator.h"

class VendorRegistrationForm : public FormValidator
{
    Q_OBJECT
    Q_PROPERTY(int compsno READ compsno WRITE setCompsno NOTIFY compsnoChanged)
    Q_PROPERTY(QString compname READ compname WRITE setCompname NOTIFY compnameChanged)
    Q_PROPERTY(QString mob READ mob WRITE setMob NOTIFY mobChanged)
    Q_PROPERTY(int branch READ branch WRITE setBranch NOTIFY branchChanged)
    Q_PROPERTY(QString check_status READ check_status WRITE setCheck_status NOTIFY check_statusChanged)
    Q_PROPERTY(QString fax READ fax WRITE setFax NOTIFY faxChanged)
    Q_PROPERTY(QString pbox READ pbox WRITE setPbox NOTIFY pboxChanged)
    Q_PROPERTY(QString addr READ addr WRITE setAddr NOTIFY addrChanged)
    Q_PROPERTY(int rsno READ rsno WRITE setRsno NOTIFY rsnoChanged)
    Q_PROPERTY(int dsno READ dsno WRITE setDsno NOTIFY dsnoChanged)
    Q_PROPERTY(int wsno READ wsno WRITE setWsno NOTIFY wsnoChanged)
    Q_PROPERTY(QString tin READ tin WRITE setTin NOTIFY tinChanged)
    Q_PROPERTY(QString vat READ vat WRITE setVat NOTIFY vatChanged)
    Q_PROPERTY(QString dname READ dname WRITE setDname NOTIFY dnameChanged)
    Q_PROPERTY(QString telno READ telno WRITE setTelno NOTIFY telnoChanged)
    Q_PROPERTY(QString email READ email WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(bool dummy READ dummy WRITE setDummy NOTIFY dummyChanged)
    Q_PROPERTY(QString accno READ accno WRITE setAccno NOTIFY accnoChanged)
    Q_PROPERTY(QString mobCountryCode READ mobCountryCode WRITE setMobCountryCode NOTIFY mobCountryCodeChanged)
    Q_PROPERTY(QString telnoCountryCode READ telnoCountryCode WRITE setTelnoCountryCode NOTIFY telnoCountryCodeChanged)
private:
    QString m_mobCountryCode;
    QString m_telnoCountryCode;
public:
    explicit VendorRegistrationForm(QObject *parent = nullptr);
    const int compsno() const;
    const QString compname() const;
    const QString mob() const;
    const int branch() const;
    const QString check_status() const;
    const QString fax() const;
    const QString pbox() const;
    const QString addr() const;
    const int rsno() const;
    const int dsno() const;
    const int wsno() const;
    const QString tin() const;
    const QString vat() const;
    const QString dname() const;
    const QString telno() const;
    const QString email() const;
    const bool dummy() const;
    const QString accno() const;
    const QString& mobCountryCode() const;
    const QString& telnoCountryCode() const;
public slots:
    void setCompsno(const int& compsno);
    void setCompname(const QString& compname);
    void setMob(const QString& mob);
    void setBranch(const int& branch);
    void setCheck_status(const QString& check_status);
    void setFax(const QString& fax);
    void setPbox(const QString& pbox);
    void setAddr(const QString& addr);
    void setRsno(const int& rsno);
    void setDsno(const int& dsno);
    void setWsno(const int& wsno);
    void setTin(const QString& tin);
    void setVat(const QString& vat);
    void setDname(const QString& dname);
    void setTelno(const QString& telno);
    void setEmail(const QString& email);
    void setDummy(const bool& dummy);
    void setAccno(const QString& accno);
    void setMobCountryCode(const QString& countryCode);
    void setTelnoCountryCode(const QString& countryCode);
public:
    struct FormKeys {
        static constexpr const char* compsno = "compsno";
        static constexpr const char* compname = "compname";
        static constexpr const char* mob = "mob";
        static constexpr const char* branch = "branch";
        static constexpr const char* check_status = "check_status";
        static constexpr const char* fax = "fax";
        static constexpr const char* pbox = "pbox";
        static constexpr const char* addr = "addr";
        static constexpr const char* rsno = "rsno";
        static constexpr const char* dsno = "dsno";
        static constexpr const char* wsno = "wsno";
        static constexpr const char* tin = "tin";
        static constexpr const char* vat = "vat";
        static constexpr const char* dname = "dname";
        static constexpr const char* telno = "telno";
        static constexpr const char* email = "email";
        static constexpr const char* dummy = "dummy";
        static constexpr const char* accno = "accno";
    };
    Q_INVOKABLE void validate() override;
    Q_INVOKABLE void qmlValidate() override;
signals:
    void compsnoChanged();
    void compnameChanged();
    void mobChanged();
    void branchChanged();
    void check_statusChanged();
    void faxChanged();
    void pboxChanged();
    void addrChanged();
    void rsnoChanged();
    void dsnoChanged();
    void wsnoChanged();
    void tinChanged();
    void vatChanged();
    void dnameChanged();
    void telnoChanged();
    void emailChanged();
    void dummyChanged();
    void accnoChanged();
    void mobCountryCodeChanged();
    void telnoCountryCodeChanged();
};


