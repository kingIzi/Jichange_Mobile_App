#include <QCoreApplication>
#include <QtTest>
#include <QFuture>
#include <QSignalSpy>
#include <QPair>
#include "requests.h"



// add necessary includes here
class setup_tests : public QObject
{
    Q_OBJECT
    std::unique_ptr<Requests> requests = nullptr;
public:
    setup_tests();
    ~setup_tests();
private slots:

};

setup_tests::setup_tests() {
    this->requests = std::make_unique<Requests>();
}

setup_tests::~setup_tests() {}

//QTEST_MAIN(setup_tests)

#include "tst_setup_tests.moc"
