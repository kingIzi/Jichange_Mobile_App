#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include <exception>
#include "requests/companyusersrequests.h"
#include "requests/authrequests.h"


using namespace testing;

struct CompanyUsersRegistrationTests : testing::Test {
    QCoreApplication app;
    std::unique_ptr<CompanyUsersRequests> companyUsersRequests = nullptr;
    CompanyUsersRegistrationTests(int argc = 0,char* argv[] = {}) :
        app(argc,argv),
        companyUsersRequests(std::make_unique<CompanyUsersRequests>())
    {}
};

struct CompanyUsersPageTests : CompanyUsersRegistrationTests{
    CompanyUsersPageTests(int argc = 0,char* argv[] = {}) :
        CompanyUsersRegistrationTests(argc,argv),
        authRequests(std::make_unique<AuthRequests>())
    {
        const auto body = (QVariantMap) {
                qMakePair("userName","company1"),
                qMakePair("password","12345678")
        };
        this->authRequests->loginUser(body);
        QCoreApplication::processEvents();
    }
    std::unique_ptr<AuthRequests> authRequests = nullptr;
};

TEST_F(CompanyUsersRegistrationTests,check_account_number_invalid_number)
{
    const QVariantMap body = {std::make_pair("acc","12349")};
    QSignalSpy spy(this->companyUsersRequests.get(),SIGNAL(checkAccountExists(const bool)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestCheckAccount(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).toBool());
}

TEST_F(CompanyUsersRegistrationTests,check_account_number_valid_number)
{
    const QVariantMap body = {std::make_pair("acc","1234")};
    QSignalSpy spy(this->companyUsersRequests.get(),SIGNAL(checkAccountExists(const bool)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestCheckAccount(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_TRUE(args.at(0).toBool());
}

TEST_F(CompanyUsersRegistrationTests,addCompanyL_exists_account_number)
{
    const QVariantMap body = {
        std::make_pair("compsno", "0"),
        std::make_pair("compname", "Izidore ltd"),
        std::make_pair("mob", "255765553524"),
        std::make_pair("branch", "21"),
        std::make_pair("check_status", "No"),
        std::make_pair("fax", ""),
        std::make_pair("pbox", ""),
        std::make_pair("addr", ""),
        std::make_pair("rsno", "0"),
        std::make_pair("dsno", "0"),
        std::make_pair("wsno", "0"),
        std::make_pair("tin", ""),
        std::make_pair("vat", ""),
        std::make_pair("dname", ""),
        std::make_pair("telno", ""),
        std::make_pair("email", ""),
        std::make_pair("dummy", true),
        std::make_pair("accno", "1234")
    };
    QSignalSpy failedReply(this->companyUsersRequests.get(),SIGNAL(addCompanyLFailed(const QString)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestAddCompanyL(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(failedReply.count(),1);
    const auto args = failedReply.takeFirst();
    qDebug() << args.at(0).toString().toLower();
    EXPECT_EQ(spyWorking.count(),2);
    EXPECT_EQ(args.at(0).toString().toLower(),QString("the account number you have entered is already in use").toLower());
}

TEST_F(CompanyUsersRegistrationTests,invalid_server_error)
{
    const QVariantMap body = {
        std::make_pair("compsno", "0"),
        std::make_pair("compname", "Mfumu ltd"),
        std::make_pair("mob", "255765553524"),
        std::make_pair("branch", "21"),
        std::make_pair("check_status", "No"),
        std::make_pair("fax", ""),
        std::make_pair("pbox", ""),
        std::make_pair("addr", ""),
        std::make_pair("rsno", "0"),
        std::make_pair("dsno", "0"),
        std::make_pair("wsno", "0"),
        std::make_pair("tin", ""),
        std::make_pair("vat", ""),
        std::make_pair("dname", ""),
        std::make_pair("telno", ""),
        std::make_pair("email", ""),
        std::make_pair("dummy", true),
        std::make_pair("accno", "02J2314330000")
    };
    const auto req = static_cast<Requests*>(this->companyUsersRequests.get());
    QSignalSpy internalErrorSpy(req,SIGNAL(internalServerError(const QString)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestAddCompanyL(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(internalErrorSpy.count(),1);
    const auto args = internalErrorSpy.takeFirst();
    EXPECT_EQ(spyWorking.count(),2);
    EXPECT_EQ(args.at(0).toString().toLower(),QString("An unexpected error occurred, please try again or contact support.").toLower());
}

TEST_F(CompanyUsersRegistrationTests,addCompanyL_exists_company)
{
    const QVariantMap body = {
        std::make_pair("compsno", "0"),
        std::make_pair("compname", "Izidore ltd"),
        std::make_pair("mob", "255765553524"),
        std::make_pair("branch", "21"),
        std::make_pair("check_status", "No"),
        std::make_pair("fax", ""),
        std::make_pair("pbox", ""),
        std::make_pair("addr", ""),
        std::make_pair("rsno", "0"),
        std::make_pair("dsno", "0"),
        std::make_pair("wsno", "0"),
        std::make_pair("tin", ""),
        std::make_pair("vat", ""),
        std::make_pair("dname", ""),
        std::make_pair("telno", ""),
        std::make_pair("email", ""),
        std::make_pair("dummy", true),
        std::make_pair("accno", "02J2314330000")
    };
    QSignalSpy failedReply(this->companyUsersRequests.get(),SIGNAL(addCompanyLFailed(const QString)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestAddCompanyL(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(failedReply.count(),1);
    const auto args = failedReply.takeFirst();
    EXPECT_EQ(spyWorking.count(),2);
    EXPECT_EQ(args.at(0).toString().toLower(),QString("This Company already exists").toLower());
}

TEST_F(CompanyUsersPageTests,company_users_list_valid_institution_id)
{
    const auto user = this->authRequests->getCurrentUser();
    EXPECT_FALSE(user.isEmpty());
    EXPECT_EQ(user.value(Keys::Login::InstID).toInt(),67);

    const QVariantMap body = {std::make_pair("compid",user.value(Keys::Login::InstID).toInt())};

    QSignalSpy spy(this->companyUsersRequests.get(),&CompanyUsersRequests::companyUsersList);
    QSignalSpy spyWorking(this->companyUsersRequests.get(),&CompanyUsersRequests::isWorkingChanged);

    this->companyUsersRequests->requestCompanyUsersList(body);
    QCoreApplication::processEvents();

    EXPECT_TRUE(spy.isValid());
    EXPECT_EQ(spyWorking.count(),2);
    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).isNull());
    EXPECT_FALSE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(CompanyUsersPageTests,company_users_list_invalid_institution_id)
{
    const auto user = this->authRequests->getCurrentUser();
    EXPECT_FALSE(user.isEmpty());

    const QVariantMap body = {std::make_pair("compid","-1")};

    QSignalSpy spy(this->companyUsersRequests.get(),SIGNAL(companyUsersList(const QJsonArray)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestCompanyUsersList(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).isNull());
    EXPECT_TRUE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(CompanyUsersPageTests,company_users_list_empty_body)
{
    const auto user = this->authRequests->getCurrentUser();
    EXPECT_FALSE(user.isEmpty());

    const QVariantMap body = {};

    QSignalSpy spy(this->companyUsersRequests.get(),SIGNAL(companyUsersList(const QJsonArray)));
    QSignalSpy spyWorking(this->companyUsersRequests.get(),SIGNAL(isWorkingChanged()));

    this->companyUsersRequests->requestCompanyUsersList(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).isNull());
    EXPECT_TRUE(args.at(0).toJsonArray().isEmpty());
}

