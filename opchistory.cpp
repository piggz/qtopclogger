#include "opchistory.h"
#include <QDebug>
#include <QSettings>

OPCHistory::OPCHistory():m_skipData(true)
{
    QSettings settings;
    m_historySize = settings.value("MemoryUsage", 5000).toInt();
}

OPCHistory::~OPCHistory()
{
}

void OPCHistory::newData(QMap<QString, QVariant> data)
{
    if (m_skipData) {
        return;
    }

    QDateTime now = QDateTime::currentDateTimeUtc();

    //Log the time of new data
    m_timeHistory << now.toTime_t();

    if(m_timeHistory.size() > m_historySize) {
        m_timeHistory.pop_front();
    }

    //Loop over the new data
    QMapIterator<QString, QVariant> i(data);

    while (i.hasNext()) {
        i.next();
        m_historyValues[i.key()] << data[i.key()].toDouble();

        if(m_historyValues[i.key()].size() > m_historySize) {
            m_historyValues[i.key()].pop_front();
        }
    }
}

QVector<double> OPCHistory::keys()
{
    return m_timeHistory;
}


QVector<double> OPCHistory::values(const QString &tag)
{
    return m_historyValues[tag];
}

void OPCHistory::enableLogging()
{
    m_skipData = false;
}

void OPCHistory::setHistorySize(int histSize)
{
    m_historySize = histSize;
    m_historyValues.clear();
    m_timeHistory.clear();
}
