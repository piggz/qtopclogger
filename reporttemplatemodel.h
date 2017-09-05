#ifndef REPORTTEMPLATEMODEL_H
#define REPORTTEMPLATEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QStringList>

class ReportTemplateModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ReportTemplateModel();

    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

private:

    QStringList mTemplates;
};

#endif // REPORTTEMPLATEMODEL_H
