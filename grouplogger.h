#ifndef GROUPLOGGER_H
#define GROUPLOGGER_H

#include <QObject>
#include <opcdatareceiver.h>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QPair>
#include <QDateTime>
#include <QQmlEngine>

class GroupLogger : public QObject, public OPCDataReceiver
{
    Q_OBJECT

public:
    explicit GroupLogger(QObject *parent = 0);
    ~GroupLogger();

    struct Group{
        QString name;
        QString expression;
        QStringList tags;
    };

    Q_PROPERTY(bool logging READ logging WRITE setLogging NOTIFY loggingChanged)
    Q_PROPERTY(QString logPath READ logPath WRITE setLogPath NOTIFY logPathChanged)

    bool logging();
    void setLogging(bool l);
    void setRoot(QObject *r);

    QString logPath();
    void setLogPath(const QString &path);

    bool groupLogging(const QString &group);

signals:
    void loggingChanged(bool l);
    void logPathChanged(const QString &p);

public slots:
    virtual void newData(QMap<QString, QVariant> data);
    int fileWriteTime();
    void addGroup(const QString &groupName, const QString &expression, QStringList tags);

private:
    QMap<QString, QPair<QFile*, QTextStream*> > mFileMap;
    QMap<QString, Group> mGroupMap;
    QMap<QString, bool> mLoggingMap;

    QObject *mQmlRoot;
    int mFileWriteTime;
    bool mLogging;
    QString mLogPath;
    QDateTime mLastLogTime;

    void closeLogFiles();
};

#endif // GROUPLOGGER_H
