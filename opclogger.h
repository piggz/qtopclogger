#ifndef OPCLOGGER_H
#define OPCLOGGER_H

#include <QObject>
#include <opcdatareceiver.h>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QPair>
#include <QDateTime>
#include <QQmlEngine>

class OPCLogger : public QObject, public OPCDataReceiver
{
    Q_OBJECT
public:
    explicit OPCLogger(QObject *parent = 0);
    ~OPCLogger();

    struct Tag{
        QString name;
        QString logType;
        QString expression;
    };

    Q_PROPERTY(bool logging READ logging WRITE setLogging NOTIFY loggingChanged)
    Q_PROPERTY(QString logPath READ logPath WRITE setLogPath NOTIFY logPathChanged)

    bool logging();
    void setLogging(bool l);
    void setRoot(QObject *r);

    QString logPath();
    void setLogPath(const QString &path);
signals:
    void loggingChanged(bool l);
    void logPathChanged(const QString &p);

public slots:
    virtual void newData(QMap<QString, QVariant> data);
    void addTag(const QString &name, const QString &logType, const QString &expression);
    int fileWriteTime();

private:
    QMap<QString, QPair<QFile*, QTextStream*> > mFileMap;
    QMap<QString, Tag> mTagMap;
    QMap<QString, QVariant> mOldData;

    QObject *mQmlRoot;
    int mFileWriteTime;
    bool mLogging;
    QString mLogPath;
    QDateTime mLastLogTime;

    void closeLogFiles();
};

#endif // OPCLOGGER_H
