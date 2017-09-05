#include "groupdatamodel.h"
#include "grouplogger.h"
#include <QDebug>

GroupDataModel::GroupItem::GroupItem(const QString &name, bool group, GroupItem *parent)
{
    m_name = name;
    m_group = group;
    m_parentItem = parent;
}

GroupDataModel::GroupItem::~GroupItem()
{
    qDeleteAll(m_childItems);
}

void GroupDataModel::GroupItem::appendChild(GroupItem *child)
{
    m_childItems.append(child);
}

GroupDataModel::GroupItem* GroupDataModel::GroupItem::child(int row)
{
    return m_childItems.value(row);
}

int GroupDataModel::GroupItem::childCount() const
{
    return m_childItems.count();
}

int GroupDataModel::GroupItem::row() const
{
    if (m_parentItem) {
        return m_parentItem->m_childItems.indexOf(const_cast<GroupItem*>(this));
    }
    return 0;
}

int GroupDataModel::GroupItem::columnCount() const
{
    //if (m_group) {
    //    return 1;
    //}
    return 2;
}

QVariant GroupDataModel::GroupItem::data(int column) const
{
    if (column == 0) {
        return m_name;
    } else {
        if (m_group) {
            return m_value.toBool() ? QStringLiteral("<LOGGING>") : QStringLiteral("<NOTLOGGING>");
        } else {
            return m_value;
        }
    }
    return 0;
}

GroupDataModel::GroupItem* GroupDataModel::GroupItem::parentItem()
{
    return m_parentItem;
}

void GroupDataModel::GroupItem::setValue(const QVariant &value)
{
    m_value = value;
}

//======================

GroupDataModel::GroupDataModel(QObject *parent) : QAbstractItemModel(parent), m_logger(0)
{
    m_rootItem = new GroupItem("Groups", true, 0);
}

GroupDataModel::~GroupDataModel()
{
    delete m_rootItem;
}

QModelIndex GroupDataModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }

    GroupItem *parentItem;

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = static_cast<GroupItem*>(parent.internalPointer());
    }

    GroupItem *childItem = parentItem->child(row);

    if (childItem) {
        return createIndex(row, column, childItem);
    } else {
        return QModelIndex();
    }
}

QModelIndex GroupDataModel::parent(const QModelIndex &child) const
{
    if(!child.isValid()) {
        return QModelIndex();
    }
    GroupItem *childItem = static_cast<GroupItem*>(child.internalPointer());
    GroupItem *parentItem = childItem->parentItem();

    if (parentItem == m_rootItem) {
        return QModelIndex();
    }
    return createIndex(parentItem->row(), 0, parentItem);
}

int GroupDataModel::rowCount(const QModelIndex &parent) const
{
    GroupItem *parentItem;

    if (parent.column() > 0) {
        return 0;
    }

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = static_cast<GroupItem*>(parent.internalPointer());
    }

    return parentItem->childCount();
}

int GroupDataModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) {
        return static_cast<GroupItem*>(parent.internalPointer())->columnCount();
    } else {
        return m_rootItem->columnCount();
    }
}

QVariant GroupDataModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    GroupItem *item = static_cast<GroupItem*>(index.internalPointer());
    if (role == Qt::UserRole) {
        return item->data(0);
    } else if (role == Qt::UserRole+1) {
        return item->data(1);
    }

    return QVariant();
}

void GroupDataModel::addGroup(const QString &groupName, QStringList tags)
{
    beginResetModel();
    GroupItem *group = new GroupItem(groupName, true, m_rootItem);

    foreach(QString tag, tags) {
        GroupItem *item = new GroupItem(tag, false, group);
        group->appendChild(item);
    }
    m_rootItem->appendChild(group);
    endResetModel();
}

void GroupDataModel::newData(QMap<QString, QVariant> data)
{
    //Loop the groups
    for (int i = 0; i < m_rootItem->childCount(); ++i) {
        //loop the items
        GroupItem *group = m_rootItem->child(i);
        if (group) {
            for (int j = 0; j < group->childCount(); ++j) {
                GroupItem *item = group->child(j);
                if (item) {
                    item->setValue(data[item->data(0).toString()]);
                    emit dataChanged(index(j, 0, index(i, 0)), index(j, 0,index(i, 0)));
                }
            }
        }
        if (m_logger) {
            group->setValue(m_logger->groupLogging(group->data(0).toString()));
            emit dataChanged(index(i, 0), index(i, 0));
        }
    }
}

QHash<int, QByteArray> GroupDataModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Qt::UserRole] = "groupname";
    roles[Qt::UserRole + 1] = "groupdata";

    return roles;
}

void GroupDataModel::setLogger(GroupLogger *logger)
{
    m_logger = logger;
}

void GroupDataModel::clearGroups()
{
    beginResetModel();
    delete m_rootItem;
    m_rootItem = new GroupItem("Groups", true, 0);
    endResetModel();
}
