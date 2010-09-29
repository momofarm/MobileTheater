
#include "QSelectByArea.h"
#include <stdlib.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QSignalMapper>
#include <QTextCodec>
#include "QTheaterList.h"
#include "httpTool.h"
#include "Constants.h"
#include "QSelectByTheater.h"
#include <QAction>

QSelectByArea::QSelectByArea(QWidget *pParent, QStringList *pList)
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

    for (int i = 0; i < pList->count(); i++)
    {
        QString str = pList->at(i);

        QByteArray arydata;

        arydata.append(str);

        QPushButton *pButton = new QPushButton(str/*QString::fromUtf8(arydata.data())*/, this);

        ar.push_back(pButton);

        pLayout->addWidget(pButton);

        pMapper->setMapping(pButton, pList->at(i));

        connect(pButton, SIGNAL(clicked()), pMapper, SLOT(map()));
    }
    //mapped(QString &)

    connect(pMapper, SIGNAL(mapped(QString)), this, SLOT(PressArea(QString)));

    setLayout(pLayout);

    show();
}

QSelectByArea::~QSelectByArea()
{

}


void QSelectByArea::PressArea(QString area)
{
   QHttpTool *t = new QHttpTool(this);

   QTheaterList *list = new QTheaterList(this, area);

   connect(t, SIGNAL(ReturnResult(QByteArray &)), list, SLOT(DealResult(QByteArray &)));

   t->Request(HTTP_URL_HOST, HTTP_URL_PORT, list);

   QStringList arArea = list->GetTheaterList();

   QStringList arCode = list->GetCodeList();

   QSelectByTheater dlgTheater(this, &arArea, &arCode);

   dlgTheater.exec();


}


