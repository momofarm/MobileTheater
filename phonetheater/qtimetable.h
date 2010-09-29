#ifndef QTIMETABLE_H
#define QTIMETABLE_H

#include "QUrlFactory.h"
#include <QStringList>

class QTimeTable : public QUrlFactory
{
public:
    QTimeTable(QObject *pParent, QString strParm);


    QString GetParm();


public slots:
    void DealResult(QByteArray &result);

public:
    QStringList GetTheaterInfo();

    QStringList GetMovieNames();
    QStringList GetMovieHall();
    QStringList GetMovieTime();

protected:

    QString strTheaterCode;

    QStringList arTheaterInfo;

    QStringList arMovieHall;
    QStringList arMovieList;
    QStringList arMovieTime;

    //QStringList arListCode;
   // QStringList arListName;
};

#endif // QTIMETABLE_H
