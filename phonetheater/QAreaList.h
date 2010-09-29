#ifndef QAREALIST_H
#define QAREALIST_H
#include <QStringList>

#include "QUrlFactory.h"


class QAreaList : public QUrlFactory
{
public:

    QAreaList(QObject *pParent, QString strParm);
    //strParm stand for area name

    QString GetParm();

    QStringList GetAreaList();

public slots:
    void DealResult(QByteArray &result);


protected:

    QString strAreaName;

    QStringList arList;


};
#endif // QAREALIST_H
