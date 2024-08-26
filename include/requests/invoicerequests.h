#pragma once

#include "requests/requests.h"

class InvoiceRequests : public Requests
{
    Q_OBJECT
private:
    struct Endpoints {
        static constexpr const char* GetCustomersS = "/api/Invoice/GetCustomersS";
        static constexpr const char* GetCurrency = "/api/Invoice/GetCurrency";
        static constexpr const char* AddInvoice = "/api/Invoice/AddInvoice";
    };
private:
    const QJsonArray parseCustomerNames(QNetworkReply* reply);
    const QJsonArray parseGetCurrencies(QNetworkReply* reply);
    const int parseAddInvoice(QNetworkReply* reply);
public:
    explicit InvoiceRequests(Requests *parent = nullptr);
    Q_INVOKABLE void requestCustomerNames(const QVariantMap& body);
    Q_INVOKABLE void requestGetCurrency();
    Q_INVOKABLE void requestInvoiceFormData(const QVariantMap& customerNamesBody);
    Q_INVOKABLE void requestAddInvoice(const QVariantMap& body);
signals:
    void customerNames(const QJsonArray);
    void currencies(const QJsonArray);
    void invoiceFormData(const QJsonArray,const QJsonArray);
    void addedInvoice(const int);
    void addInvoiceFailed(const QString);
};

