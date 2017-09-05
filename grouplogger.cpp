#include "grouplogger.h"

#include <QDebug>
#include <QDir>
#include <QQmlContext>

GroupLogger::GroupLogger(QObject *parent) :
    QObject(parent), mQmlRoot(0), mLogging(false), mFileWriteTime(0)
{
    mLogPath = QLatin1String("");
}

GroupLogger::~GroupLogger()
{
    closeLogFiles();
}

void GroupLogger::addGroup(const QString &groupName, const QString &expression, QStringList tags)
{
    Group grp;

    grp.name = groupName;
    grp.expression = expression;
    grp.tags = tags;

    mGroupMap[groupName] = grp;
}

void GroupLogger::newData(QMap<QString, QVariant> data)
{
    QMapIterator<QString, Group> i(mGroupMap);
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

    while (i.hasNext()) {
        i.next();
        QMetaObject::invokeMethod(mQmlRoot, "shouldLogData",
                                  Q_RETURN_ARG(QVariant, shouldLog),
                                  Q_ARG(QVariant, i.value().expression));

        mLoggingMap[i.key()] = shouldLog.toBool();
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

                    //Add the headers to the file
                    *ts << "Time";
                    QStringList tags = i.value().tags;
                    foreach(QString tag, tags) {
                        *ts << "," << tag;
                    }
                    *ts << endl;
                } else {
                    //Unable to create the mapping
                    qDebug() << "Unable to open file " << f->fileName();
                    continue;
                }
            }

            QPair<QFile* , QTextStream*> dataFile = mFileMap[i.key()];
            *(dataFile.second) << now.toString(Qt::ISODate);
            QStringList tags = i.value().tags;
            foreach(QString tag, tags) {
                *(dataFile.second) << "," << data[tag.trimmed()].toString();
            }
            *(dataFile.second)  << endl;
        }
    }

    mFileWriteTime = t.elapsed();
}

int GroupLogger::fileWriteTime()
{
    return mFileWriteTime;
}

bool GroupLogger::logging(){
    return mLogging;
}

void GroupLogger::setLogging(bool l) {
    qDebug() << "Group Logger: logging" << l << mLogPath;
    if (l != mLogging) {
        mLogging = l;

        if (!mLogging) {
            closeLogFiles();
        }

        emit loggingChanged(mLogging);
    }
}

void GroupLogger::closeLogFiles()
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

QString GroupLogger::logPath()
{
    return mLogPath;
}

void GroupLogger::setLogPath(const QString &path)
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

void GroupLogger::setRoot(QObject *r)
{
    mQmlRoot = r;
}

bool GroupLogger::groupLogging(const QString &group)
{
    return mLoggingMap[group];
}
