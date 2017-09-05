#include "opclogger.h"

#include <QDebug>
#include <QDir>
#include <QQmlContext>

OPCLogger::OPCLogger(QObject *parent) :
    QObject(parent), mQmlRoot(0), mLogging(false), mFileWriteTime(0)
{
    mLogPath = QLatin1String("");
}

OPCLogger::~OPCLogger()
{
    closeLogFiles();
}

void OPCLogger::newData(QMap<QString, QVariant> data)
{
    QMapIterator<QString, Tag> i(mTagMap);
    QVariant shouldLog;
    QTime t;

    if (!mLogging) {
        return;
    }

    t.start();

    QDateTime now = QDateTime::currentDateTimeUtc();

    if (now.date() > mLastLogTime.date()) { //Date has changed since last log
        closeLogFiles();
    }

    mLastLogTime = now;
    QString theDate = now.toString("yyyyMMdd");
    QString logType;
    while (i.hasNext()) {
        i.next();
        logType = i.value().logType;
        if (logType == "Never") {
            continue;
        } else if (logType == "Always") {
            shouldLog = true;
        } else if (logType == "OnChange") {
            if (data[i.key()] != mOldData[i.key()] ) {
                shouldLog = true;
            }
        } else if (logType == "Expression") {
            QMetaObject::invokeMethod(mQmlRoot, "shouldLogData",
                                      Q_RETURN_ARG(QVariant, shouldLog),
                                      Q_ARG(QVariant, i.value().expression));
        } else {
            continue;
        }

        if (shouldLog.toBool()) {
            if (!mFileMap.contains(i.key())) {  //This key doesnt exist in the file map
                //Create file mapping
                qDebug() << "Creating log file for " << i.key();

                QFile *f = new QFile(mLogPath + "/" + i.key() + "_" + theDate + ".csv");
                if (f->open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
                    QTextStream *ts = new QTextStream(f);
                    QPair<QFile* , QTextStream*> p;
                    p.first = f;
                    p.second = ts;
                    mFileMap[i.key()] = p;
                } else {
                    //Unable to create the mapping
                    qDebug() << "Unable to open file " << f->fileName();
                    continue;
                }
            }
            QPair<QFile* , QTextStream*> dataFile = mFileMap[i.key()];
            *(dataFile.second) << now.toString(Qt::ISODate) << "," << data[i.key()].toString() << endl;
            (dataFile.second)->flush();
        }
    }
    mOldData = data;
    mFileWriteTime = t.elapsed();
}

int OPCLogger::fileWriteTime()
{
    return mFileWriteTime;
}

bool OPCLogger::logging(){
    return mLogging;
}

void OPCLogger::setLogging(bool l) {
    qDebug() << "OPC Logger: logging" << l << mLogPath;
    if (l != mLogging) {
        mLogging = l;

        if (!mLogging) {
            closeLogFiles();
        }

        emit loggingChanged(mLogging);
    }
}

void OPCLogger::closeLogFiles()
{
    //Close all files
    QMapIterator<QString, QPair<QFile*, QTextStream* > > i(mFileMap);

    qDebug() << "Closing all files";

    while (i.hasNext()) {
        i.next();
        QPair<QFile*, QTextStream* > p = i.value();
        p.first->close();
        delete p.second;
        delete p.first;
    }
    mFileMap.clear();
}

QString OPCLogger::logPath()
{
    return mLogPath;
}

void OPCLogger::setLogPath(const QString &path)
{
    qDebug() << "Setting log path to " << path;
    QDir d;
    if (mLogPath != path) {
        if (!d.exists(path)) {
            if (!d.mkpath(path)) {
                //If we cannot make the path, reject the change
                emit logPathChanged(mLogPath);
                return;
            }
        }
        mLogPath = path;
        closeLogFiles();
        emit logPathChanged(mLogPath);
    }
}

void OPCLogger::setRoot(QObject *r)
{
    mQmlRoot = r;
}

void OPCLogger::addTag(const QString &name, const QString &logType, const QString &expression)
{
    Tag tag;

    tag.name = name;
    tag.logType = logType;
    tag.expression = expression;

    mTagMap[name] = tag;
}
