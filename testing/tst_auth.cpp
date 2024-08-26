
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include "requests/authrequests.h"

using namespace testing;

struct AuthTests : testing::Test {
    QCoreApplication app;
    std::unique_ptr<AuthRequests> authRequests = nullptr;
    AuthTests(int argc = 0,char* argv[] = {}) :
        app(argc,argv),
        authRequests(std::make_unique<AuthRequests>())
    {
        this->authRequests->clearCurrentUser();
    }
};

TEST_F(AuthTests, incorrect_crudentials)
{
    const QVariantMap logins = {
        qMakePair("userName","super"),
        qMakePair("password","12345678")
    };
    QSignalSpy spy(this->authRequests.get(),SIGNAL(loginFailed(const QString)));
    QSignalSpy spyWorking(this->authRequests.get(),SIGNAL(isWorkingChanged()));

    this->authRequests->loginUser(logins);
    QCoreApplication::processEvents();

    QVERIFY(this->authRequests->getCurrentUser().empty());
    EXPECT_TRUE(this->authRequests->getCurrentUser().empty());
    EXPECT_FALSE(this->authRequests->isLoggedIn());
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Username or password is incorrect").toLower());
}

TEST_F(AuthTests, incorrect_payload)
{
    const QVariantMap logins = {
        qMakePair("userName","super"),
    };
    QSignalSpy spy(this->authRequests.get(),SIGNAL(internalServerError(const QString)));
    QSignalSpy spyWorking(this->authRequests.get(),SIGNAL(isWorkingChanged()));

    this->authRequests->loginUser(logins);
    QCoreApplication::processEvents();

    EXPECT_TRUE(this->authRequests->getCurrentUser().empty());
    EXPECT_FALSE(this->authRequests->isLoggedIn());
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("An unexpected error occurred, please try again or contact support.").toLower());
}

TEST_F(AuthTests, correct_credentials)
{
    const QVariantMap logins = {
        qMakePair("userName","company1"),
        qMakePair("password","12345678")
    };
    QSignalSpy spy(this->authRequests.get(),SIGNAL(loginSuccessfull()));
    QSignalSpy spyWorking(this->authRequests.get(),SIGNAL(isWorkingChanged()));

    this->authRequests->loginUser(logins);
    QCoreApplication::processEvents();

    EXPECT_FALSE(this->authRequests->getCurrentUser().empty());
    EXPECT_TRUE(this->authRequests->isLoggedIn());
    EXPECT_EQ(this->authRequests->getCurrentUser().value("Usno").toInt(),1);
    EXPECT_EQ(this->authRequests->getCurrentUser().value("role").toString().toLower(),QString("Companys").toLower());
    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
}

