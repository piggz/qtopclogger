#ifndef GROUPDATAMODEL_H
#define GROUPDATAMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <opcdatareceiver.h>

class GroupLogger;

class GroupDataModel : public QAbstractItemModel, public OPCDataReceiver
{
    Q_OBJECT

public:

    class GroupItem {
    public:
        explicit GroupItem(const QString &name, bool group, GroupItem *parent = 0);
        ~GroupItem();

        void appendChild(GroupItem *child);
        GroupItem *child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        int row() const;
        GroupItem *parentItem();
        void setValue(const QVariant& value);
    private:
        QList<GroupItem*> m_childItems;
        QString m_name;
        QVariant m_value;
        bool m_group;
        GroupItem *m_parentItem;
    };

    explicit GroupDataModel(QObject *parent = 0);
    ~GroupDataModel();

    virtual void newData(QMap<QString, QVariant> data);

    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QModelIndex parent(const QModelIndex &child) const;

    Q_INVOKABLE void addGroup(const QString &groupName, QStringList tags);
    Q_INVOKABLE void clearGroups();
    void setLogger(GroupLogger *logger);
private:
    GroupItem *m_rootItem;

    GroupLogger *m_logger;
};

#endif // GROUPDATAMODEL_H
