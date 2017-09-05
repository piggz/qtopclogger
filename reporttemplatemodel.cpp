#include "reporttemplatemodel.h"

#include <QDir>
#include <QFileInfoList>

ReportTemplateModel::ReportTemplateModel()
{
    QDir d("./reports/");

    d.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    d.setSorting(QDir::Name);

    QFileInfoList list = d.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        QString fileName = fileInfo.fileName();
        if (fileName.endsWith(".opctemplate")) {
            mTemplates << fileName;
        }
    }
}

int ReportTemplateModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return mTemplates.size();
}

QVariant ReportTemplateModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::UserRole) {
        return mTemplates.at(index.row());
    }

    return QVariant();
}

QHash<int, QByteArray> ReportTemplateModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Qt::UserRole] = "reportname";

    return roles;
}
