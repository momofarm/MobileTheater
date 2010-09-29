#ifndef QSELECTBYTHEATER_H
#define QSELECTBYTHEATER_H

#include <QDialog>
#include <QObject>

class QStringList;
class QSignalMapper;

class QSelectByTheater : public QDialog
{
    Q_OBJECT

public:

    QSelectByTheater(QWidget *pParent, QStringList *pTheaterNameList, QStringList *pTheaterCodeList);
    ~QSelectByTheater();

public slots:
    void Press(QString strCode);

protected:
    QSignalMapper *pMapper;
};


#endif // QSELECTBYTHEATER_H
