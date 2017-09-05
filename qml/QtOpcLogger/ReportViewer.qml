import QtQuick 2.3
import QtQuick.Controls 2.1
import FileIO 1.0
//import QtWebEngine 1.0
import QtWebView 1.0

Item {
    visible: true

    Label {
        id: txtTitle
        text: "Report Viewer"
        font.underline: true
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
    }

    FileIO {
        id: reportTemplate
        onError: console.log(msg)
    }

    FileIO {
        id: reportOutput
        onError: console.log(msg)
    }

    Row {
        id: rowControls
        anchors.top: txtTitle.bottom
        anchors.left: parent.left
        anchors.margins: 10
        spacing: 10
        ComboBox {
            id: cboReportTemplate

            model: ReportModel
        }
        Button {
            id: btnLoadReport
            text: "Load"

            onClicked: {
                web.loadHtml(generateReport(cboReportTemplate.currentText), "./reports/", "");
            }
        }

        /*
        Button {
            id: btnPrint
            text: "Open as PDF"
            onClicked: {
                web.printToPdf("file:///output.pdf", WebEngineView.A4, WebEngineView.Portrait);
                tmrOpenPdf.start();
            }
        }*/
    }

    /*
    WebEngineView {
        id: web
        anchors.top: rowControls.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }*/

    WebView {
        id: web
        anchors.top: rowControls.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        anchors.margins: 10
    }

    Timer {
        id: tmrOpenPdf
        interval: 1000
        running: false

        onTriggered: {
            Qt.openUrlExternally("file://output.pdf");
        }
    }

    function generateReport(report) {
        reportTemplate.source = "./reports/" + report;
        var reportSource = reportTemplate.read();
        var pattern = /\[(.*?)\]/g;

        reportSource = reportSource.replace(pattern, function(match, text, urlId)
        {
            return LiveData.currentData(text);
        });

        return reportSource;
    }

}

