
#include "QAreaList.h"
#include "QTextCodec"
#include "Constants.h"
#include <parser.h>
#include <QVariant>

QAreaList::QAreaList(QObject *pParent, QString strParm):
        QUrlFactory(pParent, strParm)
{

    setParent(pParent);

    strAreaName = strParm;

}

QString QAreaList::GetParm()
{
    QString strPath(PATH_AREA_LIST);

    QString strPathAndParm = strPath;

    QByteArray ar = strPathAndParm.toAscii();

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    QString encoded = codec->toUnicode(ar);

    return encoded;

}

void QAreaList::DealResult(QByteArray &result)
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
            QString str = list.at(i).toString();

            arList.push_back(str);

        }

    }
    else
    {
        return;
    }

}

QStringList QAreaList::GetAreaList()
{
    return arList;

}

