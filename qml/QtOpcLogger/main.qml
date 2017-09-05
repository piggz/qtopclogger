import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.1
import FileIO 1.0

ApplicationWindow {
    id:mainWindow
    property string logPath: ""
    property int updateFrequency: 1000
    property int memoryUsage: 5000
    property int dataReadTime: 0
    property int tagWriteTime: 0
    property int groupWriteTime: 0

    property string opcHost: ""
    property string opcServer: ""

    width: 800
    height: 640
    visible: true

    header: ToolBar {
        RowLayout{
            ToolButton {
                id: fileButton
                text: "File"
                onClicked: menu.open()

                Menu {
                    id: menu
                    y: fileButton.height

                    MenuItem { text: "Settings"
                        onTriggered: {
                            settingsWindow.show();
                        }
                    }
                    MenuItem { text: "Close"
                        onTriggered: {
                            mainWindow.close();
                        }
                    }
                }
            }
        }
    }

    footer: ToolBar {
        height: 30
        RowLayout {
            anchors.fill: parent
            Rectangle {
                radius: width / 2
                anchors.margins: 8
                anchors.verticalCenter: parent.verticalCenter
                color: OPCController.connected ? "#00FF00" : "#FF0000"
                Layout.preferredWidth: parent.height - 8
                Layout.preferredHeight: parent.height - 8
            }
            Label {
                id: statusMessage
                anchors.verticalCenter: parent.verticalCenter
                text: OPCController.connectedStatus + ", Tag Logger: " + (OPCLogger.logging ? "Logging" : "Not Logging")
            }
            Item {
                Layout.fillWidth: true
            }
            Button {
                id: btnConnect
                checked: OPCController.connected
                checkable: true
                text: checked ? "Disconnect" : "Connect"
                Layout.preferredHeight: parent.height - 8
                anchors.verticalCenter: parent.verticalCenter

                onClicked: {
                    if (OPCController.connected) {
                        OPCController.disconnectFromServer();
                    } else {
                        OPCController.connectToServer();
                        OPCController.registerTags();
                    }
                }
            }

            Button {
                id: btnPlayStop
                checked: OPCLogger.logging
                checkable: true
                text: checked ? "Stop Logging" : "Start Logging"
                Layout.preferredHeight: parent.height - 8
                anchors.verticalCenter: parent.verticalCenter

                onClicked: {
                    OPCLogger.logging = !OPCLogger.logging
                    GroupLogger.logging = !GroupLogger.logging
                }
            }
        }
    }

    Label {
        id: txtTitle
        text: qsTr("OPC Data Logger")
        font.bold: true
        font.pixelSize: 32
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    SwipeView {
        id: swipeView
        anchors.top: txtTitle.bottom
        anchors.bottom: tabBar.top
        anchors.left: parent.left
        anchors.right: parent.right

        currentIndex: tabBar.currentIndex

        TagEditor {
            id: tagEditor

            onTagsSaved: {
                console.log("Tags Updated.....");
                mainWindow.readTagsDb();
            }
        }

        GroupEditor {
            id: groupEditor

            onGroupsSaved: {
                console.log("Groups Updated.....");
                mainWindow.readGroupsDb();
            }
        }

        TagViewer {
            id: viewTag
        }

        GroupViewer {
            id: viewGroup
        }

        ReportViewer {
            id: viewReport
        }
    }

    TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.left: parent.left

        TabButton {
            text: qsTr("Tag Editor")
        }
        TabButton {
            text: qsTr("Group Editor")
        }
        TabButton {
            text: qsTr("Tag Viewer")
        }
        TabButton {
            text: qsTr("Group Viewer")
        }
        TabButton {
            text: qsTr("Report Viewer")
        }
    }

    ListModel {id: opcLiveItemModel}
    ListModel {id: groupItemModel}

    Window {
        id: settingsWindow
        title: "Settings"
        width: 400
        height: 200
        flags: Qt.Dialog
        minimumHeight: 200

        ColumnLayout {
            anchors.margins: 10
            anchors.fill: parent

            Label {
                text: "Memory Usage:"
            }
            Slider {
                id: sldMemUsage
                to: 10000
                from: 0
                value: Settings.value("MemoryUsage", 5000);
                width: parent.width - 25
            }

            Label {
                id: txtUpdateTime
                text: "Update Frequency (100 - 30000): "
            }

            TextField {
                id: txtEditUpdateTime
                text: updateFrequency
                width: 50
                validator: IntValidator {bottom: 100; top: 30000}
            }
            Label {
                id: txtLogFolder
                text: "Log Folder:"
            }

            TextField {
                id: txtEditLogPath
                text: logPath
                width: parent.width - 25
            }
            Button {
                text: "Ok"
                anchors.right: parent.right

                onClicked: {
                    console.log("Saving...");
                    updateFrequency = txtEditUpdateTime.text;

                    logPath = txtEditLogPath.text;
                    OPCLogger.logPath = logPath;
                    GroupLogger.logPath = logPath

                    memoryUsage = sldMemUsage.value
                    OPCHistory.setHistorySize(memoryUsage);

                    saveSettings();

                    settingsWindow.close();
                }
            }

            //Rest of the space
            Item {
                Layout.alignment: Qt.AlignBottom
                Layout.fillHeight: true
                Layout.preferredWidth: 70
                Layout.preferredHeight: 40
            }
        }
    }

    Timer {
        running: true
        repeat: true
        interval: updateFrequency
        onTriggered: {
            OPCController.readerUpdateTags();

            dataReadTime = OPCController.dataReadTime();
            tagWriteTime = OPCLogger.fileWriteTime();
            groupWriteTime = GroupLogger.fileWriteTime();
        }
    }

    //Delayed startup
    Timer {
        id: tmrDelay
        running: true
        repeat: false
        interval: 5000
        onTriggered: {
            OPCHistory.enableLogging();
        }
    }

    Connections {
        target: TagModel
        property bool done: false;
        onReceivedTags: {
            if (!done) {
                console.log("Tag model updated so reading tags and groups");
                tagEditor.readTagsDb();
                groupEditor.readGroupsDb();
            }
        }
    }

    FileIO {
        id: tagsDb
        source: "tags.db"
        onError: console.log(msg)
    }

    FileIO {
        id: groupsDb
        source: "groups.db"
        onError: console.log(msg)
    }

    Component.onCompleted: {
        loadSettings();
        readTagsDb();
        readGroupsDb();

        //Start logging
        OPCLogger.logging = true;
        GroupLogger.logging = true;
    }

    function loadSettings()
    {
        logPath = Settings.value("LogPath", "C:/OPCLogData/");
        updateFrequency = Settings.value("UpdateFrequency", 1000);
        memoryUsage = Settings.value("MemoryUsage", 5000)

        OPCLogger.logPath = logPath;
        GroupLogger.logPath = logPath;
        OPCHistory.setHistorySize(memoryUsage);
    }

    function saveSettings()
    {
        Settings.setValue("LogPath", logPath);
        Settings.setValue("UpdateFrequency", updateFrequency);
        Settings.setValue("MemoryUsage", memoryUsage);
    }

    function isNumeric(str) {
        return !isNaN(parseFloat(str)) && isFinite(str)
    }

    function readTagsDb() {
        console.log("In read");
        console.time("readTagsDb");
        var tags;

        opcLiveItemModel.clear();

        tags = tagsDb.read();
        var lines = tags.split("\n");

        var lineCount = lines.length;
        //console.log("Lines:", lines, lineCount);
        var line;
        //Loop lines
        for (var i = 0; i < lineCount; ++i) {
            line = lines[i].split(";");
            //console.log(line);
            if (line[0] === "opchost") {
                opcHost = line[1].trim();
            } else if (line[0] === "opcserver") {
                opcServer = line[1].trim();
                OPCController.selectServer(opcHost, opcServer);
            } else if (line[0] === "opcitem") {
                var opcItemData = line[1].split("|||");
                //console.log(opcItemData);
                if (opcItemData.length === 5) {
                    OPCController.addTag(opcItemData[0], opcItemData[1],opcItemData[2]);
                    OPCLogger.addTag(opcItemData[0], opcItemData[3], opcItemData[4]);
                    opcLiveItemModel.append({"opcname": opcItemData[0],"opctag": opcItemData[1].trim(),"opctype": opcItemData[2].trim(),"opclogtype": opcItemData[3].trim(), "opclogexpression": opcItemData[4].trim()})
                }
            }
        }
        OPCController.connectToServer();
        OPCController.registerTags();
        console.timeEnd("readTagsDb");
    }

    function readGroupsDb() {
        console.log("Reading groups.db...");
        var groups;
        var tags;
        groupItemModel.clear();
        GroupModel.clearGroups();

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
                    groupItemModel.append({"groupname": line[0].trim(),"expression": line[1].trim(),"tags": line[2].trim()});
                    GroupLogger.addGroup(line[0].trim(), line[1].trim(), tags);
                    GroupModel.addGroup(line[0].trim(), tags);
                }
            }
        }
    }

    function shouldLogData(expression) {
        //Dangerous but useful
        return Boolean(eval(expression));
    }

    function tagType(tag) {
        for (var i = 0; i < opcLiveItemModel.count; ++i) {
            var itm = opcLiveItemModel.get(i);
            if (itm.opcname === tag) {
                return itm.opctype;
            }
        }
        return "";
    }
}
