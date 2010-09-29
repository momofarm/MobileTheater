#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgeopositioninfo.h>
#include <qgeopositioninfosource.h>
#include <QPointer>

QTM_USE_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void SelectByArea();
    void SelectByGPS();
    void positionUpdated(QGeoPositionInfo geoPositionInfo);

private:
    Ui::MainWindow *ui;

    QAction *pActionBack;
    QAction *pActionOption;

    QPointer<QGeoPositionInfoSource> locationDataSource;
    QGeoPositionInfo myPositionInfo;
};

#endif // MAINWINDOW_H
