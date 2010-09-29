#include "qlistmodel.h"
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QAbstractItemDelegate>
#include <QString>
#include <math.h>
#include <QListView>
#include <QDebug>

#define nDivSpace 2

listdelicate::listdelicate(QObject *pParent):
        QAbstractItemDelegate(pParent)
{
    bModified = false;
    nMoreLines = 0;
    nNewHeight = 0;

    //connect(this, SIGNAL(SetMod()), this, SLOT(Mod()));

}


void listdelicate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const
{

    //TODO:
    //  if expanded for new lines, what will happen after expanded in this section?
    //  check again before run... I don't know if there is a problem here
    QRect r = option.rect;

    QString dataString = GetDataString(index, 0);

    QBrush brush(QColor(255, 255, 255));

    painter->setBackground(brush);
    painter->drawText(r.left(), r.top(), r.width(), r.height(), Qt::AlignLeft, dataString, &r);

    /*
    QRect r = option.rect;

    int nHeightEach = SplitHeight(r) - 2 * nDivSpace;

    //split original Rect size to three part
    QRect rcLine1(r.left(), r.top(), r.width(), nHeightEach);
    QRect rcLine2(r.left(), r.top() + nHeightEach + nDivSpace, r.width(), nHeightEach);
    QRect rcLine3(r.left(), r.top() + nHeightEach * 2 + nDivSpace * 2, r.width(), nHeightEach);

    QRectF rctemp = painter->boundingRect(QRectF(0, 0, 0, 0), QString("10:00"));

    //text actual length
    QRect rcText = rctemp.toRect();

    //start painting lines

    //line 1
    QString dataString = GetDataString(index, 0);

    painter->drawText(rcLine1.left(), rcLine1.top(), rcLine1.width(), rcLine1.height(), Qt::AlignLeft, dataString, &rcLine1);


    //line 2
    QString dataString2 = GetDataString(index, 1);

    painter->drawText(rcLine2.left(), rcLine2.top(), rcLine2.width(), rcLine2.height(), Qt::AlignLeft, dataString2, &rcLine2);

    //line 3
    QString dataString3 = GetDataString(index, 2);


    //time format should like this: 11:00,12:00,13:00, ...etc
    QStringList list = dataString3.split(",");

    //total string this control can have

    int nWidth = r.width();

    int nMaxCount = nWidth / rcText.width();

    bool bNeedSplit = false;

    int nNewLine = 0;

    if (list.count() > nMaxCount)       //need to split line
    {
        bNeedSplit = true;

        nNewLine = round(list.count() / nMaxCount) + 1;
    }

    /*
    if (bNeedSplit)
    {
        //bModified = true;

        //emit SetMod();

        bModified = true;

        nTextHeight = (nNewLine - 1) * nHeightEach + rcLine3.height() + (nNewLine - 1) * nDivSpace;

        //check if need more than one new line

        QRect rcLineExpand(rcLine3.left(), rcLine3.top(), rcLine3.width(), rcLine3.height() + nTextHeight);

        int rTop = rcLineExpand.top();

        QStringList tempList = list;

        for (int i = 0; i < nNewLine; i++)
        {

            QRect rcLine(rcLineExpand.left(), rTop + (i * nHeightEach + nDivSpace), rcLineExpand.width(), nHeightEach);

            QStringList temp;

            for (int j = nMaxCount; j > 0; j--)
            {
                if (!tempList.isEmpty())
                    temp.append(tempList.takeFirst());
            }


            QString str = temp.join((" "));

            painter->drawText(rcLine.left(), rcLine.top(), rcLine.width(), rcLine.height(), Qt::AlignLeft, str, &rcLine);

        }

        nMoreLines = nNewLine;
    }
    else
    {*/


  //      painter->drawText(rcLine3.left(), rcLine3.top(), rcLine3.width(), rcLine3.height(), Qt::AlignLeft, dataString3, &rcLine3);
    //}


    //use QRectF QPainter::boundingRect ( const QRectF & rectangle, int flags, const QString & text )
    //  to detect QString boundary


}

void listdelicate::Mod()
{

}

int listdelicate::SplitHeight(QRect &rc) const
{
    if (bModified)
    {

        return (nTextHeight - (nMoreLines * nDivSpace)) / nMoreLines;
    }
    else
    {
        nTextHeight = rc.height() / 3;

        return nTextHeight;
    }
}


void listdelicate::paintLine2(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{


}

void listdelicate::paintLine3(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)
{


}


QString listdelicate::GetDataString(const QModelIndex &index, int nIndexCount) const
{
    QModelIndex id = index.model()->index(index.row(), index.column() + nIndexCount);

    int nCol = id.column();

    QVariant data = id.data();

    QString str = id.data().toString();

    return str;
}


QSize listdelicate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{  
        return QSize(30, 20);
}

listdelicate::~listdelicate()
{

}

