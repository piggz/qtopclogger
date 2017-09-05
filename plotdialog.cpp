#include "plotdialog.h"
#include "ui_plotdialog.h"

#include <QDebug>

PlotDialog::PlotDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlotDialog)
{
    ui->setupUi(this);
    m_plot = new QCustomPlot(this);
    m_plot->addGraph();

    m_plot->plotLayout()->setRowSpacing(0);
    m_plot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    m_plot->xAxis->setDateTimeFormat("MM-dd hh:mm:ss");

    m_plot->xAxis->setLabel("Time");
    m_plot->yAxis->setLabel("Value");
    m_plot->yAxis2->setVisible(false);

    m_group = new QCPMarginGroup(m_plot);
    m_plot->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, m_group);
    m_plot->axisRect()->setMargins(QMargins(0,0,0,0));
    m_plot->plotLayout()->setRowSpacing(0);

    m_plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectItems | QCP::iSelectAxes);

    m_title = new QCPPlotTitle(m_plot, "Title");
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0,0,m_title);
    m_plot->axisRect()->setRangeZoomAxes(0, 0);

    m_tracerStart = new QCPItemTracer(m_plot);
    m_tracerEnd = new QCPItemTracer(m_plot);

    m_tracerStart->setPen(QColor(0,192,0));
    m_tracerEnd->setPen(QColor(192,0,0));

    m_tracerStart->setGraph(m_plot->graph(0));
    m_tracerEnd->setGraph(m_plot->graph(0));

    m_tracerStart->setVisible(false);
    m_tracerEnd->setVisible(false);

    connect(m_plot, SIGNAL(axisClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisClicked(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)));
    connect(m_plot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(plotMousePress(QMouseEvent*)));
    connect(m_plot, SIGNAL(mouseRelease(QMouseEvent*)), this, SLOT(plotMouseRelease(QMouseEvent*)));
    connect(m_plot, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(plotMouseMove(QMouseEvent*)));

    ui->verticalLayout->addWidget(m_plot);
    m_plot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_graphColors << QColor(255,0,0);
    m_graphColors << QColor(0,255,0);
    m_graphColors << QColor(0,0,255);
    m_graphColors << QColor(255,0,255);
    m_graphColors << QColor(0,192,255);
    m_graphColors << QColor(255,128,0);
    m_graphColors << QColor(128,0,0);
    m_graphColors << QColor(0,128,0);
    m_graphColors << QColor(0,0,128);
    m_graphColors << QColor(128,0,128);
    m_graphColors << QColor(0,128,128);
    m_graphColors << QColor(128,128,0);

    m_nextColor = 0;
}

PlotDialog::~PlotDialog()
{
    delete ui;
}

void PlotDialog::setData(const QString &tag, const QVector<double> &key, const QVector<double> &value)
{
    m_nextColor = 0;

    m_plot->graph(0)->setData(key, value);
    m_plot->graph(0)->rescaleAxes();
    m_plot->graph(0)->setPen(nextColor());

    m_plot->yAxis->setLabel(tag);
    m_plot->yAxis->setLabelColor(m_plot->graph(0)->pen().color());

    //Delete additional axisrects
    unsigned int ac = m_plot->axisRectCount();
    for (unsigned int i = 1; i < ac; ++i) {
        QCPAxisRect *a = m_plot->axisRects().takeLast();
        m_plot->plotLayout()->remove(a);
    }
    m_plot->plotLayout()->simplify();

    //Delete additional graphs and axis
    unsigned int graphCount = m_plot->graphCount();
    for (unsigned int i = 1; i < graphCount; ++i) {
        m_plot->axisRect()->removeAxis(m_plot->axisRect()->axis(QCPAxis::atLeft, 1));
        m_plot->removeGraph(m_plot->graph(1));
    }
    m_plot->replot();
}

void PlotDialog::addData(const QString &tag, const QVector<double> &key, const QVector<double> &value)
{
    QCPAxis *ax = m_plot->axisRect()->addAxis(QCPAxis::atLeft);
    ax->setLabel(tag);
    QCPGraph *gra = m_plot->addGraph(m_plot->xAxis, ax);
    gra->setData(key, value);
    gra->setPen(nextColor());
    ax->setLabelColor(gra->pen().color());
    ax->setTickLabelPadding(2);
    ax->setLabelPadding(2);

    gra->rescaleAxes();

    m_plot->replot();
}

void PlotDialog::addBoolData(const QString &tag, const QVector<double> &key, const QVector<double> &value)
{
    QCPAxisRect *boolAxisRect = new QCPAxisRect(m_plot, false);
    m_plot->plotLayout()->addElement(m_plot->plotLayout()->rowCount(),0,boolAxisRect);
    boolAxisRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 50));
    boolAxisRect->setAutoMargins(QCP::msLeft | QCP::msRight | QCP::msBottom);
    boolAxisRect->setMargins(QMargins(0,0,0,0));

    QCPAxis *lax = boolAxisRect->addAxis(QCPAxis::atLeft);
    lax->setAutoTickLabels(true);
    lax->setTickStep(1);
    lax->setRangeLower(0);
    lax->setRangeUpper(1);
    lax->setAutoTickCount(1);
    lax->setSubTickCount(0);
    lax->setTickLabels(true);

    QCPAxis *bax = boolAxisRect->addAxis(QCPAxis::atBottom);
    bax->setTickLabels(false);
    bax->setTickLabelType(QCPAxis::ltDateTime);
    bax->setDateTimeFormat("MM-dd hh:mm:ss");
    bax->setLabel(tag);

    boolAxisRect->axis(QCPAxis::atBottom)->setLayer("axes");
    boolAxisRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");

    boolAxisRect->setMarginGroup(QCP::msLeft|QCP::msRight, m_group);

    QCPGraph *gra = m_plot->addGraph(bax, lax);
    gra->setData(key, value);
    gra->setPen(nextColor());
    lax->setLabelColor(gra->pen().color());
    lax->setTickLabelPadding(2);
    lax->setLabelPadding(2);

    connect(m_plot->xAxis, SIGNAL(rangeChanged(QCPRange)), bax, SLOT(setRange(QCPRange)));

    gra->rescaleAxes();

    m_plot->replot();
}

void PlotDialog::setTitle(const QString &tag)
{
    setWindowTitle(tag);
    m_title->setText(tag);
}

void PlotDialog::on_btnSavePDF_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QString(), "PDF (*.pdf)");

    if (!fileName.isEmpty()) {
        m_plot->savePdf(fileName);
    }
}

void PlotDialog::on_btnSavePNG_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PNG", QString(), "PNG (*.png)");

    if (!fileName.isEmpty()) {
        m_plot->savePng(fileName);
    }
}

void PlotDialog::axisClicked(QCPAxis *axis, QCPAxis::SelectablePart, QMouseEvent *event)
{
    if (axis->axisType() == QCPAxis::atBottom) {
        m_plot->axisRect()->setRangeZoomAxes(axis, 0);
    } else if (axis->axisType() == QCPAxis::atLeft || axis->axisType() == QCPAxis::atRight) {
        m_plot->axisRect()->setRangeZoomAxes(0, axis);
        m_plot->axisRect()->setRangeDragAxes(m_plot->xAxis, axis);
    }

}

void PlotDialog::plotMousePress(QMouseEvent *e)
{
    if (e->modifiers() && Qt::ShiftModifier) {
        clearLabels();
        m_plot->setInteraction(QCP::iRangeDrag, false);

        m_tracerStart->setGraphKey(m_plot->xAxis->pixelToCoord(e->pos().x()));
        m_plot->replot();
        m_startX = m_tracerStart->position->key();
        m_startY = m_tracerStart->position->value();

        ui->lblStartTime->setText(QDateTime::fromTime_t(m_startX).toString(Qt::RFC2822Date));
        ui->lblStartValue->setText(QString::number(m_startY));
        e->accept();

    }
}

void PlotDialog::plotMouseRelease(QMouseEvent *e)
{
    if (e->modifiers() && Qt::ShiftModifier) {
        m_tracerEnd->setGraphKey(m_plot->xAxis->pixelToCoord(e->pos().x()));
        m_plot->replot();
        m_endX = m_tracerEnd->position->key();
        m_endY = m_tracerEnd->position->value();
        calculateGradient();

        e->accept();

    }
    m_plot->setInteraction(QCP::iRangeDrag, true);
}

void PlotDialog::plotMouseMove(QMouseEvent *e)
{
    if (e->modifiers() && Qt::ShiftModifier) {
        m_tracerEnd->setGraphKey(m_plot->xAxis->pixelToCoord(e->pos().x()));
        m_plot->replot();
        m_endX = m_tracerEnd->position->key();
        m_endY = m_tracerEnd->position->value();

        calculateGradient();

        e->accept();
    }
}

void PlotDialog::calculateGradient()
{
    ui->lblEndTime->setText(QDateTime::fromTime_t(m_endX).toString(Qt::RFC2822Date));
    ui->lblEndValue->setText(QString::number(m_endY));

    //Calculate Gradient
    double timediff = m_endX - m_startX;
    double valdiff = m_endY - m_startY;

    ui->lblTimeDifference->setText(QString::number(timediff / 60));
    ui->lblValueDifference->setText(QString::number(valdiff));
    double grad = valdiff / (timediff / 60);
    ui->lblGradient->setText(QString::number(grad) + QLatin1String(" (units/minute)"));
}

void PlotDialog::clearLabels()
{
    ui->lblStartTime->setText(QString());
    ui->lblStartValue->setText(QString());
    ui->lblEndTime->setText(QString());
    ui->lblEndValue->setText(QString());

    ui->lblTimeDifference->setText(QString());
    ui->lblValueDifference->setText(QString());
    ui->lblGradient->setText(QString());
}

void PlotDialog::on_btnLoadFile_clicked()
{
    QSettings s;
    QString loadFile = QFileDialog::getOpenFileName(this, "Open CSV", s.value("LogPath").toString(), "CSV (*.csv)");

    QString tag;
    if (!loadFile.isEmpty()) {
        qDebug() << loadFile;
        tag = loadFile.mid(loadFile.lastIndexOf("/") + 1);
        tag = tag.mid(0, tag.lastIndexOf("_"));
        qDebug() << tag;

        QFile file(loadFile);

        QVector<double> dataX;
        QList<QVector<double> > dataY;
        if ( file.open(QIODevice::ReadOnly) ) {
            QString line;
            QStringList csv;
            QTextStream t( &file );
            unsigned int colCount = 0;
            QStringList columnNames;
            bool first = true;
            do {
                line = t.readLine();
                csv = line.split(",");
                if (first) {
                    columnNames = csv;
                    first = false;
                    colCount = csv.count();
                    QVector<double> y;
                    for (unsigned int i = 1; i < colCount; ++i) {
                        dataY.append(y);
                    }
                }
                if (csv.count() == colCount) { //valid data
                    //dataY.reserve(csv.count() - 1);
                    QDateTime dt = QDateTime::fromString(csv.at(0), Qt::ISODate);
                    if (dt.isValid()){
                        dataX.append(dt.toTime_t());

                        for (unsigned int i = 1; i < colCount; ++i) {
                            if (csv.at(i).toLower() == "true" ) {
                                dataY[i-1].append(1.0);
                            } else if (csv.at(i).toLower() == "false" ) {
                                dataY[i-1].append(0.0);
                            } else {
                                dataY[i-1].append(csv.at(i).toDouble());
                            }
                        }
                    }
                    //printf("%d\n", dataY.count());
                }
            } while (!line.isNull());
            qDebug() << "finished read";
            file.close();

            setTitle(tag);

            qDebug() << "Adding data to plot" << dataY.count() << endl;
            setData(columnNames[1], dataX, dataY.at(0));

            QVariant tagType;

            for (unsigned int i = 1; i < colCount - 1; ++i) {
                QMetaObject::invokeMethod(mQmlRoot, "tagType",
                                          Q_RETURN_ARG(QVariant, tagType),
                                          Q_ARG(QVariant, columnNames[i+1]));
                if (tagType.toString() == "Boolean") {
                    addBoolData(columnNames[i+1], dataX, dataY[i]);
                } else {
                    addData(columnNames[i+1], dataX, dataY[i]);
                }
            }

        }
    }
}

void PlotDialog::on_btnAddFile_clicked()
{
    QSettings s;
    QString loadFile = QFileDialog::getOpenFileName(this, "Add CSV", s.value("LogPath").toString(), "CSV (*.csv)");

    QString tag;
    if (!loadFile.isEmpty()) {
        qDebug() << loadFile;
        tag = loadFile.mid(loadFile.lastIndexOf("/") + 1);
        tag = tag.mid(0, tag.lastIndexOf("_"));
        qDebug() << tag;

        QFile file(loadFile);

        QVector<double> dataX;
        QVector<double> dataY;
        if ( file.open(QIODevice::ReadOnly) ) {
            QString line;
            QStringList csv;
            QTextStream t( &file );
            bool first = true;
            bool valid = false;
            do {
                line = t.readLine();
                csv = line.split(",");

                if (first) {
                    if (csv.count() == 2) {
                        valid = true;
                    }
                    first = false;
                }

                if (csv.count() == 2) { //valid data
                    dataX.append(QDateTime::fromString(csv.at(0), Qt::ISODate).toTime_t());
                    if (csv.at(1).toLower() == "true" ) {
                        dataY.append(1.0);
                    } else if (csv.at(1).toLower() == "false" ) {
                        dataY.append(0.0);
                    } else {
                        dataY.append(csv.at(1).toDouble());
                    }
                }
            } while (!line.isNull() && valid);

            file.close();

            if (valid) {
                QVariant tagType;
                QMetaObject::invokeMethod(mQmlRoot, "tagType",
                                          Q_RETURN_ARG(QVariant, tagType),
                                          Q_ARG(QVariant, tag));
                if (tagType.toString() == "Boolean") {
                    addBoolData(tag, dataX, dataY);
                } else {
                    addData(tag, dataX, dataY);
                }
            }
        }
    }
}

QColor PlotDialog::nextColor()
{
    QColor next = m_graphColors[m_nextColor];
    m_nextColor++;
    if (m_nextColor > 11) {
        m_nextColor = 0;
    }
    return next;
}

void PlotDialog::on_chkTracer_clicked(bool checked)
{
    m_tracerStart->setVisible(checked);
    m_tracerEnd->setVisible(checked);
    m_plot->replot();
}

void PlotDialog::setRoot(QObject *r)
{
    mQmlRoot = r;
}
