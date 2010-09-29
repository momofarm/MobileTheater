#ifndef TODAYSHOW_H
#define TODAYSHOW_H
#include <QDialog>
#include <QObject>
#include <QLabel>
#include <QListView>
#include <QVector>

class QTodayShow : public QDialog
{
    Q_OBJECT
public:
    QTodayShow(QStringList aryName, QStringList aryHall, QStringList aryTime, QWidget *parent = 0);

    void SetInfo(QString strTheaterName, QString strTheaterPhone, QString StrTheaterAddress);

protected:
    QLabel *labelName;
    QLabel *labelAddr;
    QLabel *labelPhone;
    QVector<QListView *> arListViews;

public slots:
    void HideAll();

};

#endif // TODAYSHOW_H
