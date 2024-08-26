#include <QApplication>
#include <FelgoApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtWebView/QtWebView>
#include <QTranslator>


// uncomment this line to add the Live Client Module and use live reloading with your custom C++ code
#include <FelgoLiveClient>
#include "latesttransactionstablemodel.h"
#include "customerstablemodel.h"
#include "requests/authrequests.h"
#include "requests/setupbranch.h"
#include "requests/companyusersrequests.h"
#include "models/branchlistmodel.h"
#include "forms/vendorregistrationform.h"
#include "forms/customerform.h"
#include "forms/invoiceform.h"


int main(int argc, char *argv[])
{

    QtWebView::initialize();
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Biz Logic Solutions");
    QCoreApplication::setApplicationName("Jichange");

    QTranslator translator;
    if (!translator.load("qrc:/jichange_v3_en_us")) {
        qDebug() << "Failed to install translator";
    }
    app.installTranslator(&translator);
    FelgoApplication felgo;


    QQmlApplicationEngine engine;
    felgo.initialize(&engine);

    // Set an optional license key from project file
    // This does not work if using Felgo Live, only for Felgo Cloud Builds and local builds
    felgo.setLicenseKey(PRODUCT_LICENSE_KEY);
    qmlRegisterType<LatestTransactionsTableModel>("LatestTransactionsTableModel",1,0,"LatestTransactionsTableModel");
    qmlRegisterType<CustomersTableModel>("CustomersTableModel",1,0,"CustomersTableModel");
    qmlRegisterType<SetupBranch>("SetupBranch",1,0,"SetupBranch");
    qmlRegisterType<BranchListModel>("BranchListModel",1,0,"BranchListModel");
    qmlRegisterType<Validator>("Validator",1,0,"Validator");
    qmlRegisterType<CompanyUsersRequests>("CompanyUsersRequests",1,0,"CompanyUsersRequests");
    qmlRegisterType<VendorRegistrationForm>("VendorRegistrationForm",1,0,"VendorRegistrationForm");
    qmlRegisterType<CustomerForm>("CustomerForm",1,0,"CustomerForm");
    qmlRegisterType<InvoiceForm>("InvoiceForm",1,0,"InvoiceForm");
    AuthRequests requests;
    engine.rootContext()->setContextProperty("_authRequests",&requests);

    // use this during development
    // for PUBLISHING, use the entry point below
    felgo.setMainQmlFileName(QStringLiteral("qml/Main.qml"));

    // use this instead of the above call to avoid deployment of the qml files and compile them into the binary with qt's resource system qrc
    // this is the preferred deployment option for publishing games to the app stores, because then your qml files and js files are protected
    // to avoid deployment of your qml files and images, also comment the DEPLOYMENTFOLDERS command in the .pro file
    // also see the .pro file for more details
    //felgo.setMainQmlFileName(QStringLiteral("qrc:/qml/Main.qml"));

    engine.load(QUrl(felgo.mainQmlFileName()));

    // to start your project as Live Client, comment (remove) the lines "felgo.setMainQmlFileName ..." & "engine.load ...",
    // and uncomment the line below
    //FelgoLiveClient client (&engine);

    return app.exec();
}
