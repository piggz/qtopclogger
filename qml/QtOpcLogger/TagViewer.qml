import QtQuick 2.3
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

Item {
    visible: true

    Label {
        id: txtTitle
        text: "Tag Viewer"
        font.underline: true
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
    }

    Label {
        id: txtStats
        text: "Statistics"
        font.underline: true
        font.bold: true
        anchors.left: parent.left
        anchors.top: txtTitle.bottom
        anchors.margins: 10
    }
    Label {
        id: txtReadTime
        text: "Data Read Time: " + dataReadTime + " mSecs"
        anchors.left: parent.left
        anchors.top: txtStats.bottom
        anchors.margins: 10
    }
    Label {
        id: txtTagWriteTime
        text: "Tag Write Time: " + tagWriteTime + " mSecs"
        anchors.left: parent.left
        anchors.top: txtReadTime.bottom
        anchors.margins: 10
    }
    Label {
        id: txtGroupWriteTime
        text: "Group Write Time: " + groupWriteTime + " mSecs"
        anchors.left: parent.left
        anchors.top: txtTagWriteTime.bottom
        anchors.margins: 10
    }
    Label {
        id: txtDataHeader
        text: "Live Data"
        font.underline: true
        font.bold: true
        anchors.left: parent.left
        anchors.top: txtGroupWriteTime.bottom
        anchors.margins: 10
    }

    SystemPalette {
        id: palette
    }

    Component {
        id: opcView


        Item {
            width: parent.width
            height: selected ? btnPlt.y + btnPlt.height + 12 : txtOpcKey.height + 8
            property bool selected: false
            clip: true

            Behavior on height {
                NumberAnimation { duration: 200 }
            }

            Rectangle {
                anchors.fill: parent
                color: palette.midlight

                Rectangle {
                    height: 1
                    width: parent.width
                    anchors.bottom: parent.bottom
                    color: palette.shadow
                }
            }

            Label {
                id: txtOpcKey
                y: 5
                x: 5
                text: opckey
                width: parent.width / 2 - 20
            }
            Label {
                id: txtOpcValue
                y: 5
                anchors.left: txtOpcKey.right
                anchors.margins: 10
                text: isNumeric(opcvalue) ? opcvalue.toFixed(2) : opcvalue
            }

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    selected = !selected;
                }
            }

            Button {
                id: btnPlt
                anchors.right: parent.right
                anchors.top: txtOpcValue.bottom
                anchors.margins: 4
                text: "View Graph"
                onClicked: {
                    PlotDialog.setTitle(opckey);
                    PlotDialog.setData(opckey, OPCHistory.keys(), OPCHistory.values(opckey));
                    PlotDialog.show();
                }
            }

            Button {
                id: btnAddPlt
                anchors.right: btnPlt.left
                anchors.top: txtOpcValue.bottom
                anchors.margins: 4
                text: "Add to Graph"
                onClicked: {
                    //PlotDialog.setTitle(opckey);
                    PlotDialog.addData(opckey, OPCHistory.keys(), OPCHistory.values(opckey));
                    PlotDialog.show();
                }
            }
        }
    }

    ListView {
        id: childData
        flickableDirection: Flickable.VerticalFlick
        ScrollBar.vertical: ScrollBar {}
        clip: true
        anchors.margins: 5
        anchors.top: txtDataHeader.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        model: LiveData
        delegate: opcView
    }


    Connections {
        target: OPCController

        onConnectedChanged: {
            btnConnect.checked = OPCController.connected;
        }
    }
}
