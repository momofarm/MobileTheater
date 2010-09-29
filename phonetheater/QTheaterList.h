#ifndef QTHEATERLIST_H
#define QTHEATERLIST_H
#include <QStringList>

#include "QUrlFactory.h"


class QTheaterList : public QUrlFactory
{
public:

    QTheaterList(QObject *pParent, QString strParm);
    //strParm stand for area name

    QString GetParm();

    QStringList GetTheaterList();

    QStringList GetCodeList();

public slots:
    void DealResult(QByteArray &result);


protected:

    QString strAreaName;

    QStringList arListCode;
    QStringList arListName;


};


#endif // QTHEATERLIST_H
