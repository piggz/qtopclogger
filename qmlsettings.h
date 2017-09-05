#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include <QObject>
#include <QSettings>

class QMLSettings : public QObject
{
    Q_OBJECT
public:
    explicit QMLSettings(QObject *parent = 0);


public slots:
    void setValue(const QString &key, const QVariant &val);
    QVariant value(const QString &key, const QVariant &def);

private:
    QSettings mSettings;

};

#endif // QMLSETTINGS_H
