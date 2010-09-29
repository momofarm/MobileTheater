#ifndef QLISTMODEL_H
#define QLISTMODEL_H

#include <QAbstractItemDelegate>
#include <QPainter>

class listdelicate : public QAbstractItemDelegate
{
public:
    listdelicate(QObject *pParent = 0);

    virtual ~listdelicate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
     void SetMod();

public slots:
    void Mod();

public:
    QString GetDataString(const QModelIndex &index, int nIndexCount) const;
    void paintLine2(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
    void paintLine3(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index);
    int SplitHeight(QRect &rc) const;


protected:
    mutable bool bModified;
    mutable int nMoreLines;
    int nNewHeight;
    mutable int nTextHeight;
};

#endif // QLISTMODEL_H
