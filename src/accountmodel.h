#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QAbstractListModel>
#include <QUrl>
#include <QNetworkConfigurationManager>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include "account.h"
#include "o1twitter.h"
#include "o1requestor.h"

class AccountModel : public QAbstractListModel
{
    Q_OBJECT
public:
    AccountModel();

    virtual int rowCount(const QModelIndex&) const;
    virtual QVariant data(const QModelIndex &index, int role) const;

    Q_INVOKABLE void obtainPinUrl();
    Q_INVOKABLE void enterPin(const QString &pin);
    Q_INVOKABLE bool isLinked();
    Q_INVOKABLE void verifyCredentials();

signals:
    void pinRequestError(const QString &errorMessage);
    void pinRequestSuccessful(const QString &url);
    void linkingFailed(const QString &errorMessage);
    void linkingSuccessful();
    void credentialsVerified(const QJsonDocument accountDetails);
    void credentialsInvalid();
    void verificationError(const QString &errorMessage);

public slots:
    void handlePinRequestError(const QString &errorMessage);
    void handlePinRequestSuccessful(const QUrl &url);
    void handleLinkingFailed();
    void handleLinkingSucceeded();

private:
    QList<Account*> availableAccounts;
    QNetworkConfigurationManager *networkConfigurationManager;
    QString encryptionKey;
    O1Twitter *o1;
    QNetworkAccessManager *manager;
    O1Requestor *requestor;

    void obtainEncryptionKey();

private slots:
    virtual void onVerificationError(QNetworkReply::NetworkError error);
    virtual void onVerificationFinished();
};

#endif // ACCOUNTMODEL_H
