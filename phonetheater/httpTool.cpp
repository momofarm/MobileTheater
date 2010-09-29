#include <QObject>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QUrl>
#include <QTextCodec>
#include "httpTool.h"
#include "QUrlFactory.h"
#include <QEventLoop>

QHttpTool::QHttpTool(QObject *pParent)
    :QObject(pParent)
{
    pManager = new QNetworkAccessManager(this);

}

void QHttpTool::Request(QString strUrlHost, int port, QUrlFactory *factory)
{


    QUrl urlHost(strUrlHost);

    urlHost.setPort(port);

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    QByteArray ary;

    QString strParmeter = factory->GetParm();

    ary.append(strParmeter);

    QString encoded = codec->toUnicode(ary);

    urlHost.setPath(encoded);

    QUrl finalUrl(urlHost);

    QNetworkRequest request(finalUrl);

    QNetworkReply *reply = pManager->get(request);

    QEventLoop loop;

    connect(pManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    connect(pManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(Ready(QNetworkReply*)));

    loop.exec();

}


void QHttpTool::Ready(QNetworkReply *reply)
{
    if (reply->isFinished())
    {
        QByteArray ary = reply->readAll();

        QString strResult(ary.data());

        emit ReturnResult(ary);
        //strResults = strResult;

    }
}

