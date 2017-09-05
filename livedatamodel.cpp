#include "livedatamodel.h"
#include <QDebug>

LiveDataModel::LiveDataModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void LiveDataModel::newData(QMap<QString, QVariant> data)
{
    mOldData = mData;

    //TODO There are bugs in this, if data contains items not in mData
    //but is the same size

    if (mData.size() != data.size()) {
        beginResetModel();
        mData = data;
        endResetModel();
        return;
    }

    mData = data;
    int r = 0;
    foreach(QString key, data.keys()) {
        mData[key] = data.value(key);
        emit dataChanged(index(r), index(r));
        ++r;
    }


}

int LiveDataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mData.size();
}

QVariant LiveDataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::UserRole) {
        return mData.keys().at(index.row());
    } else if (role == Qt::UserRole + 1) {
        return mData.values().at(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> LiveDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Qt::UserRole] = "opckey";
    roles[Qt::UserRole + 1] = "opcvalue";

    return roles;
}

QVariant LiveDataModel::currentData(const QString &tag)
{
    return mData[tag];
}

QVariant LiveDataModel::oldData(const QString &tag)
{
    return mOldData[tag];
}
