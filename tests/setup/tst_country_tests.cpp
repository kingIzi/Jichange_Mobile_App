#include <QtTest>
#include <QSignalSpy>
#include <QObject>
#include "requests.h"


class country_tests : public QObject {
    Q_OBJECT
private:
    std::unique_ptr<Requests> requests = nullptr;
public:
    country_tests();
    ~country_tests();
private slots:
    void test_add_country_empty_body();
    void test_add_country_missing_required();
    void test_delete_country_sno_less_than_zero();
    void test_country_list();
};



country_tests::country_tests() :
    requests(std::make_unique<Requests>())
{

}

country_tests::~country_tests()
{

}

void country_tests::test_add_country_empty_body()
{
    const QVariantMap branch = {};
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,this->requests->prepareCountryBody(branch));
}

void country_tests::test_add_country_missing_required()
{
    const QVariantMap country = {
        qMakePair("dummy",true),
        qMakePair("sno","0"),
        qMakePair("AuditBy","1")
    };
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,this->requests->prepareCountryBody(country));
}

void country_tests::test_delete_country_sno_less_than_zero()
{
    const QVariantMap country = {
        //qMakePair("sno",9347289742),
        qMakePair("sno",-11),
        qMakePair("userid","1")
    };
    QVERIFY_THROWS_EXCEPTION(std::runtime_error,this->requests->prepareDeleteCountry(country));
}

void country_tests::test_country_list()
{
    QEventLoop loop;
    const auto reply = this->requests->makeRequest(QVariantMap(),Endpoints::Setup::GetCountries);
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    QSignalSpy spy(this->requests.get(),SIGNAL(countryListReady(const QJsonArray)));
    this->requests->parseCountryListRequest(reply);
    QCOMPARE_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    QVERIFY(args.at(0).typeId() == QMetaType::QJsonArray);
    QVERIFY(!args.at(0).toJsonArray().isEmpty());
}


QTEST_MAIN(country_tests)

#include "tst_country_tests.moc"
