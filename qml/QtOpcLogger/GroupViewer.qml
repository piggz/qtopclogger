import QtQuick 2.3
import QtQuick.Controls 1.4

Item {
    visible: true

    Label {
        id: txtTitle
        text: "Group Viewer"
        font.underline: true
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
    }

    TreeView {
        id: groupTree
        anchors.top: txtTitle.bottom
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        anchors.margins: 10

        model: GroupModel

        onDoubleClicked: {
            if (GroupModel.hasChildren(index)) {
                var groupname = GroupModel.data(index, 0x100); //0x100 is the User role
                PlotDialog.setTitle(groupname);
                for (var i = 0; i < GroupModel.rowCount(index); ++i) {
                    var tag = GroupModel.data(GroupModel.index(i, 0, index), 0x100);
                    if (i == 0) {
                        PlotDialog.setData(tag, OPCHistory.keys(), OPCHistory.values(tag));
                    } else {
                        var typ = tagType(tag);
                        if (typ === "Boolean") {
                            PlotDialog.addBoolData(tag, OPCHistory.keys(), OPCHistory.values(tag));
                        } else {
                            PlotDialog.addData(tag, OPCHistory.keys(), OPCHistory.values(tag));

                        }
                    }
                    PlotDialog.show();
                }
            }
        }

        TableViewColumn {
            title: "Name"
            role: "groupname"
            width: groupTree.width * 0.75
        }

        TableViewColumn {
            title: "Data"
            role: "groupdata"
            width: groupTree.width * 0.25
            delegate: Item {
                Label {
                    visible: !rectLogging.visible
                    text: isNumeric(styleData.value) ? styleData.value.toFixed(2) : styleData.value
                }
                Rectangle {
                    id: rectLogging
                    visible: styleData.value === "<LOGGING>" || styleData.value === "<NOTLOGGING>"
                    y: 1
                    x: 1
                    height: parent.height - 2
                    width: height
                    radius: width / 2
                    color: styleData.value === "<LOGGING>" ? "#00FF00" : "#FF0000"
                }
            }
        }

    }
}

