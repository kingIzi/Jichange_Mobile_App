#ifndef COMPANYUSER_H
#define COMPANYUSER_H

#include <QObject>

class CompanyUser : public QObject
{
    Q_OBJECT
public:
    explicit CompanyUser(QObject *parent = nullptr);

signals:

};

#endif // COMPANYUSER_H
