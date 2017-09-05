#ifndef OPCHISTORY_H
#define OPCHISTORY_H

#include <QObject>
#include <opcdatareceiver.h>
#include <QMap>
#include <QPair>
#include <QDateTime>
#include <QVector>
#include <QVariant>

class OPCHistory : public QObject, public OPCDataReceiver
{
    Q_OBJECT
public:
    explicit OPCHistory();
    ~OPCHistory();

public slots:
    virtual void newData(QMap<QString, QVariant> data);
    QVector<double> keys();
    QVector<double> values(const QString& tag);
    void enableLogging();
    void setHistorySize(int histSize);

private:
    QMap<QString, QVector<double> > m_historyValues;
    QVector<double> m_timeHistory;

    bool m_skipData;
    int m_historySize;
};

#endif // OPCHISTORY_H
