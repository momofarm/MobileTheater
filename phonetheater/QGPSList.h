#ifndef QGPSLIST_H
#define QGPSLIST_H

#include "QUrlFactory.h"
#include <QStringList>

class QGpsList : public QUrlFactory
{
public:
    QGpsList(QString lng, QString lat, QObject *pParent = 0);

    QString GetParm();

    QStringList GetTopList();

    QStringList GetNames();

public slots:
    void DealResult(QByteArray &result);

protected:
    QString strLngLatParm;
    QStringList ids;
    QStringList names;

};

#endif // QGPSLIST_H
