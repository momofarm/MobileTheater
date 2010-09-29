
#include "QTheaterList.h"
#include "QTextCodec"
#include "Constants.h"
#include <parser.h>
#include <QVariant>

QTheaterList::QTheaterList(QObject *pParent, QString strParm):
        QUrlFactory(pParent, strParm)
{

    setParent(pParent);

    if (strParm.isEmpty())
    {
        Q_ASSERT(false);

        //empty not allowed

        return;

    }

    strAreaName = strParm;

}

QString QTheaterList::GetParm()
{
    QString strPath(PATH_THEATER_LIST);

    if (strAreaName.isEmpty())
    {
        Q_ASSERT(false);

        return QString("");
    }

    QString strPathAndParm = strPath + strAreaName;

    QByteArray ar = strPathAndParm.toAscii();

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    QString encoded = codec->toUnicode(ar);

    return encoded;

}

void QTheaterList::DealResult(QByteArray &result)
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

    if (list.size() > 0)
    {

        for (int i = 0; i < list.size(); i++)
        {
            QVariantList list2 = list.at(i).toList();

            QString co11 = list2.at(0).toString();

            arListCode.push_back(co11);

            QString col2 = list2.at(1).toString();

            arListName.push_back(col2);
        }
    }
    else
    {
        return;
    }

}

QStringList QTheaterList::GetTheaterList()
{
    return arListName;

}

QStringList QTheaterList::GetCodeList()
{
    return arListCode;

}

