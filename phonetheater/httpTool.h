#ifndef HTTPTOOL_H
#define HTTPTOOL_H

#include <QObject>
class QNetworkReply;
class QNetworkAccessManager;
class QUrlFactory;

class QHttpTool : public QObject
{
    Q_OBJECT

public:
    QHttpTool(QObject *pParent = 0);
    void Request(QString strUrlHost, int port, QUrlFactory *factory);

signals:
    void ReturnResult(QByteArray&);

public slots:
    void Ready(QNetworkReply *reply);

protected:
    QNetworkAccessManager *pManager;

};

#endif // HTTPTOOL_H
