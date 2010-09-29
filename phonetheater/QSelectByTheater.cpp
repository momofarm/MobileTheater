

#include "QSelectByTheater.h"
#include <stdlib.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QSignalMapper>
#include <QTextCodec>
#include "qtimetable.h"
#include "httpTool.h"
#include "Constants.h"
#include "todayshow.h"
#include <QAction>

QSelectByTheater::QSelectByTheater(QWidget *pParent, QStringList *pTheaterNameList, QStringList *pTheaterCodeList)
    :QDialog(pParent)
{
    QAction *pActionBack = new QAction("°h¥X", this);

    pActionBack->setSoftKeyRole(QAction::NegativeSoftKey);

    QAction *pActionOption = new QAction("¿ï¶µ", this);

    pActionOption->setSoftKeyRole(QAction::PositiveSoftKey);

    addAction(pActionBack);

    addAction(pActionOption);

    connect(pActionBack, SIGNAL(triggered()), this, SLOT(close()));

    connect(pActionOption, SIGNAL(triggered()), this, SLOT(close()));

    std::vector<QPushButton *> ar;

    QVBoxLayout *pLayout = new QVBoxLayout();

    pMapper = new QSignalMapper(this);

    QTextCodec *codec = QTextCodec::codecForName("BIG5");

    for (int i = 0; i < pTheaterNameList->count(); i++)
    {
        QString str = pTheaterNameList->at(i);

        QByteArray arydata;

        arydata.append(str);

        QPushButton *pButton = new QPushButton(str, this);

        ar.push_back(pButton);

        pLayout->addWidget(pButton);

        pMapper->setMapping(pButton, pTheaterCodeList->at(i));

        connect(pButton, SIGNAL(clicked()), pMapper, SLOT(map()));
    }
    //mapped(QString &)

    connect(pMapper, SIGNAL(mapped(QString)), this, SLOT(Press(QString)));

    setLayout(pLayout);

    show();
}

QSelectByTheater::~QSelectByTheater()
{

}


void QSelectByTheater::Press(QString strCode)
{
   //sender()->

   int a = 0;

   QHttpTool *t = new QHttpTool(this);

   QTimeTable *list = new QTimeTable(this, strCode);

   connect(t, SIGNAL(ReturnResult(QByteArray &)), list, SLOT(DealResult(QByteArray &)));

   t->Request(HTTP_URL_HOST, HTTP_URL_PORT, list);

   QTodayShow showDlg(list->GetMovieNames(), list->GetMovieHall(), list->GetMovieTime(), this);

   QStringList theaterInfo = list->GetTheaterInfo();
   //name/phone/addr

   QString name = theaterInfo.at(0);

   QString phone = theaterInfo.at(1);

   QString addr = theaterInfo.at(2);

   showDlg.SetInfo(name, phone, addr);


   showDlg.exec();

}


