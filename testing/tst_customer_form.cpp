#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include <exception>
#include <QRegularExpression>
#include <QScopedPointer>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>
#include "forms/customerform.h"

using namespace testing;

TEST(test_customer_form,missing_custname)
{
    const auto form = std::make_unique<CustomerForm>();
    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto errors = (QStringList) {QObject::tr("Please provide the customer name."),QObject::tr("Customer name must contain at least one first and last name, separated by a space.")};
    QScopedPointer<Validator> cust_name(new Validator(CustomerForm::FormKeys::Cust_Name,validator.get(),errors,true));
    form->getModifiableValidators().emplaceBack(cust_name.get());

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please provide the customer name.").toLower());
}

TEST(test_customer_form,invalid_custname_is_empty)
{
    const auto form = std::make_unique<CustomerForm>();
    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Cust_Name);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please provide the customer name."),QObject::tr("Customer name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    form->setCust_Name("");
    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please provide the customer name.").toLower());
}

TEST(test_customer_form,invalid_custname_ill_formed)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Cust_Name);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please provide the customer name."),QObject::tr("Customer name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setCust_Name(":JAfhs krafas");
    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Customer name must contain at least one first and last name, separated by a space.").toLower());
}

TEST(test_customer_form,valid_custname)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Cust_Name);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please provide the customer name."),QObject::tr("Customer name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setCust_Name("JAfhs krafas");
    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_customer_form,missing_mobile_number)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}

TEST(test_customer_form,invalid_mobile_number_start_with_zero)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setPhone("0745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_customer_form,invalid_mobile_number_start_with_country_code)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setPhone("+255745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_customer_form,invalid_mobile_number_is_empty)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setPhone(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}

TEST(test_customer_form,invalid_mobile_number_no_country_code_selected)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setPhone("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select the mobile number's country code.").toLower());
}



TEST(test_customer_form,valid_mobile_number)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Phone);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setPhoneCountryCode("243");
    form->setPhone("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_customer_form,missing_mail)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Email);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide an email address.").toLower());
}

TEST(test_customer_form,invalid_mail_ill_formed)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Email);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setEmail("vita@.com"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid email address.").toLower());
}

TEST(test_customer_form,invalid_mail_is_empty)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Email);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setEmail(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide an email address.").toLower());
}

TEST(test_customer_form,valid_mail)
{
    const auto form = std::make_unique<CustomerForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CustomerForm::FormKeys::Email);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CustomerForm::isInvalidForm);

    form->setEmail("vita@vita.sk"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_customer_form,valid_form_data)
{
    const auto form = std::make_unique<CustomerForm>();
    QSignalSpy spy(form.get(),&CustomerForm::isValidForm);

    const auto Cust_NameValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    QScopedPointer<Validator> Cust_Name(new Validator(CustomerForm::FormKeys::Cust_Name,Cust_NameValidator.get(),{QObject::tr("Please provide the customer name."),QObject::tr("Customer name must contain at least one first and last name, separated by a space.")},true));

    const auto PhoneValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    QScopedPointer<Validator> Phone(new Validator(CustomerForm::FormKeys::Phone,PhoneValidator.get(),{QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")},true));

    const auto EmailValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    QScopedPointer<Validator> Email(new Validator(CustomerForm::FormKeys::Email,EmailValidator.get(),{QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")},true));

    form->getModifiableValidators().emplaceBack(Cust_Name.get());
    form->getModifiableValidators().emplaceBack(Phone.get());
    form->getModifiableValidators().emplaceBack(Email.get());

    form->setCust_Name("Izidore ltd");
    form->setPhone("766534433");
    form->setPhoneCountryCode("256");
    form->setEmail("duck@example.com");

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value("Phone"),"256766534433");
    EXPECT_EQ(args.at(0).toMap().keys().length(),3);
}
