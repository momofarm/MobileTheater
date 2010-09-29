#ifndef QURLFACTORY_H
#define QURLFACTORY_H
#include <QObject>
#include <QDebug>

class QUrlFactory : public QObject
{
    Q_OBJECT

public:
    QUrlFactory(QObject *pParent, QString strParm):
            QObject(pParent)
    {
        //  dummy function, please implement......
        //Q_ASSERT(FALSE);

    };

    virtual QString GetParm() = 0;

public slots:
    virtual void DealResult(QByteArray &result) = 0;

protected:

};

#endif // QURLFACTORY_H
