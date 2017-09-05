#ifndef PLOTDIALOG_H
#define PLOTDIALOG_H

#include <QDialog>
#include "qcustomplot.h"

namespace Ui {
class PlotDialog;
}

class PlotDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotDialog(QWidget *parent = 0);
    ~PlotDialog();

    Q_INVOKABLE void setTitle(const QString& tag);
    Q_INVOKABLE void setData(const QString &tag, const QVector<double> &key, const QVector<double> &value);
    Q_INVOKABLE void addData(const QString& tag, const QVector<double> &key, const QVector<double> &value);
    Q_INVOKABLE void addBoolData(const QString& tag, const QVector<double> &key, const QVector<double> &value);

    void setRoot(QObject *r);

private slots:
    void on_btnSavePDF_clicked();
    void on_btnSavePNG_clicked();

    void axisClicked(QCPAxis *axis, QCPAxis::SelectablePart, QMouseEvent *event);
    void plotMousePress(QMouseEvent*);
    void plotMouseRelease(QMouseEvent*);
    void plotMouseMove(QMouseEvent*);

    void on_btnLoadFile_clicked();

    void on_btnAddFile_clicked();

    void on_chkTracer_clicked(bool checked);

private:
    void calculateGradient();
    void clearLabels();

    Ui::PlotDialog *ui;

    QCustomPlot *m_plot;
    QCPPlotTitle *m_title;
    QCPMarginGroup *m_group;

    QCPItemTracer *m_tracerStart;
    QCPItemTracer *m_tracerEnd;

    double m_startX;
    double m_startY;
    double m_endX;
    double m_endY;

    QList<QColor> m_graphColors;
    unsigned int m_nextColor;

    QColor nextColor();

    QObject *mQmlRoot;
};

#endif // PLOTDIALOG_H
