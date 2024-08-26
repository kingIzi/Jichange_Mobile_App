#pragma once
#include <QObject>
#include <QList>
#include <memory>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>

class Branch : public QObject
{
    Q_OBJECT
private:
    QString name;
    QString location;
    QString status;
    int sno;
    int branchSno;
    QString auditBy;
    QDateTime auditDate;
public:
    struct Keys {
        static constexpr const char* Name = "Name";
        static constexpr const char* Location = "Location";
        static constexpr const char* Status = "Status";
        static constexpr const char* Sno = "Sno";
        static constexpr const char* Branch_Sno = "Branch_Sno";
        static constexpr const char* AuditBy = "AuditBy";
        static constexpr const char* Audit_Date = "Audit_Date";
    };
public:
    explicit Branch(QObject *parent = nullptr);
    explicit Branch(const QJsonObject& branch,QObject *parent = nullptr);
    static const QList<Branch*> createList(const QJsonArray& branchList);
public:
    const bool operator==(Branch const* branch) const {
        const auto branchSnoMatch = branch->branchSno == this->branchSno;
        const auto snoMatch = branch->sno == this->sno;
        const auto nameMatch = branch->name.compare(this->name,Qt::CaseInsensitive) == 0;
        const auto locationMatch = branch->location.compare(this->location,Qt::CaseInsensitive) == 0;
        const auto statusMatch = branch->status.compare(this->status,Qt::CaseInsensitive) == 0;
        const auto auditByMatch = branch->auditBy.compare(this->auditBy,Qt::CaseInsensitive) == 0;
        const auto auditDateMatch = branch->auditDate == this->auditDate;
        return branchSnoMatch && snoMatch && nameMatch && locationMatch && statusMatch && auditByMatch && auditDateMatch;
    }
    QString getName() const;
    void setName(const QString &newName);

    QString getLocation() const;
    void setLocation(const QString &newLocation);

    QString getStatus() const;
    void setStatus(const QString &newStatus);

    int getSno() const;
    void setSno(int newSno);

    int getBranchSno() const;
    void setBranchSno(int newBranchSno);

    QString getAuditBy() const;
    void setAuditBy(const QString &newAuditBy);

    QDateTime getAuditDate() const;
    void setAuditDate(const QDateTime &newAuditDate);

signals:
};

