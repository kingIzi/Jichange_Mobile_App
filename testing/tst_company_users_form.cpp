#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSignalSpy>
#include <QCoreApplication>
#include <exception>
#include "forms/companyuserform.h"
#include <QRegularExpression>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegularExpressionValidator>

TEST(test_company_form_properties,pos)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setPos(0);
    EXPECT_EQ(form->pos(),0);
}

TEST(test_company_form_properties,auname_space_start)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setAuname(" Chance the rapper");
    EXPECT_EQ(form->auname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,auname_space_end)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setAuname("Chance the rapper ");
    EXPECT_EQ(form->auname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,auname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setAuname("Chance the rapper");
    EXPECT_EQ(form->auname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,uname_space_start)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setUname(" Chance the rapper");
    EXPECT_EQ(form->uname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,uname_space_end)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setUname("Chance the rapper ");
    EXPECT_EQ(form->uname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,uname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setUname("Chance the rapper");
    EXPECT_EQ(form->uname().toLower(),QString("chance the rapper"));
}

TEST(test_company_form_properties,mob_space_start)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMob(" 742036609");
    EXPECT_EQ(form->mob().toLower(),QString("742036609"));
}

TEST(test_company_form_properties,mob_space_end)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMob("742036609 ");
    EXPECT_EQ(form->mob().toLower(),QString("742036609"));
}

TEST(test_company_form_properties,mob)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMob("742036609");
    EXPECT_EQ(form->mob().toLower(),QString("742036609"));
}

TEST(test_company_form_properties,mail_space_start)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMail(" scottt.izi@gmail.com");
    EXPECT_EQ(form->mail().toLower(),QString("scottt.izi@gmail.com"));
}

TEST(test_company_form_properties,mail_space_end)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMail("scottt.izi@gmail.com ");
    EXPECT_EQ(form->mail().toLower(),QString("scottt.izi@gmail.com"));
}

TEST(test_company_form_properties,mail)
{
    const auto form = std::make_unique<CompanyUserForm>();
    form->setMail("scottt.izi@gmail.com");
    EXPECT_EQ(form->mail().toLower(),QString("scottt.izi@gmail.com"));
}

TEST(test_company_form,missing_pos)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::pos);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a user role."),QObject::tr("The role you have selected is invalid. Please try again.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, select a user role.").toLower());
}

TEST(test_company_form,invalid_pos)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setRequired(true);
    posValidator->setName(CompanyUserForm::FormKeys::pos);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a user role."),QObject::tr("The role you have selected is invalid. Please try again.")});
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setPos(-1); //testing variable

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("The role you have selected is invalid. Please try again.").toLower());
}

TEST(test_company_form,invalid_pos_negative_value)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setRequired(true);
    posValidator->setName(CompanyUserForm::FormKeys::pos);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a user role."),QObject::tr("The role you have selected is invalid. Please try again.")});
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setPos(-10); //testing variable

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("The role you have selected is invalid. Please try again.").toLower());
}

TEST(test_company_form,valid_pos)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setRequired(true);
    posValidator->setName(CompanyUserForm::FormKeys::pos);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, select a user role."),QObject::tr("The role you have selected is invalid. Please try again.")});
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setPos(2); //testing variable

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_auname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[a-zA-Z0-9.]+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::auname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a user name."),QObject::tr("Please provide an alphanumeric username value.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a user name.").toLower());
}

TEST(test_company_form,invalid_auname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[a-zA-Z0-9.]+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::auname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a user name."),QObject::tr("User name may be alphanumeric with no spaces but (.) is allowed.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setAuname("Kimpa Vita"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("User name may be alphanumeric with no spaces but (.) is allowed.").toLower());
}


TEST(test_company_form,invalid_auname_is_empty)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[a-zA-Z0-9.]+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::auname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a user name."),QObject::tr("User name may be alphanumeric with no spaces but (.) is allowed.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setAuname(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a user name.").toLower());
}

TEST(test_company_form,valid_auname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[a-zA-Z0-9.]+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::auname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a user name."),QObject::tr("User name may be alphanumeric with no spaces but (.) is allowed.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setAuname("Kimpa.Vita"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_uname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::uname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a full name."),QObject::tr("Full name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a full name.").toLower());
}

TEST(test_company_form,invalid_uname_with_numbers)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::uname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a full name."),QObject::tr("Full name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setUname("Dona Beatriz12"); //testing


    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Full name must contain at least one first and last name, separated by a space.").toLower());
}

TEST(test_company_form,invalid_uname_is_empty)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::uname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a full name."),QObject::tr("Full name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setUname(""); //testing


    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a full name.").toLower());
}


TEST(test_company_form,valid_uname)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::uname);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a full name."),QObject::tr("Full name must contain at least one first and last name, separated by a space.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setUname("Dona Beatriz"); //testing


    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_mobile_number)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}

TEST(test_company_form,invalid_mobile_number_start_with_zero)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMob("0745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_company_form,invalid_mobile_number_start_with_country_code)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMob("+255745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid mobile number without leading zeros or country code.").toLower());
}

TEST(test_company_form,invalid_mobile_number_is_empty)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMob(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide a mobile number.").toLower());
}

TEST(test_company_form,invalid_mobile_number_no_country_code_selected)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMob("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please select the mobile number's country code.").toLower());
}



TEST(test_company_form,valid_mobile_number)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mob);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMobCountryCode("243");
    form->setMob("745988875"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_mail)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mail);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide an email address.").toLower());
}

TEST(test_company_form,invalid_mail_ill_formed)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mail);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMail("vita@.com"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please enter a valid email address.").toLower());
}

TEST(test_company_form,invalid_mail_is_empty)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mail);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMail(""); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Please, provide an email address.").toLower());
}

TEST(test_company_form,valid_mail)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::mail);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::isInvalidForm);

    form->setMail("vita@vita.sk"); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_userid)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::userid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again.").toLower());
}

TEST(test_company_form,invalid_userid_is_less_than_zero)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::userid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setUserid(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}

TEST(test_company_form,valid_userid)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::userid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());

    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setUserid(2492); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_sno)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::sno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again.").toLower());
}

TEST(test_company_form,invalid_sno)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::sno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setSno(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_company_form,valid_sno)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(0,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::sno);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(false);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setSno(0); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,missing_compid)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::compid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong.").toLower());
}

TEST(test_company_form,invalid_compid)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::compid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true);
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setCompid(-10); //testing

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toString().toLower(),QString("Opps! Something went wrong! Please try again or contact support.").toLower());
}


TEST(test_company_form,valid_compid)
{
    const auto form = std::make_unique<CompanyUserForm>();
    const auto validator = std::make_unique<QIntValidator>(1,9000000);
    const auto posValidator = std::make_unique<Validator>();
    posValidator->setName(CompanyUserForm::FormKeys::compid);
    posValidator->setValidator(validator.get());
    posValidator->setErrors({QObject::tr("Opps! Something went wrong."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")});
    posValidator->setRequired(true); //bug
    form->getModifiableValidators().emplaceBack(posValidator.get());


    QSignalSpy spy(form.get(),&CompanyUserForm::unexpectedError);

    form->setCompid(67); //testing

    form->validate();

    EXPECT_EQ(spy.count(),0);
}

TEST(test_company_form,valid_form_data)
{
    const auto form = std::make_unique<CompanyUserForm>();
    QSignalSpy spy(form.get(),&CompanyUserForm::isValidForm);

    const auto posValidator = std::make_unique<QIntValidator>(1,9000000);
    QScopedPointer<Validator> pos(new Validator(CompanyUserForm::FormKeys::pos,posValidator.get(),{QObject::tr("Please, select a user role."),QObject::tr("The role you have selected is invalid. Please try again.")},true));

    const auto aunameValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[a-zA-Z0-9.]+$"));
    QScopedPointer<Validator> auname(new Validator(CompanyUserForm::FormKeys::auname,aunameValidator.get(),{QObject::tr("Please, provide a user name."),QObject::tr("User name may be alphanumeric with no spaces but (.) is allowed.")},true));

    const auto unameValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[A-Za-z]+(?: [A-Za-z]+)+$"));
    QScopedPointer<Validator> uname(new Validator(CompanyUserForm::FormKeys::uname,unameValidator.get(),{QObject::tr("Please, provide a full name."),QObject::tr("Full name must contain at least one first and last name, separated by a space.")},true));

    const auto mobValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("^[67]\\d{8}$"));
    QScopedPointer<Validator> mob(new Validator(CompanyUserForm::FormKeys::mob,mobValidator.get(),{QObject::tr("Please, provide a mobile number."),QObject::tr("Please enter a valid mobile number without leading zeros or country code."),QObject::tr("Please select the mobile number's country code.")},true));

    const auto mailValidator = std::make_unique<QRegularExpressionValidator>(QRegularExpression("\\w+([-+.']\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"));
    QScopedPointer<Validator> mail(new Validator(CompanyUserForm::FormKeys::mail,mailValidator.get(),{QObject::tr("Please, provide an email address."),QObject::tr("Please enter a valid email address")},true));

    const auto useridValidator =std::make_unique<QIntValidator>(1,9000000);
    QScopedPointer<Validator> userid(new Validator(CompanyUserForm::FormKeys::userid,useridValidator.get(),{QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},true));

    const auto snoValidator =std::make_unique<QIntValidator>(1,9000000);
    QScopedPointer<Validator> sno(new Validator(CompanyUserForm::FormKeys::sno,snoValidator.get(),{QObject::tr("Opps! Something went wrong! Please try again."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));

    const auto compidValidator = std::make_unique<QIntValidator>(1,9000000);
    QScopedPointer<Validator> compid(new Validator(CompanyUserForm::FormKeys::compid,compidValidator.get(),{QObject::tr("Opps! Something went wrong."),QObject::tr("Opps! Something went wrong! Please try again or contact support.")},false));

    form->getModifiableValidators().emplaceBack(pos.get());
    form->getModifiableValidators().emplaceBack(auname.get());
    form->getModifiableValidators().emplaceBack(mob.get());
    form->getModifiableValidators().emplaceBack(mail.get());
    form->getModifiableValidators().emplaceBack(userid.get());
    form->getModifiableValidators().emplaceBack(sno.get());
    form->getModifiableValidators().emplaceBack(compid.get());

    form->setPos(21);
    form->setAuname("USernaem1");
    form->setUname("Hell Gate");
    form->setMob("765434323");
    form->setMobCountryCode("243");
    form->setMail("scot.sd@gmail.com");
    form->setUserid(2);
    form->setSno(0);
    form->setCompid(67);

    form->validate();

    EXPECT_EQ(spy.count(),1);
    const auto args = spy.takeFirst();
    EXPECT_EQ(args.at(0).toMap().value("mob"),"243765434323");
    EXPECT_EQ(args.at(0).toMap().keys().length(),8);
}

