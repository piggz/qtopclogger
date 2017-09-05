#include "qmlsettings.h"

QMLSettings::QMLSettings(QObject *parent) :
    QObject(parent)
{
}

void QMLSettings::setValue(const QString &key, const QVariant &val)
{
    mSettings.setValue(key, val);
}

QVariant QMLSettings::value(const QString &key, const QVariant &def)
{
    return mSettings.value(key, def);
}
