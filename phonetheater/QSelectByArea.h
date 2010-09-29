#ifndef QSELECTBYAREA_H
#define QSELECTBYAREA_H
#include <QDialog>
#include <QObject>

class QStringList;
class QSignalMapper;

class QSelectByArea : public QDialog
{
    Q_OBJECT

public:

    QSelectByArea(QWidget *pParent, QStringList *pList);
    ~QSelectByArea();

public slots:
    void PressArea(QString area);

protected:
    QSignalMapper *pMapper;
};

#endif // QSELECTBYAREA_H
