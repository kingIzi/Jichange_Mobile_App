#include <QCoreApplication>
#include <QtTest>
#include <QFuture>
#include <QSignalSpy>
#include <QPair>
#include "setupbranch.h"



// add necessary includes here
class branch_tests : public QObject
{
    Q_OBJECT
    std::unique_ptr<SetupBranch> setupBranch = nullptr;
public:
    branch_tests();
    ~branch_tests();
private slots:
    void test_branch_list();
};

branch_tests::branch_tests() {
    this->setupBranch = std::make_unique<SetupBranch>();
}

branch_tests::~branch_tests() {}

void branch_tests::test_branch_list()
{
    const QVariantMap branch = {};
    QSignalSpy spy(this->setupBranch.get(),SIGNAL(branchList(const QList<Branch*>)));

    this->setupBranch->requestBranchList(branch);

    QCOMPARE_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    QVERIFY(!args.at(0).isNull());
}


QTEST_MAIN(branch_tests)

#include "tst_branch_tests.moc"
