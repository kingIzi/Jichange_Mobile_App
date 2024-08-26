#include <QCoreApplication>
#include <QtTest>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QSignalSpy>
#include <QThread>
#include <thread>
#include "requests.h"

class chatbot_tests : public QObject {
    Q_OBJECT
    std::unique_ptr<Requests> requests = nullptr;
public:
    chatbot_tests();
    ~chatbot_tests();
private slots:
    void test_text_chatbot_empty_body();
    void test_text_chatbot_missing_argument();
    void test_text_chatbot_success();
};

chatbot_tests::chatbot_tests()
{
    this->requests = std::make_unique<Requests>();
}

chatbot_tests::~chatbot_tests()
{

}

void chatbot_tests::test_text_chatbot_empty_body()
{
    const QVariantMap chat = {};
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,this->requests->prepareChatBody(chat));
}

void chatbot_tests::test_text_chatbot_missing_argument()
{
    const QVariantMap chat = {
        qMakePair("text", "How many invoices did we have last year?")
    };
    QVERIFY_THROWS_EXCEPTION(std::invalid_argument,this->requests->prepareChatBody(chat));
}

void chatbot_tests::test_text_chatbot_success()
{
    const QVariantMap chat = {
        qMakePair("userId",1),
        qMakePair("text", "How many invoices did we have last year?")
    };
    QVERIFY_THROWS_NO_EXCEPTION(this->requests->prepareChatBody(chat),std::invalid_argument(""));
    const auto body = this->requests->prepareChatBody(chat);
    QEventLoop loop;
    const auto reply = this->requests->makeRequest(body,"/chat",QList<QPair<QString,QString>>(),"http://127.0.0.1:5000");
    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
    std::thread waiter([reply](){
        using namespace std::literals::chrono_literals;
        while (reply->isFinished()) {
            qDebug() << "Hello world";
            std::this_thread::sleep_for(1s);
        }
    });
    loop.exec();
    waiter.join();
    QSignalSpy spy(this->requests.get(),SIGNAL(chatReply(const QJsonObject)));
    this->requests->parseTextChatbotRequest(reply);
    QCOMPARE_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    QVERIFY(args.at(0).typeId() == QMetaType::QJsonObject);
    QVERIFY(!args.at(0).toJsonObject().isEmpty());
}

//QTEST_MAIN(chatbot_tests)

#include "tst_chatbot_tests.moc"
