
#include <QPainter>
#include <qlistview.h>

#include "listviewitem.h"

//obselete for now, maybe use later
viewitem::viewitem(QListView *parent)
{
    arList.empty();
    nLineCount = 0;
}

viewitem::viewitem(QStringList &list, int nLines)
{
    arList = list;
    nLineCount = nLines;
}


void viewitem::paintCell(QPainter *painter, const QColorGroup &cg, int column, int width, int alignment)
{

    int nHeight = 0; //height();

    int nEachHeight = nHeight / nLineCount;

    int nTop = 0;

    int nLeftStart = 0;

    for (int i = 0; i < nLineCount; i++)
    {
        QRect rcLine(nLeftStart, nTop, width, nEachHeight);

        QString str = arList.at(i);

        painter->drawText(rcLine.left(), rcLine.top(), rcLine.width(), rcLine.height(), Qt::AlignLeft, str, &rcLine);
    }


}

