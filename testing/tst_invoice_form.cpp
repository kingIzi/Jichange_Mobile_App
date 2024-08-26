#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include <exception>
#include <QRegularExpression>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>
#include <QVariantList>
#include "forms/invoiceform.h"

using namespace testing;

TEST(test_invoice_form,missing_invno)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(BIZ|BSL\\/).*"));
    const auto errors = (QStringList) {QObject::tr("Please provide an invoice number."),QObject::tr("Invoice numbers must start with 'BIZ' or 'BSL/'.")};
    const auto key = InvoiceForm::FormKeys::invno;
    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_invno_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(BIZ|BSL\\/).*"));
    const auto errors = (QStringList) {QObject::tr("Please provide an invoice number."),QObject::tr("Invoice numbers must start with 'BIZ' or 'BSL/'.")};
    const auto invno = "";
    const auto key = InvoiceForm::FormKeys::invno;
    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,invno));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_invno_ill_formed)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(BIZ|BSL\\/).*"));
    const auto errors = (QStringList) {QObject::tr("Please provide an invoice number."),QObject::tr("Invoice numbers must start with 'BIZ' or 'BSL/'.")};
    const auto invno = "K813NGAD";
    const auto key = InvoiceForm::FormKeys::invno;
    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,invno));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_invno)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(BIZ|BSL\\/).*"));
    const auto errors = (QStringList) {QObject::tr("Please provide an invoice number."),QObject::tr("Invoice numbers must start with 'BIZ' or 'BSL/'.")};
    const auto invno = "BSL/2024/08/01";
    const auto key = InvoiceForm::FormKeys::invno;
    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,invno));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString().toLower(),QString(invno).toLower());
}

TEST(test_invoice_form,missing_date)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the invoice date."),QObject::tr("Invalid invoice date")};
    const auto key = InvoiceForm::FormKeys::date;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_date_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the invoice date."),QObject::tr("Invalid invoice date")};
    const auto key = InvoiceForm::FormKeys::date;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_date_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "6/5/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the invoice date."),QObject::tr("Invalid invoice date")};
    const auto key = InvoiceForm::FormKeys::date;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_date_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "06/05/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the invoice date."),QObject::tr("Invalid invoice date")};
    const auto key = InvoiceForm::FormKeys::date;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),date);
}

TEST(test_invoice_form,missing_edate)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid due date.")};
    const auto key = InvoiceForm::FormKeys::edate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_edate_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid due date.")};
    const auto key = InvoiceForm::FormKeys::edate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_edate_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "6/5/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid due date.")};
    const auto key = InvoiceForm::FormKeys::edate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_edate_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "06/05/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid due date.")};
    const auto key = InvoiceForm::FormKeys::edate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),date);
}

TEST(test_invoice_form,missing_iedate)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid expiry date.")};
    const auto key = InvoiceForm::FormKeys::iedate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_iedate_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid expiry date.")};
    const auto key = InvoiceForm::FormKeys::iedate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_iedate_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "6/5/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid expiry date.")};
    const auto key = InvoiceForm::FormKeys::iedate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_iedate_format)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto date = "06/05/2024";
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(0[1-9]|[12][0-9]|3[01])\\/(0[1-9]|1[0-2])\\/(?!0000)\\d{4}$"));
    const auto errors = (QStringList) {QObject::tr("Please specify the due date."),QObject::tr("Invalid expiry date.")};
    const auto key = InvoiceForm::FormKeys::iedate;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,date));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),date);
}

TEST(test_invoice_form,missing_customer_name)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QIntValidator>(1,99999);
    const auto errors = (QStringList) {QObject::tr("Please select a customer."),QObject::tr("You must select a customer.")};
    const auto key = InvoiceForm::FormKeys::chus;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,empty_customer_name)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QIntValidator>(1,99999);
    const auto errors = (QStringList) {QObject::tr("Please select a customer."),QObject::tr("You must select a customer.")};
    const auto key = InvoiceForm::FormKeys::chus;
    const auto customer = "";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,customer));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,valid_customer_name)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QIntValidator>(1,99999);
    const auto errors = (QStringList) {QObject::tr("Please select a customer."),QObject::tr("You must select a customer.")};
    const auto key = InvoiceForm::FormKeys::chus;
    const auto customer = "12";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,customer));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),customer);
}

TEST(test_invoice_form,missing_ptype)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Flexible|Fixed)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a payment type."),QObject::tr("Opps! Something went wrong! Contact support or try again.")};
    const auto key = InvoiceForm::FormKeys::ptype;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_ptype_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Flexible|Fixed)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a payment type."),QObject::tr("Opps! Something went wrong! Contact support or try again.")};
    const auto key = InvoiceForm::FormKeys::ptype;
    const auto paymentType = "";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,paymentType));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_ptype)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Flexible|Fixed)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a payment type."),QObject::tr("Opps! Something went wrong! Contact support or try again.")};
    const auto key = InvoiceForm::FormKeys::ptype;
    const auto paymentType = "flexible";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,paymentType));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_ptype)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Flexible|Fixed)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a payment type."),QObject::tr("Opps! Something went wrong! Contact support or try again.")};
    const auto key = InvoiceForm::FormKeys::ptype;
    const auto paymentType = "Flexible";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,paymentType));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),paymentType);
}

TEST(test_invoice_form,missing_ccode)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(CAD|USD|TZS)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a currency."),QObject::tr("Invalid currency selected.")};
    const auto key = InvoiceForm::FormKeys::ccode;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_ccode_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(CAD|USD|TZS)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a currency."),QObject::tr("Invalid currency selected.")};
    const auto key = InvoiceForm::FormKeys::ccode;
    const auto ccode = "";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,ccode));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_ccode_unknown_currency)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(CAD|USD|TZS)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a currency."),QObject::tr("Invalid currency selected.")};
    const auto key = InvoiceForm::FormKeys::ccode;
    const auto ccode = "CDF";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,ccode));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(1).toLower());
}

TEST(test_invoice_form,valid_ccode)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(CAD|USD|TZS)$"));
    const auto errors = (QStringList) {QObject::tr("Please select a currency."),QObject::tr("Invalid currency selected.")};
    const auto key = InvoiceForm::FormKeys::ccode;
    const auto ccode = "TZS";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true,ccode));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),ccode);
}

TEST(test_invoice_form,missing_invRemark)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("Please provide the a remark."),QObject::tr("")};
    const auto key = InvoiceForm::FormKeys::Inv_remark;

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,false));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_TRUE(args.at(0).toMap().isEmpty());
}

TEST(test_invoice_form,valid_invRemark_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("Please provide the a remark."),QObject::tr("")};
    const auto key = InvoiceForm::FormKeys::Inv_remark;
    const auto inv_remark = "";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,false,inv_remark));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),inv_remark);
}

TEST(test_invoice_form,valid_invRemark)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("Please provide the a remark."),QObject::tr("")};
    const auto key = InvoiceForm::FormKeys::Inv_remark;
    const auto inv_remark = "good";

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,false,inv_remark));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value(key).toString(),inv_remark);
}

TEST(test_invoice_form,missing_item_details)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);

    const auto key = InvoiceForm::FormKeys::details;
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("You must add at least one item."),QObject::tr("")};


    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),errors.at(0).toLower());
}

TEST(test_invoice_form,missing_item_detail_description)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);
    const auto key = InvoiceForm::FormKeys::details;

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("You must add at least one item."),QObject::tr("")};
    const auto item_description_errors = (QStringList) {QObject::tr("Please fill."),QObject::tr("")};
    const auto item_unitPrice_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_qty_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_total_amount_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_remarks_errors = (QStringList) {QObject::tr(""),QObject::tr("")};

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    const auto item_desc_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_desc(new Validator(InvoiceForm::Details::item_description,item_desc_validator.get(),item_description_errors,true));

    const auto unit_price = 5000.00;
    const auto item_unitPrice_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> item_unitPrice(new Validator(InvoiceForm::Details::item_unit_price,item_unitPrice_validator.get(),item_unitPrice_errors,true,unit_price));

    const auto qty = 3;
    const auto item_qty_validator = std::make_unique<QIntValidator>(1,5000);
    QScopedPointer<Validator> item_qty(new Validator(InvoiceForm::Details::item_qty,item_qty_validator.get(),item_qty_errors,true,qty));

    const auto amount = unit_price * qty;
    const auto total_amount_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> total_amount(new Validator(InvoiceForm::Details::item_total_amount,total_amount_validator.get(),item_total_amount_errors,true,amount));

    const auto remarks = "good";
    const auto remarks_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_remarks(new Validator(InvoiceForm::Details::remarks,remarks_validator.get(),item_remarks_errors,false,remarks));

    QList<Validator*> list; list.reserve(4);
    list.append(item_desc.get());
    list.append(item_unitPrice.get());
    list.append(item_qty.get());
    list.append(item_remarks.get());
    list.append(total_amount.get());

    form->getTempDetails().append(list);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),item_description_errors.at(0).toLower());
}

TEST(test_invoice_form,invalid_item_detail_description_is_empty)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);
    const auto key = InvoiceForm::FormKeys::details;

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("You must add at least one item."),QObject::tr("")};
    const auto item_description_errors = (QStringList) {QObject::tr("Please fill."),QObject::tr("")};
    const auto item_unitPrice_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_total_amount_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_qty_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_remarks_errors = (QStringList) {QObject::tr(""),QObject::tr("")};

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    const auto description = "";
    const auto item_desc_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_desc(new Validator(InvoiceForm::Details::item_description,item_desc_validator.get(),item_description_errors,true,description));

    const auto unit_price = 5000.00;
    const auto item_unitPrice_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> item_unitPrice(new Validator(InvoiceForm::Details::item_unit_price,item_unitPrice_validator.get(),item_unitPrice_errors,true,unit_price));

    const auto qty = 3;
    const auto item_qty_validator = std::make_unique<QIntValidator>(1,5000);
    QScopedPointer<Validator> item_qty(new Validator(InvoiceForm::Details::item_qty,item_qty_validator.get(),item_qty_errors,true,qty));

    const auto amount = unit_price * qty;
    const auto total_amount_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> total_amount(new Validator(InvoiceForm::Details::item_total_amount,total_amount_validator.get(),item_total_amount_errors,true,amount));

    const auto remarks = "good";
    const auto remarks_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_remarks(new Validator(InvoiceForm::Details::remarks,remarks_validator.get(),item_remarks_errors,false,remarks));

    QList<Validator*> list; list.reserve(4);
    list.append(item_desc.get());
    list.append(item_unitPrice.get());
    list.append(item_qty.get());
    list.append(item_remarks.get());
    list.append(total_amount.get());

    form->getTempDetails().append(list);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    EXPECT_EQ(validSpy.count(),0);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),item_description_errors.at(0).toLower());
}

TEST(test_invoice_form,valid_item_detail_description)
{
    const auto form = std::make_unique<InvoiceForm>();
    QSignalSpy spy(form.get(),&InvoiceForm::isInvalidForm);
    QSignalSpy validSpy(form.get(),&InvoiceForm::isValidForm);
    const auto key = InvoiceForm::FormKeys::details;

    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    const auto errors = (QStringList) {QObject::tr("You must add at least one item."),QObject::tr("")};
    const auto item_description_errors = (QStringList) {QObject::tr("Please fill."),QObject::tr("")};
    const auto item_unitPrice_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_qty_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_total_amount_errors = (QStringList) {QObject::tr("Please specify."),QObject::tr("Cannot be 0")};
    const auto item_remarks_errors = (QStringList) {QObject::tr(""),QObject::tr("")};

    QScopedPointer<Validator> valid(new Validator(key,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(valid.get());

    const auto description = "T-Shirt";
    const auto item_desc_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_desc(new Validator(InvoiceForm::Details::item_description,item_desc_validator.get(),item_description_errors,true,description));

    const auto unit_price = 5000.00;
    const auto item_unitPrice_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> item_unitPrice(new Validator(InvoiceForm::Details::item_unit_price,item_unitPrice_validator.get(),item_unitPrice_errors,true,unit_price));

    const auto qty = 3;
    const auto item_qty_validator = std::make_unique<QIntValidator>(1,5000);
    QScopedPointer<Validator> item_qty(new Validator(InvoiceForm::Details::item_qty,item_qty_validator.get(),item_qty_errors,true,qty));

    const auto amount = unit_price * qty;
    const auto total_amount_validator = std::make_unique<QDoubleValidator>(1.10,90000000.00,2);
    QScopedPointer<Validator> total_amount(new Validator(InvoiceForm::Details::item_total_amount,total_amount_validator.get(),item_total_amount_errors,true,amount));

    const auto remarks = "good";
    const auto remarks_validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression());
    QScopedPointer<Validator> item_remarks(new Validator(InvoiceForm::Details::remarks,remarks_validator.get(),item_remarks_errors,false,remarks));

    QList<Validator*> list;
    list.reserve(4);
    list.append(item_desc.get());
    list.append(item_unitPrice.get());
    list.append(item_qty.get());
    list.append(item_remarks.get());
    list.append(total_amount.get());

    form->getTempDetails().append(list);

    form->validate();

    EXPECT_EQ(spy.count(),0);
    EXPECT_EQ(validSpy.count(),1);
    const auto args = validSpy.takeFirst();
    EXPECT_FALSE(args.at(0).toMap().isEmpty());
    const auto details = args.at(0).toMap().value(key).toList();
    EXPECT_EQ(1,details.length());
    for (const auto& detail : details) {
        const auto desc = detail.toMap().value(InvoiceForm::Details::item_description).toString();
        const auto price = detail.toMap().value(InvoiceForm::Details::item_unit_price).toDouble();
        const auto quantity = detail.toMap().value(InvoiceForm::Details::item_qty).toDouble();
        const auto invRemark = detail.toMap().value(InvoiceForm::Details::remarks).toString();
        const auto total = detail.toMap().value(InvoiceForm::Details::item_total_amount).toDouble();

        EXPECT_EQ(description,desc);
        EXPECT_EQ(unit_price,price);
        EXPECT_EQ(quantity,qty);
        EXPECT_EQ(invRemark,remarks);
        EXPECT_EQ(total,amount);
    }
}

