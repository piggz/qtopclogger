import QtQuick 2.3
import QtQuick.Controls 2.1

import FileIO 1.0

Item {

    property string opcHost: ""
    property string opcServer: ""

    signal groupsSaved

    Label {
        id: txtTitle
        text: "Group Editor"
        font.underline: true
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
    }

    Button {
        id: btnAddItem
        text: "Add Group"
        anchors.right: parent.right
        anchors.top: txtTitle.bottom
        anchors.margins: 10

        onClicked: {
            groupItemModel.append({"groupname": "NEW_GROUP","expression": "1","tags": "", "groupdelete": false})
        }
    }

    FileIO {
        id: groupsDb
        source: "groups.db"
        onError: console.log(msg)
    }

    ListModel {id: groupItemModel}

    ListView {
        id: listGroups
        flickableDirection: Flickable.VerticalFlick
        ScrollBar.vertical: ScrollBar {}
        clip: true
        anchors.margins: 10
        anchors.top: btnAddItem.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rowButtons.top
        header: groupItemHeaderComponent
        model: groupItemModel
        delegate: groupItemComponent
    }


    Component {
        id: groupItemHeaderComponent
        Item {
            height: childrenRect.height + 4
            width: parent.width
            Row {
                spacing:4
                width: parent.width
                Label {
                    text: "Group Name"
                    width: parent.width / 6
                }
                Label {
                    text: "Logging Expression"
                    width: parent.width / 3
                }
                Label {
                    text: "Tags (comma separated)"
                    width: parent.width / 3
                }
                Label {
                    text: "Delete"
                    width: parent.width / 6
                }
            }
        }
    }

    Component {
        id: groupItemComponent

        Row {
            property int indexOfThisDelegate: index
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 4
            height: childrenRect.height + 4
            width: parent.width
            TextField {
                id: inpGroupName
                width: parent.width / 6
                text: groupname
                onTextChanged: {
                    groupItemModel.setProperty(parent.indexOfThisDelegate, "groupname", text);
                }
            }

            TextField {
                id: inpExpression
                width: parent.width / 3
                text: expression

                onTextChanged: {
                    groupItemModel.setProperty(parent.indexOfThisDelegate, "expression", text);
                }
            }

            TextField {
                id: inpGroupTags
                width: parent.width / 3
                text: tags

                onTextChanged: {
                    groupItemModel.setProperty(parent.indexOfThisDelegate, "tags", text);
                }
            }

            CheckBox {
                id: chkDelete
                checked: groupdelete
                text: ""
                width: parent.width / 12

                onCheckedChanged: {
                    groupItemModel.setProperty(parent.indexOfThisDelegate, "groupdelete", checked);
                }
            }
        }
    }

    Row {
        id: rowButtons
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        spacing: 10
        height: 50
        Button {
            text: "Load groups.db"
            height: parent.height

            onClicked: {
                readGroupsDb();
            }
        }
        Button {
            text: "Save groups.db"
            height: parent.height
            onClicked: {
                saveGroupsDb();
                readGroupsDb();
                groupsSaved();
            }
            enabled: groupItemModel.count > 0

        }

    }

    function readGroupsDb() {
        console.log("Reading groups.db...");
        var groups;
        var tags;
        groupItemModel.clear();

        groups = groupsDb.read();
        var lines = groups.split("\n");

        var lineCount = lines.length;
        console.log("Lines:", lines, lineCount);
        var line;
        //Loop lines
        for (var i = 0; i < lineCount; ++i) {
            line = lines[i].split("|||");
            console.log(line);
            if (line.length === 3) {
                tags = line[2].split(",");
                if (tags.length > 0) {
                    //Valid group definition
                    groupItemModel.append({"groupname": line[0].trim(),"expression": line[1].trim(),"tags": line[2].trim(), "groupdelete": false});
                }
            }
        }
    }

    function saveGroupsDb() {
        console.log("Saving groups.db...");

        var groupdbtxt = ""

        for (var i = 0; i < groupItemModel.count; ++i) {
            var elem = groupItemModel.get(i);
            if (!elem.groupdelete) {
                groupdbtxt += elem.groupname.trim() + "|||" + elem.expression.trim() + "|||" + elem.tags.trim() + "\n";
            }
        }
        console.log(groupdbtxt);
        groupsDb.write(groupdbtxt);
    }

}

