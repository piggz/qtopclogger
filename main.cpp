#include "livedatamodel.h"
#include "qmlsettings.h"
#include "plotdialog.h"
#include "opchistory.h"
#include "fileio.h"
#include "groupdatamodel.h"
#include "opclogger.h"
#include "grouplogger.h"
#include "reporttemplatemodel.h"

#include <qtopc_global.h>
#include <opccontroller.h>
#include <opcdaservermodel.h>
#include <opctagmodel.h>

#include <QApplication>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QtQml/QtQml>
#include <QDebug>
#include <QtWebView/QtWebView>

void logMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QDateTime now = QDateTime::currentDateTimeUtc();
    QFile f("./debug.log");
    if (f.open(QFile::WriteOnly | QFile::Append | QFile::Text)) {
        QTextStream ts(&f);
        ts << now.toString(Qt::ISODate) << " " << msg << "\n";
        f.close();
    }
}

void noMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(type);
    Q_UNUSED(context);
    Q_UNUSED(msg);
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(logMessageOutput);
    //qInstallMessageHandler(noMessageOutput);
    QApplication app(argc, argv);

    QtWebView::initialize();

    qmlRegisterType<FileIO, 1>("FileIO", 1, 0, "FileIO");
    qRegisterMetaType<QVector<double> > ("QVector<double>");
    qmlRegisterType<OPCDAServerModel>("OPCDAServerModel", 1, 0, "OPCDAServerModel");
    qmlRegisterType<OPCTagModel>("OPCTagModel", 1, 0, "OPCTagModel");

    QCoreApplication::setApplicationName("QtOpcLogger");
    QCoreApplication::setOrganizationName("ACME");

    QQmlApplicationEngine engine;

    LiveDataModel liveData;
    QMLSettings appSettings;
    OPCDAServerModel daServerModel("");
    PlotDialog plotDialog;
    OPCHistory history;
    GroupDataModel groupModel;
    OPCLogger logger;
    GroupLogger groupLogger;
    ReportTemplateModel reportTemplates;

    groupModel.setLogger(&groupLogger);

    OPCController controller(&engine);
    controller.registerDataReceiver(&liveData); //LiveData model requires data first so logger can check values
    controller.registerDataReceiver(&logger);
    controller.registerDataReceiver(&history);
    controller.registerDataReceiver(&groupLogger);
    controller.registerDataReceiver(&groupModel);

    engine.rootContext()->setContextProperty("OPCController", &controller);
    engine.rootContext()->setContextProperty("TagModel", controller.tagModel());
    //engine.rootContext()->setContextProperty("LoggerController", &loggerController);
    engine.rootContext()->setContextProperty("OPCLogger", &logger);
    engine.rootContext()->setContextProperty("LiveData", &liveData);
    engine.rootContext()->setContextProperty("Settings", &appSettings);
    engine.rootContext()->setContextProperty("DAServerModel", &daServerModel);
    engine.rootContext()->setContextProperty("PlotDialog", &plotDialog);
    engine.rootContext()->setContextProperty("OPCHistory", &history);
    engine.rootContext()->setContextProperty("GroupLogger", &groupLogger);
    engine.rootContext()->setContextProperty("GroupModel", &groupModel);
    engine.rootContext()->setContextProperty("ReportModel", &reportTemplates);

    qDebug() << "DA Servers:" << daServerModel.rowCount(QModelIndex()) << daServerModel.roleNames();

    engine.load(QUrl(QStringLiteral("qrc:/qml/QtOpcLogger/main.qml")));

    logger.setRoot(engine.rootObjects()[0]);
    groupLogger.setRoot(engine.rootObjects()[0]);
    plotDialog.setRoot(engine.rootObjects()[0]);

    //loggerController.startThread();

    return app.exec();
}
