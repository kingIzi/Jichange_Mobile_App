#include <QCoreApplication>
#include <QtTest>
#include <QFuture>
#include <QSignalSpy>
//#include "requests.h"
#include "authrequests.h"


// add necessary includes here
class login_tests : public QObject
{
    Q_OBJECT
    std::unique_ptr<AuthRequests> requests = nullptr;
public:
    login_tests();
    ~login_tests();
private slots:
    void test_login_incorrect_crudentials();
    void test_login_incorect_json();
    void test_success_login();
};

login_tests::login_tests() {
    this->requests = std::make_unique<AuthRequests>();
}

login_tests::~login_tests() {}

void login_tests::test_login_incorrect_crudentials()
{
    this->requests->clearCurrentUser();
    const QVariantMap logins = {
        qMakePair("userName","super"),
        qMakePair("password","12345678")
    };
    QSignalSpy spy(this->requests.get(),SIGNAL(loginFailed(const QString)));

    this->requests->loginUser(logins);

    QVERIFY(this->requests->getCurrentUser().empty());
    QVERIFY(!this->requests->isLoggedIn());
    QCOMPARE_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    QCOMPARE_EQ(args.at(0).toString().toLower(),QString("Username or password is incorrect").toLower());
}

void login_tests::test_login_incorect_json()
{
    this->requests->clearCurrentUser();
    const QVariantMap logins = {
        qMakePair("userName","super"),
    };
    QSignalSpy spy(this->requests.get(),SIGNAL(loginFailed(const QString)));

    this->requests->loginUser(logins);

    QVERIFY(this->requests->getCurrentUser().empty());
    QVERIFY(!this->requests->isLoggedIn());
    QCOMPARE_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    QCOMPARE_EQ(args.at(0).toString().toLower(),QString("InternalServerError").toLower());
}

void login_tests::test_success_login()
{
    this->requests->clearCurrentUser();
    const QVariantMap logins = {
        qMakePair("userName","company1"),
        qMakePair("password","12345678")
    };
    QSignalSpy spy(this->requests.get(),SIGNAL(loginSuccessfull()));

    this->requests->loginUser(logins);

    QVERIFY(!this->requests->getCurrentUser().empty());
    qDebug() << this->requests->getCurrentUser();
    QVERIFY(this->requests->isLoggedIn());
    QCOMPARE_EQ(this->requests->getCurrentUser().value("Usno").toInt(),1);
    QCOMPARE_EQ(this->requests->getCurrentUser().value("role").toString().toLower(),QString("Companys").toLower());
    QCOMPARE_EQ(spy.count(),1);
}

QTEST_MAIN(login_tests)

#include "tst_login_tests.moc"
