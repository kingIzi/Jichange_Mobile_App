#pragma once
#include <QObject>
#include "requests.h"
//#include "entities/companyuser.h"


class CompanyUsersRequests : public Requests
{
    Q_OBJECT
private:
    struct Endpoints {
        static constexpr const char* companyUsersList = "/api/CompanyUsers/GetCompanyUserss";
        static constexpr const char* checkAccount = "/api/company/CheckAccount";
        static constexpr const char* addCompanyL = "/api/Company/AddCompanyBankL";
    };
private:
    void parseCheckAccount(QNetworkReply * reply);
    void parseAddCompanyL(QNetworkReply * reply);
    void parseCompanyUsersList(QNetworkReply* reply);
public:
    explicit CompanyUsersRequests(Requests *parent = nullptr);
    Q_INVOKABLE void requestCompanyUsersList(const QVariantMap& body);
    Q_INVOKABLE void requestCheckAccount(const QVariantMap& body);
    Q_INVOKABLE void requestAddCompanyL(const QVariantMap& body);
signals:
    void companyUsersList(const QJsonArray);
    void checkAccountExists(const bool);
    void addCompanyLResponse(const long long companySno);
    void addCompanyLFailed(const QString);
};

