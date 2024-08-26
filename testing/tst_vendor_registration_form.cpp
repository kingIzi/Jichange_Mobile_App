#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include "forms/vendorregistrationform.h"
#include <QRegularExpression>
#include <QScopedPointer>

using namespace testing;

TEST(test_vendor_registration_form,missing_compsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again.").toLower());
}

TEST(test_vendor_registration_form,invalid_compsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setCompsno(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_vendor_registration_form,valid_compsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(false); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setCompsno(0); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_compname)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z0-9]+(?: [A-Za-z0-9]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a vendor name."),QObject::tr("Vendor name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a vendor name.").toLower());
}

TEST(test_vendor_registration_form,invalid_compname_is_empty)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>();
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a vendor name."),QObject::tr("Vendor name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setCompname(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a vendor name.").toLower());
}

TEST(test_vendor_registration_form,valid_compname)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>();
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::compname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a vendor name."),QObject::tr("Vendor name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setCompname("Izidore ltd"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_mobile_number)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}

TEST(test_vendor_registration_form,invalid_mobile_number_start_with_zero)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setMob("0745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_vendor_registration_form,invalid_mobile_number_start_with_country_code)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setMob("+255745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_vendor_registration_form,invalid_mobile_number_is_empty)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setMob(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}


TEST(test_vendor_registration_form,invalid_mobile_number_no_country_code_selected)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setMob("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select the mobile number's country code.").toLower());
}

TEST(test_vendor_registration_form,valid_mobile_number)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setMobCountryCode("255");
    form->setMob("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_branch)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::branch);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a branch."),QObject::tr("The branch you have selected is invalid.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, select a branch.").toLower());
}

TEST(test_vendor_registration_form,invalid_branch)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::branch);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a branch."),QObject::tr("The branch you have selected is invalid.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setBranch(-1); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("The branch you have selected is invalid.").toLower());
}


TEST(test_vendor_registration_form,valid_branch)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::branch);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a branch."),QObject::tr("The branch you have selected is invalid.")});
    posValidator->setRequired(true); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setBranch(21); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_account_number)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(01|02)(J|\\d)\\d{10}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::accno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide the account number."),QObject::tr("The account number you have entered is incorrect.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide the account number.").toLower());
}

TEST(test_vendor_registration_form,invalid_account_number_ill_formed)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(01|02)(J|\\d)\\d{10}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::accno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide the account number."),QObject::tr("The account number you have entered is incorrect.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setAccno("0745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("The account number you have entered is incorrect.").toLower());
}

TEST(test_vendor_registration_form,invalid_account_number_is_empty)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(01|02)(J|\\d)\\d{10}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::accno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide the account number."),QObject::tr("The account number you have entered is incorrect.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setAccno(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide the account number.").toLower());
}


TEST(test_vendor_registration_form,valid_account_number)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(01|02)(J|\\d)\\d{10}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::accno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide the account number."),QObject::tr("The account number you have entered is incorrect.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setAccno("0152452360000"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_check_status)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Yes|No)$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::check_status);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, specify the need for an approval check."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, specify the need for an approval check.").toLower());
}

TEST(test_vendor_registration_form,invalid_check_status_is_empty)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Yes|No)$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::check_status);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, specify the need for an approval check."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setCheck_status("");

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, specify the need for an approval check.").toLower());
}

TEST(test_vendor_registration_form,invalid_check_status_incorrect_input)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Yes|No)$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::check_status);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, specify the need for an approval check."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setCheck_status("no");

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}

TEST(test_vendor_registration_form,valid_check_status)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Yes|No)$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::check_status);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, specify the need for an approval check."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&VendorRegistrationForm::isInvalidForm);

    form->setCheck_status("Yes");

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_rsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::rsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a region."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select a region.").toLower());
}

TEST(test_vendor_registration_form,invalid_rsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::rsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a region."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setRsno(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_vendor_registration_form,valid_rsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::rsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a region."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(false); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setRsno(0); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_dsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::dsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a district."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select a district.").toLower());
}

TEST(test_vendor_registration_form,invalid_dsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::dsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a district."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setDsno(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_vendor_registration_form,valid_dsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::dsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a district."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(false); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setDsno(0); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,missing_wsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::wsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a ward."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select a ward.").toLower());
}

TEST(test_vendor_registration_form,invalid_wsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::wsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a ward."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setWsno(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_vendor_registration_form,valid_wsno)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(VendorRegistrationForm::FormKeys::wsno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please select a ward."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(false); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&VendorRegistrationForm::unexpectedError);

    form->setWsno(0); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_vendor_registration_form,valid_form_data)
{
    const auto form = std::make_unique<VendorRegistrationForm>();
    QSignalSpy spy(form.get(),&VendorRegistrationForm::isValidForm);

    const auto compsnoValidator = std::make_unique<QIntValidator>(0,9000000);
    QScopedPointer<Validator> compsno(new Validator(VendorRegistrationForm::FormKeys::compsno,compsnoValidator.get(),{QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));

    const auto compnameValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z0-9]+(?: [A-Za-z0-9]+)+$"));
    QScopedPointer<Validator> compname(new Validator(VendorRegistrationForm::FormKeys::compname,compnameValidator.get(),{QObject::tr("Please, provide a vendor name."),QObject::tr("Vendor name must contain at least one first and last name, separated by a space.")},true));

    const auto mobValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    QScopedPointer<Validator> mob(new Validator(VendorRegistrationForm::FormKeys::mob,mobValidator.get(),{QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")},true));

    const auto branchValidator = std::make_unique<QIntValidator>(1,9000000);
    QScopedPointer<Validator> branch(new Validator(VendorRegistrationForm::FormKeys::branch,branchValidator.get(),{QObject::tr("Please, select a branch."),QObject::tr("The branch you have selected is invalid.")},true));

    const auto accnoValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(01|02)(J|\\d)\\d{10}$"));
    QScopedPointer<Validator> accno(new Validator(VendorRegistrationForm::FormKeys::accno,accnoValidator.get(),{QObject::tr("Please, provide the account number."),QObject::tr("The account number you have entered is incorrect.")},true));

    const auto checkStatusValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^(Yes|No)$"));
    QScopedPointer<Validator> checkStatus(new Validator(VendorRegistrationForm::FormKeys::check_status,checkStatusValidator.get(),{QObject::tr("Please, specify the need for an approval check."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},true));

    const auto rsnoValidator = std::make_unique<QIntValidator>(0,9000000);
    QScopedPointer<Validator> rsno(new Validator(VendorRegistrationForm::FormKeys::rsno,rsnoValidator.get(),{QObject::tr("Please select a region."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));

    const auto dsnoValidator = std::make_unique<QIntValidator>(0,9000000);
    QScopedPointer<Validator> dsno(new Validator(VendorRegistrationForm::FormKeys::dsno,dsnoValidator.get(),{QObject::tr("Please select a district."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));

    const auto wsnoValidator = std::make_unique<QIntValidator>(0,9000000);
    QScopedPointer<Validator> wsno(new Validator(VendorRegistrationForm::FormKeys::wsno,wsnoValidator.get(),{QObject::tr("Please select a ward."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));


    form->getModifiableValidators().emplaceBack(compsno.get());
    form->getModifiableValidators().emplaceBack(compname.get());
    form->getModifiableValidators().emplaceBack(mob.get());
    form->getModifiableValidators().emplaceBack(branch.get());
    form->getModifiableValidators().emplaceBack(accno.get());
    form->getModifiableValidators().emplaceBack(checkStatus.get());
    form->getModifiableValidators().emplaceBack(rsno.get());
    form->getModifiableValidators().emplaceBack(dsno.get());
    form->getModifiableValidators().emplaceBack(wsno.get());

    form->setCompsno(0);
    form->setCompname("Kabisa ltd");
    form->setMob("742046709");
    form->setMobCountryCode("255");
    form->setBranch(21);
    form->setAccno("0152314330000");
    form->setCheck_status("No");
    form->setDummy(true);
    form->setRsno(0);
    form->setDsno(0);
    form->setWsno(0);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value("mob"),"255742046709");
    EXPECT_EQ(args.at(0).toMap().keys().length(),10);
}

//{
//    "compsno": "0",
//    "compname": "Kabisa ltd",
//    "mob": "255742046709",
//    "branch": "21",
//    "check_status": "No",
//    "fax": "",
//    "pbox": "",
//    "addr": "",
//    "rsno": "0",
//    "dsno": "0",
//    "wsno": "0",
//    "tin": "",
//    "vat": "",
//    "dname": "",
//    "telno": "",
//    "email": "",
//    "dummy": true,
//    "accno": "0152314330000"
//}

