
#include "todayshow.h"
#include <QList>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListView>
#include <QStandardItemModel>
#include <QLabel>
#include <QHBoxLayout>
#include "qlistmodel.h"
#include <QAction>
#include <QSpacerItem>

QTodayShow::QTodayShow(QStringList aryName, QStringList aryHall, QStringList aryTime, QWidget *parent):
        QDialog(parent)
{
   //internal check

    QAction *pActionBack = new QAction("退出", this);

    pActionBack->setSoftKeyRole(QAction::NegativeSoftKey);

    QAction *pActionOption = new QAction("選項", this);

    pActionOption->setSoftKeyRole(QAction::PositiveSoftKey);

    addAction(pActionBack);

    addAction(pActionOption);

    connect(pActionBack, SIGNAL(triggered()), this, SLOT(close()));

    connect(pActionOption, SIGNAL(triggered()), this, SLOT(close()));

    QVBoxLayout *pLayoutLast = new QVBoxLayout(this);

    labelName = new QLabel(this);

    labelAddr = new QLabel(this);

    labelPhone = new QLabel(this);

    pLayoutLast->addWidget(labelName);

    pLayoutLast->addWidget(labelAddr);

    pLayoutLast->addWidget(labelPhone);

    if (aryName.size() != aryTime.size())
    {
        Q_ASSERT(false);
        //setting wrong, please check again

        return;
    }

    QLabel *label1 = new QLabel("今日放映", this);

    QVBoxLayout *pHLayout = new QVBoxLayout(this);

    pHLayout->addWidget(label1);

    QLabel *label2 = new QLabel("\(請按下電影名稱以顯示時刻表\)", this);

    pLayoutLast->addLayout(pHLayout);

    pLayoutLast->addWidget(label2);

    QList<QPushButton *> arButtons;

    int nCoutName = aryName.count();


    for (int i = 0; i < aryName.count(); i++)
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QPushButton *button = new QPushButton(aryName.at(i), this);

        arButtons.push_back(button);

        QString movie_time = aryTime.at(i);

        QStringList time_table = movie_time.split(" ");

        QVector<int> arEmpty;

        arEmpty.clear();

        for (int c = 0; c < time_table.count(); c++)
        {
            QString str = time_table.at(c);

            if (str.isEmpty())
            {
                arEmpty.push_back(c);
            }

        }

        for (int c = arEmpty.count() - 1; c >= 0; c--)
        {
            int count = arEmpty.at(c);

            time_table.removeAt(count);
        }

        //ItemModel setting
        QStandardItemModel *pModel = new QStandardItemModel(time_table.count(), 1);

        pModel->insertColumn(0);

        for (int j = 0; j < time_table.count(); j++)
        {
            QStandardItem *item = NULL;

            item = new QStandardItem(time_table.at(j));

            pModel->setItem(j, item);
        }

        QListView *pView = new QListView(this);

        pView->setModel(pModel);

        //listdelicate *pdel = new listdelicate(this);

        //pView->setItemDelegate(pdel);

        arListViews.push_back(pView);

        layout->addWidget(button);

        layout->addWidget(pView);

        pLayoutLast->addLayout(layout);

    }

    int nNameCount = aryName.count();

    int narListCount = arListViews.count();

    QSpacerItem *pSpacer = new QSpacerItem(30, 40, QSizePolicy::Expanding);

    pLayoutLast->addSpacerItem(pSpacer);

    setLayout(pLayoutLast);

    for (int k = 0; k < arListViews.count(); k++)
    {
        arListViews.at(k)->hide();
    }

    for (int l = 0; l < arListViews.count(); l++)
    {
       QPushButton *pButton = arButtons.at(l);

       QListView *pWidget = arListViews.at(l);

       connect(pButton, SIGNAL(clicked()), this, SLOT(HideAll()));

       connect(pButton, SIGNAL(clicked()), pWidget, SLOT(show()));

    }

    show();

};


void QTodayShow::HideAll()
{

    int nCount = arListViews.count();

    for (int i = 0; i < arListViews.count(); i++)
    {
        QListView *pView = arListViews.at(i);

        int a = 0;
        if (pView)
        {
            pView->hide();
        }
    }

}


void QTodayShow::SetInfo(QString strTheaterName, QString strTheaterPhone, QString StrTheaterAddress)
{
    labelName->setText(strTheaterName);

    labelPhone->setText(strTheaterPhone);

    labelAddr->setText(StrTheaterAddress);
}
