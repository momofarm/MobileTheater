#ifndef LISTVIEWITEM_H
#define LISTVIEWITEM_H
#include <qlistview.h>


class viewitem
{
public:
    viewitem(QListView *parent);
    viewitem(QStringList &list, int nLines);
   // ~viewitem();


public:
    virtual void paintCell(QPainter *painter, const QColorGroup &cg, int column, int width, int alignment);

protected:
    QStringList arList;
    int nLineCount;

};

#endif // LISTVIEWITEM_H
