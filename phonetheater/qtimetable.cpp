#include "qtimetable.h"

#include "QTextCodec"
#include "Constants.h"
#include <parser.h>
#include <QVariant>
#include <QStringList>

QTimeTable::QTimeTable(QObject *pParent, QString strParm):
        QUrlFactory(pParent, strParm)
{

    setParent(pParent);

    if (strParm.isEmpty())
    {
        Q_ASSERT(false);

        //empty not allowed

        return;

    }

    strTheaterCode = strParm;

}

QString QTimeTable::GetParm()
{
    QString strPath(PATH_THEATER_INFO);

    if (strTheaterCode.isEmpty())
    {
        Q_ASSERT(false);

        return QString("");
    }

    QString strPathAndParm = strPath + strTheaterCode;

    QByteArray ar = strPathAndParm.toAscii();

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    QString encoded = codec->toUnicode(ar);

    return encoded;

}

void QTimeTable::DealResult(QByteArray &result)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");

    QString encoded = codec->toUnicode(result);

    encoded.replace(QString("&quot"), QString("\""));

    encoded.replace(QString(";"), QString(""));

    QByteArray json;

    json.append(encoded.toUtf8());

    QJson::Parser parser;

    bool ok;

    QVariant result2 = parser.parse(json, &ok);

    QVariantList list = result2.toList();


    int a = 0;

    if (list.size() > 0)
    {

        QVariantMap map = list.at(0).toMap();
\
        const QVariant varPhone = map.value("phone");

        QString strPhone = varPhone.toString();

        const QVariant varName = map.value("name");

        QString strName = varName.toString();

        const QVariant varAddr = map.value("address");

        QString strAddr = varAddr.toString();

        arTheaterInfo.push_back(strName);

        arTheaterInfo.push_back(strPhone);

        arTheaterInfo.push_back(strAddr);

        /////////////////////////////////////////////////

        QVariantList list2 = list.at(1).toList();

        for (int i = 0; i < list2.size(); i++)
        {
            QVariantList data = list2.at(i).toList();

            QString hallname = data.at(0).toString();

            QString movie_title = data.at(1).toString();

            QString time_table = data.at(2).toString();

            arMovieHall.push_back(hallname);

            arMovieList.push_back(movie_title);

            arMovieTime.push_back(time_table);
        }

    }
    else
    {
        return;
    }
}

QStringList QTimeTable::GetTheaterInfo()
{
    return arTheaterInfo;
}

QStringList QTimeTable::GetMovieNames()
{
    return arMovieList;

}

QStringList QTimeTable::GetMovieHall()
{
    return arMovieHall;
}

QStringList QTimeTable::GetMovieTime()
{
    return arMovieTime;
}



