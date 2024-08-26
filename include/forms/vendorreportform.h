#pragma once
#include "forms/formvalidator.h"

class VendorReportForm : public FormValidator
{
    Q_OBJECT
    Q_PROPERTY(long long int Comp READ Comp WRITE setComp NOTIFY CompChanged)
    Q_PROPERTY(long long int reg READ reg WRITE setReg NOTIFY regChanged)
    Q_PROPERTY(long long int dist READ dist WRITE setDist NOTIFY distChanged)
public:
    struct FormKeys
    {
        static constexpr const char* Comp = "Comp";
        static constexpr const char* reg = "reg";
        static constexpr const char* dist = "dist";
    };
public:
    explicit VendorReportForm(QObject *parent = nullptr);
    const long long int Comp() const;
    const long long int reg() const;
    const long long int dist() const;
public slots:
    void setComp(const long long int Comp);
    void setReg(const long long int reg);
    void setDist(const long long int dist);
signals:
    void CompChanged();
    void regChanged();
    void distChanged();
};
