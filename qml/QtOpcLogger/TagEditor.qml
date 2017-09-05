import QtQuick 2.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import FileIO 1.0
import OPCDAServerModel 1.0
import OPCTagModel 1.0

Item {

    property string opcHost: ""
    property string opcServer: ""

    signal tagsSaved

    Label {
        id: txtTitle
        text: "Tag Editor"
        font.underline: true
        font.bold: true
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.margins: 10
    }

    FileIO {
        id: tagsDb
        source: "tags.db"
        onError: console.log(msg)
    }

    Grid {
        id: grd
        columns: 2
        spacing: 10
        anchors.top: txtTitle.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 10
        height: childrenRect.height

        Label {
            text: "OPC Server Host:"
        }
        TextField  {
            id: inpOPCHost
            width: 400
            text: opcHost
        }

        Label {
            text: "OPC Server:"
        }
        ComboBox {
            id: inpOPCServer
            width: 400
            textRole: "servername"
            model: DAServerModel
            editText: opcServer

            onCurrentIndexChanged: {
                opcServer = editText;
            }
        }
        Label {
            text: "OPC Items:"
        }

    }

    Button {
        id: btnAddItem
        text: "Add Tag"
        anchors.right: scroll.right
        anchors.bottom: scroll.top
        anchors.margins: 10

        onClicked: {
            opcItemModel.append({"opcname": "NEW_TAG","opctagid": -1,"opctypeid": -1, "opclogtypeid": 0, "opclogexpression": "", "opcdeletetag": false})
        }
    }

    ListModel {id: opcItemModel}

    ScrollView{
        id: scroll
        anchors.margins: 10
        anchors.top: grd.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: rowButtons.top
        frameVisible: true

        ListView {
            id: childData
            flickableDirection: Flickable.VerticalFlick
            clip: true
            header: opcItemHeaderComponent
            model: opcItemModel
            delegate: opcItemComponent
            anchors.fill: parent
            anchors.leftMargin: 5
            anchors.topMargin: 3
            cacheBuffer: 5000
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
            text: "Load tags.db"
            height: parent.height

            onClicked: {
                readTagsDb();
            }
        }
        Button {
            text: "Save tags.db"
            height: parent.height
            onClicked: {
                saveTagsDb();
                readTagsDb();

                console.time("tagsSaved");
                tagsSaved();
                console.timeEnd("tagsSaved");
            }
            enabled: opcItemModel.count > 0
        }

    }

    Component {
        id: opcItemHeaderComponent
        Item {
            height: childrenRect.height + 4
            width: parent.width
            Row {
                spacing:4
                width: parent.width
                Label {
                    text: "Tag Name"
                    width: parent.width / 11
                }
                Label {
                    text: "OPC Name"
                    width: childData.width / 3
                }
                Label {
                    text: "OPC Type"
                    width: parent.width / 12
                }
                Label {
                    text: "Log Type"
                    width: parent.width / 12
                }
                Label {
                    text: "Log Expression"
                    width: parent.width / 3
                }
                Label {
                    text: "Delete"
                    width: parent.width / 13
                }
            }
        }
    }

    Component {
        id: opcItemComponent

        Row {
            property int indexOfThisDelegate: index
            anchors.left: parent.left
            anchors.right: parent.right
            spacing: 4
            height: childrenRect.height + 4
            width: parent.width

            TextField {
                id: inpOpcName
                width: parent.width / 11
                text: opcname
                onTextChanged: {
                    opcItemModel.setProperty(parent.indexOfThisDelegate, "opcname", text);
                }
            }

            TextField {
                id: inpOpcTag
                width: parent.width / 3
                text: opctagid != -1 ? tagName(opctagid) : opctagstring

                onTextChanged: {
                    opcItemModel.setProperty(indexOfThisDelegate, "opctagstring", text);
                }

                Button {
                    height: parent.height
                    width: height
                    anchors.right: parent.right
                    onClicked: {
                        dlgOpcTag.tagIndex = indexOfThisDelegate
                        dlgOpcTag.opcIndex = opctagid
                        dlgOpcTag.open();
                    }
                }
            }

            ComboBox {
                id: inpOpcType
                width: parent.width / 12
                model: opcTypes
                currentIndex: opctypeid
                editable: false
                onCurrentIndexChanged: {
                    opcItemModel.setProperty(parent.indexOfThisDelegate, "opctypeid", currentIndex);
                }
                MouseArea {
                    anchors.fill: parent
                    onWheel: {}
                    onPressed: {mouse.accepted = false;}
                    onReleased: {mouse.accepted = false;}
                }
            }

            ComboBox {
                id: inpOpcLogType
                width: parent.width / 12
                model: opcLogTypes
                currentIndex: opclogtypeid
                editable: false

                onCurrentIndexChanged: {
                    opcItemModel.setProperty(parent.indexOfThisDelegate, "opclogtypeid", currentIndex);
                }
                MouseArea {
                    anchors.fill: parent
                    onWheel: {}
                    onPressed: {mouse.accepted = false;}
                    onReleased: {mouse.accepted = false;}
                }
            }

            TextField {
                id: inpOpcLogExpression
                width: parent.width / 3
                text: opclogexpression
                enabled: opclogtypeid === 3 //3 = Expression, faster than lookup
                onTextChanged: {
                    opcItemModel.setProperty(parent.indexOfThisDelegate, "opclogexpression", text);
                }
            }

            CheckBox {
                id: chkDelete
                checked: opcdeletetag
                text: ""
                width: parent.width / 13

                onCheckedChanged: {
                    opcItemModel.setProperty(parent.indexOfThisDelegate, "opcdeletetag", checked);
                }
            }

        }
    }

    Dialog {
        id: dlgOpcTag
        visible: false
        title: "Select OPC Tag"
        property int tagIndex: -1
        property int opcIndex: -1
        width: 520
        height: 500

        standardButtons: StandardButton.Ok | StandardButton.Cancel

        onOpcIndexChanged: {
            console.log("Setting index to", opcIndex);
            tvOpcTags.selection.clear();
            tvOpcTags.selection.select(opcIndex);
            tvOpcTags.positionViewAtRow(opcIndex);
        }

        TableView {
            id: tvOpcTags
            width: parent.width
            height: 450
            model: TagModel

            TableViewColumn {
                role: "text"
                title: "OPC Tag"
                width: 500
            }
        }

        onAccepted: {
            var t = 0;
            tvOpcTags.selection.forEach( function(rowIndex) {t = rowIndex} )
            opcItemModel.setProperty(tagIndex, "opctagid", t);
        }
    }

    ListModel {
        id: opcLogTypes
        ListElement {
            text: "Always"
        }
        ListElement {
            text: "Never"
        }
        ListElement {
            text: "OnChange"
        }
        ListElement {
            text: "Expression"
        }
    }

    ListModel {
        id: opcTypes
        ListElement {
            text: "Boolean"
        }
        ListElement {
            text: "UInt1"
        }
        ListElement {
            text: "UInt2"
        }
        ListElement {
            text: "UInt4"
        }
        ListElement {
            text: "Int1"
        }
        ListElement {
            text: "Int2"
        }
        ListElement {
            text: "Int4"
        }
        ListElement {
            text: "Real4"
        }
        ListElement {
            text: "Real8"
        }
        ListElement {
            text: "Date"
        }
        ListElement {
            text: "Money"
        }
        ListElement {
            text: "String"
        }
    }

    function readTagsDb() {
        var tags;
        console.time("readTagsDb");

        opcItemModel.clear();

        tags = tagsDb.read();
        var lines = tags.split("\n");
        var lineCount = lines.length;
        var line;

        //Loop lines
        for (var i = 0; i < lineCount; ++i) {
            line = lines[i].split(";");

            if (line[0] === "opchost") {
                opcHost = line[1].trim();
            } else if (line[0] === "opcserver") {
                opcServer = line[1].trim();
                //console.log(line[1].trim());
                inpOPCServer.currentIndex = opcServerId(line[1].trim());
            } else if (line[0] === "opcitem") {
                var opcItemData = line[1].split("|||");
                if (opcItemData.length === 5) {
                    opcItemModel.append({"opcname": opcItemData[0],"opctagid": tagId(opcItemData[1].trim()),"opctagstring": opcItemData[1].trim(), "opctypeid": typeId(opcItemData[2].trim()),"opclogtypeid": logTypeId(opcItemData[3].trim()), "opclogexpression": opcItemData[4].trim(), "opcdeletetag": false})
                }
            }
        }
        console.timeEnd("readTagsDb");
    }

    function typeId(typeString) {
        for (var i = 0 ; i < opcTypes.count; ++i) {
            var elem = opcTypes.get(i);
            var name = elem.text;
            if (typeString.toLowerCase() === name.toLowerCase()) {
                return i;
            }
        }
        return -1;
    }

    function logTypeId(logTypeString) {
        for (var i = 0 ; i < opcLogTypes.count; ++i) {
            var elem = opcLogTypes.get(i);
            var name = elem.text;
            if (logTypeString.toLowerCase() === name.toLowerCase()) {
                return i;
            }
        }
        return 0; //Always
    }

    function logType(logtypeid) {
        var logTypeCount = opcLogTypes.count;
        if (logtypeid < logTypeCount && logtypeid >= 0) {
            return opcLogTypes.get(logtypeid).text;
        }
        return "Always";
    }

    function opcServerId(server) {
        var serverCount = DAServerModel.rowCount(0);
        //console.log("Looking for", server, "in", serverCount);
        for (var i = 0 ; i < serverCount; ++i) {
            var name = DAServerModel.data(DAServerModel.index(i,0,0), OPCDAServerModel.ServerName);
            if (server.toLowerCase() === name.toLowerCase()) {
                return i;
            }
        }
        return -1;
    }

    function tagId(tag) {
        /*
        var tagCount = TagModel.rowCount(0);
        for (var i = 0 ; i < tagCount; ++i) {
            var name = TagModel.data(TagModel.index(i,0,0), OPCTagModel.TagName);
            if (tag.toLowerCase() === name.toLowerCase()) {
                return i;
            }
        }
        return -1;
        */
        //console.log("Looking for ", tag, TagModel.tagId(tag));
        return TagModel.tagId(tag);
    }

    function tagName(tagid) {
        /*
        var tagCount = TagModel.rowCount(0);
        if (tagid < tagCount) {
            return TagModel.data(TagModel.index(tagid, 0, 0), OPCTagModel.TagName);
        }
        return "";
        */
        //console.log("Looking for ", tagid, TagModel.tag(tagid));

        return TagModel.tag(tagid);
    }

    function typeName(typeid) {
        var typeCount = opcTypes.count;
        if (typeid < typeCount && typeid >= 0) {
            return opcTypes.get(typeid).text;
        }
        return "";
    }

    function saveTagsDb() {
        console.time("saveTagsDb");
        var tagsdbtxt = ""
        tagsdbtxt += "opchost;" + opcHost + "\n";
        tagsdbtxt += "opcserver;" + opcServer + "\n";

        for (var i = 0; i < opcItemModel.count; ++i) {
            var elem = opcItemModel.get(i);
            if (!elem.opcdeletetag) {
                console.log("saving:", elem.opcname, elem.opctagid, elem.opctagstring);
                tagsdbtxt += "opcitem;" + elem.opcname + "|||" + (elem.opctagid >= 0 ? tagName(elem.opctagid): elem.opctagstring) + "|||" + typeName(elem.opctypeid) + "|||" + logType(elem.opclogtypeid) + "|||"  + elem.opclogexpression + "\n";
            }
        }
        //console.log(tagsdbtxt);
        tagsDb.write(tagsdbtxt);
        console.timeEnd("saveTagsDb");
    }
}

