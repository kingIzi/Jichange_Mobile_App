#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include <memory>
#include "requests/invoicerequests.h"

using namespace testing;

struct InvoiceTests : public ::testing::Test {
    QCoreApplication app;
    std::unique_ptr<InvoiceRequests> invoiceRequests = nullptr;
    InvoiceTests(int argc = 0,char* argv[] = {}) :
        app(argc,argv),
        invoiceRequests(std::make_unique<InvoiceRequests>())
    {}
};

TEST_F(InvoiceTests,request_customer_names_empty_body)
{
    const QVariantMap body = {};
    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::customerNames);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestCustomerNames(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_TRUE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(InvoiceTests,request_customer_names_invalid_compid)
{
    const QVariantMap body = {std::make_pair("compid",1)};
    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::customerNames);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestCustomerNames(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_TRUE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(InvoiceTests,request_customer_names_valid_compid)
{
    const QVariantMap body = {std::make_pair("compid",67)};
    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::customerNames);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestCustomerNames(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(InvoiceTests,request_get_currencies)
{
    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::currencies);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestGetCurrency();
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).toJsonArray().isEmpty());
}

TEST_F(InvoiceTests,request_invoice_formData)
{
    const QVariantMap customerNamesBody = {std::make_pair("compid",67)};
    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::invoiceFormData);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestInvoiceFormData(customerNamesBody);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_FALSE(args.at(0).toJsonArray().isEmpty());
    EXPECT_FALSE(args.at(1).toJsonArray().isEmpty());
}

TEST_F(InvoiceTests,add_invoice_missing_neccessary_keys)
{
    const QVariantMap body = {};

    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::internalServerError);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestAddInvoice(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("An unexpected error occurred, please try again or contact support.").toLower());
}


TEST_F(InvoiceTests,add_invoice_exists_invoice)
{
    const QVariantMap body = {
        std::make_pair("user_id", 1),
        std::make_pair("compid", "67"),
        std::make_pair("invno", "BIZ1239"),
        std::make_pair("auname", "313,000.00"),
        std::make_pair("date", "04/25/2024"),
        std::make_pair("edate", "04/30/2024"),
        std::make_pair("iedate", "05/05/2024"),
        std::make_pair("ptype", "Flexible"),
        std::make_pair("chus", "10109"),
        std::make_pair("comno", 0),
        std::make_pair("ccode", "TZS"),
        std::make_pair("ctype", "0"),
        std::make_pair("cino", "0"),
        std::make_pair("twvat", 0),
        std::make_pair("vtamou", 0),
        std::make_pair("total", "313,000.00"),
        std::make_pair("Inv_remark", "good"),
        std::make_pair("lastrow", 0),
        std::make_pair("sno", "0"),
        std::make_pair("warrenty", ""),
        std::make_pair("goods_status", ""),
        std::make_pair("delivery_status", ""),
        std::make_pair("details", QVariantList {
            QVariantMap {
                std::make_pair("item_description", "device"),
                std::make_pair("item_qty", "3"),
                std::make_pair("item_unit_price", 23000),
                std::make_pair("item_total_amount", 69000),
                std::make_pair("remarks", "good")
            },
            QVariantMap {
                std::make_pair("item_description", "Fiscal"),
                std::make_pair("item_qty", "4"),
                std::make_pair("item_unit_price", 43000),
                std::make_pair("item_total_amount", 172000),
                std::make_pair("remarks", "best")
            },
            QVariantMap {
                std::make_pair("item_description", "Singa"),
                std::make_pair("item_qty", "3"),
                std::make_pair("item_unit_price", "24000"),
                std::make_pair("item_total_amount", "72000.00"),
                std::make_pair("remarks", "better")
            }
        })
    };

    QSignalSpy spy(this->invoiceRequests.get(),&InvoiceRequests::addInvoiceFailed);
    QSignalSpy spyWorking(this->invoiceRequests.get(),&InvoiceRequests::isWorkingChanged);

    this->invoiceRequests->requestAddInvoice(body);
    QCoreApplication::processEvents();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(spyWorking.count(),2);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("This invoice number already exists.").toLower());
}


