#include "requests/invoicerequests.h"
#include <QEventLoop>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent/QtConcurrent>

const QJsonArray InvoiceRequests::parseCustomerNames(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        throw std::runtime_error(QObject::tr("Failed to request customer names.").toStdString());
        //return ;
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.object().value(BaseKeys::response).isArray()) {
        return QJsonArray();
    }
    else {
        return doc.object().value(BaseKeys::response).toArray();
    }
}

const QJsonArray InvoiceRequests::parseGetCurrencies(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        throw std::runtime_error(QObject::tr("Failed to request currencies.").toStdString());
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.object().value(BaseKeys::response).isArray()) {
        return QJsonArray();
        //emit InvoiceRequests::currencies(QJsonArray());
    }
    else {
        return doc.object().value(BaseKeys::response).toArray();
    }
}

const int InvoiceRequests::parseAddInvoice(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        Requests::parseRequestError(reply->error());
        throw std::runtime_error(QObject::tr("Failed to request add invoice.").toStdString());
    }
    const auto doc = QJsonDocument::fromJson(reply->readAll());
    if (doc.object().value(BaseKeys::response).isString() && doc.object().value(BaseKeys::response).toString().toLower().compare("EXIST",Qt::CaseInsensitive) == 0) {
        return -1;
    }
    else {
        return doc.object().value(BaseKeys::response).toInteger();
    }
}

InvoiceRequests::InvoiceRequests(Requests *parent)
    : Requests{parent}
{

}

void InvoiceRequests::requestCustomerNames(const QVariantMap &body)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> customerNames = QtConcurrent::run([body,this](){
        return Requests::requestPostReply(body,Endpoints::GetCustomersS);
    }).then([this](QNetworkReply* reply){
        try {
            const auto response = this->parseCustomerNames(reply);
            emit InvoiceRequests::customerNames(response);
        }
        catch(const std::runtime_error& err) {
            qDebug() << err.what();
            throw std::runtime_error(err.what());
        }
    });
    watcher.setFuture(customerNames);
    loop.exec();
    this->setIsWorking(false);
}

void InvoiceRequests::requestGetCurrency()
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> getCurrencies = QtConcurrent::run([this](){
        return Requests::requestGetReply(Endpoints::GetCurrency);
    }).then([this](QNetworkReply* reply){
        try {
            const auto response = this->parseGetCurrencies(reply);
            emit InvoiceRequests::currencies(response);
        }
        catch(const std::runtime_error& err) {
            qDebug() << err.what();
            throw std::runtime_error(err.what());
        }
    });
    watcher.setFuture(getCurrencies);
    loop.exec();
    this->setIsWorking(false);
}

void InvoiceRequests::requestInvoiceFormData(const QVariantMap &customerNamesBody)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> invoiceForm = QtConcurrent::run([customerNamesBody,this](){
        return Requests::requestPostReply(customerNamesBody,Endpoints::GetCustomersS);
    }).then([this](QNetworkReply* reply){
        try {
            return this->parseCustomerNames(reply);
        }
        catch(const std::runtime_error& err) {
            qDebug() << err.what();
            throw std::runtime_error(err.what());
        }
    }).then([this](const QJsonArray customerNamesList){
        const auto reply = Requests::requestGetReply(Endpoints::GetCurrency);
        try {
            const auto currencyList = this->parseGetCurrencies(reply);
            emit InvoiceRequests::invoiceFormData(customerNamesList,currencyList);
        }
        catch(const std::runtime_error& err) {
            qDebug() << err.what();
            throw std::runtime_error(err.what());
        }
    });
    watcher.setFuture(invoiceForm);
    loop.exec();
    this->setIsWorking(false);
}

void InvoiceRequests::requestAddInvoice(const QVariantMap &body)
{
    QEventLoop loop;
    QFutureWatcher<void> watcher;
    QObject::connect(&watcher,&QFutureWatcher<void>::started,[this](){
        this->setIsWorking(true);
    });
    QObject::connect(&watcher,&QFutureWatcher<void>::finished,&loop,&QEventLoop::quit);
    QFuture<void> getCurrencies = QtConcurrent::run([body,this](){
        return Requests::requestPostReply(body,Endpoints::AddInvoice);
    }).then([this](QNetworkReply* reply){
        try {
            const auto response = this->parseAddInvoice(reply);
            if (response == -1) {
                emit InvoiceRequests::addInvoiceFailed(QObject::tr("This invoice number already exists."));
            }
            else {
                emit InvoiceRequests::addedInvoice(response);
            }
        }
        catch(const std::runtime_error& err) {
            qDebug() << err.what();
            throw std::runtime_error(err.what());
        }
    });
    watcher.setFuture(getCurrencies);
    loop.exec();
    this->setIsWorking(false);
}
