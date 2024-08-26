#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include "requests/setupbranch.h"

using namespace testing;

struct SetupBranchTests : testing::Test {
    QCoreApplication app;
    std::unique_ptr<SetupBranch> setupBranch = nullptr;
    SetupBranchTests(int argc = 0,char* argv[] = {}) :
        app(argc,argv),
        setupBranch(std::make_unique<SetupBranch>())
    {}
};

TEST_F(SetupBranchTests,branch_list)
{
    const QVariantMap branch = {};
    QSignalSpy spy(this->setupBranch.get(),SIGNAL(branchList(const QList<Branch*>)));
    QSignalSpy spyWorking(this->setupBranch.get(),SIGNAL(isWorkingChanged()));

    this->setupBranch->requestBranchList(branch);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).isNull());
}
