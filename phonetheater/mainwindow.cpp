#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "QSelectByArea.h"
#include "httpTool.h"
#include "Constants.h"
//#include "QUrlFactory.h"
#include "QTheaterList.h"
#include "QAreaList.h"
#include <qgeocoordinate.h>
#include "QGPSList.h"
#include "QSelectByTheater.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(SelectByArea()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(SelectByGPS()));


    pActionBack = new QAction("°h¥X", this);

    pActionBack->setSoftKeyRole(QAction::NegativeSoftKey);

    pActionOption = new QAction("¿ï¶µ", this);

    pActionOption->setSoftKeyRole(QAction::PositiveSoftKey);

    addAction(pActionBack);
    addAction(pActionOption);

    connect(pActionBack, SIGNAL(triggered()), this, SLOT(close()));
    connect(pActionOption, SIGNAL(triggered()), this, SLOT(close()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SelectByArea()
{

    /////////////////////////////////////////////////////////
    QHttpTool *t = new QHttpTool(this);

    QAreaList *areas = new QAreaList(this, QString(""));

    connect(t, SIGNAL(ReturnResult(QByteArray&)), areas, SLOT(DealResult(QByteArray&)));

    t->Request(HTTP_URL_HOST, HTTP_URL_PORT, areas);

    QStringList areaList = areas->GetAreaList();

    QSelectByArea dlg(this, &areaList);

    dlg.exec();

}

void MainWindow::SelectByGPS()
{
    if (!locationDataSource)
     {
         locationDataSource =
             QGeoPositionInfoSource::createDefaultSource(this);
         // Whenever the location data source signals that the current
         // position is updated, the positionUpdated function is called
         QObject::connect(locationDataSource,
                          SIGNAL(positionUpdated(QGeoPositionInfo)),
                          this,
                          SLOT(positionUpdated(QGeoPositionInfo)));

         // Start listening for position updates
         locationDataSource->startUpdates();
     }


}

void MainWindow::positionUpdated(QGeoPositionInfo geoPositionInfo)
{
    if (geoPositionInfo.isValid())
       {
           // We've got the position. No need to continue the listening.
           locationDataSource->stopUpdates();

           // Save the position information into a member variable
           myPositionInfo = geoPositionInfo;

           // Get the current location as latitude and longitude
           QGeoCoordinate geoCoordinate = geoPositionInfo.coordinate();
           qreal latitude = geoCoordinate.latitude();
           qreal longitude = geoCoordinate.longitude();

           //coordinate acquired
           //start calling request to server

           QHttpTool *t = new QHttpTool(this);

           QGpsList *gpsdata = new QGpsList(QString::number(longitude), QString::number(latitude), this);

           connect(t, SIGNAL(ReturnResult(QByteArray&)), gpsdata, SLOT(DealResult(QByteArray&)));

           t->Request(HTTP_URL_HOST, HTTP_URL_PORT, gpsdata);

           QStringList arList = gpsdata->GetTopList();

           QStringList arNames = gpsdata->GetNames();

           QSelectByTheater dlg(this, &arNames, &arList);

           dlg.exec();

           delete locationDataSource;

           locationDataSource = NULL;

           //QSelectByArea dlg(this, &areaList);

           //dlg.exec();


       }

}
