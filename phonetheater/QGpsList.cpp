
#include "QGPSList.h"
#include "Constants.h"
#include <QTextCodec>
#include <parser.h>
#include <QVariant>
#include <QStringList>

QGpsList::QGpsList(QString lng, QString lat, QObject *pParent):
        QUrlFactory::QUrlFactory(pParent, lng)
{
    strLngLatParm = QString("%1,%2").arg(lng).arg(lat);

}

QString QGpsList::GetParm()
{
    QString strPath(PATH_LOC);

    QString strPathAndParm = strPath + strLngLatParm;

    QByteArray ar = strPathAndParm.toAscii();

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    QString encoded = codec->toUnicode(ar);

    return encoded;

}

void QGpsList::DealResult(QByteArray &result)
{
    //handle this part is important

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

    if (list.size() > 0)
    {
        for (int i = 0; i < list.size(); i++)
        {
            QVariantList list2 = list.at(i).toList();

            QString strTheaterID = list2.at(0).toString();

            QString strTheaterName = list2.at(3).toString();

            ids.push_back(strTheaterID);

            names.push_back(strTheaterName);
        }

    }
    else
    {
        return;
    }

}

QStringList QGpsList::GetTopList()
{
    return ids;

}

QStringList QGpsList::GetNames()
{
    return names;
}
