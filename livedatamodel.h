#ifndef LIVEDATAMODEL_H
#define LIVEDATAMODEL_H

#include <QAbstractListModel>
#include <opcdatareceiver.h>

class LiveDataModel : public QAbstractListModel, public OPCDataReceiver
{
    Q_OBJECT
public:
    explicit LiveDataModel(QObject *parent = 0);
    virtual void newData(QMap<QString, QVariant> data);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;


public slots:
    QVariant currentData(const QString &tag);
    QVariant oldData(const QString &tag);

private:
    QMap<QString, QVariant> mData;
    QMap<QString, QVariant> mOldData;
};

#endif // LIVEDATAMODEL_H
