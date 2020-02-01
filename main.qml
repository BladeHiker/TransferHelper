import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtQml.Models 2.1
import QtQuick.XmlListModel 2.0
import QtQuick.Shapes 1.12
import DStation 1.0
import DLine 1.0
import DStaList 1.0
import DTransferPlan 1.0
import DTransferPlanList 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 480
    height: 680
    color: "#dff0f9"
    title: qsTr("TransferHelper")
    FontLoader {
        id: font0
        source: "qrc:/SourceHanSansHWSC-Bold.otf"
    }
    FontLoader {
        id: font1
        source: "qrc:/arial.ttf"
    }
    function isVis(a, b) {

        return a.indexOf(b) !== -1
    }
    DStaList {
        id: dStaList

        Component.onCompleted: {
            dStaList.dbin(":/stadb.xml")
        }
    }
    DTransferPlanList {
        id: dtransplans
    }

    Column {
        id: main
        antialiasing: true
        anchors.fill: parent
        spacing: 0
        Rectangle {
            id: rectangle
            width: parent.width
            height: 100
            color: "#6faef2"
            Rectangle {
                id: head
                width: parent.width
                color: "#00000000"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 0
                height: 100
                antialiasing: true
                Rectangle {
                    id: rectangle_swap
                    color: "#00ffffff"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 8
                    width: parent.width * 0.1
                    Button {
                        id: swap
                        anchors.centerIn: parent.Center
                        height: parent.height
                        width: parent.width
                        background: Rectangle {
                            color: "#00000000"
                        }
                        text: qsTr("⇵")
                        bottomPadding: 0
                        topPadding: 0
                        leftPadding: 0
                        rightPadding: 0
                        anchors.verticalCenterOffset: -2
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.right: parent.right
                        anchors.rightMargin: 0
                        display: AbstractButton.TextOnly
                        font.family: font0.name
                        anchors.verticalCenter: parent.verticalCenter
                        antialiasing: true
                        font.pointSize: swap.pressed ? 35 : 30
                        font.bold: false
                        onClicked: {

                            var t = place_from.text
                            place_from.text = place_to.text
                            place_to.text = qsTr(t)
                        }
                    }
                }
                Rectangle {
                    id: inp
                    width: parent.width * 0.8
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: -3
                    anchors.top: parent.top
                    anchors.topMargin: 8
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#00000000"
                    scale: 0.9
                    Rectangle {
                        color: "#a0ffffff"
                        radius: 25
                        anchors.top: parent.top
                        anchors.topMargin: 0
                        anchors.horizontalCenter: parent.horizontalCenter
                        clip: true
                        border.color: {
                            if (place_from.activeFocus)
                                return "#ffffff"
                            return "#a0ffffff"
                        }
                        antialiasing: true
                        opacity: 1
                        border.width: 3
                        width: parent.width
                        height: parent.height / 2.2
                        TextField {
                            id: place_from
                            width: parent.width
                            font.bold: true
                            clip: true
                            font.family: font0.name
                            leftPadding: 25
                            bottomPadding: 0
                            topPadding: 0
                            font.preferShaping: true
                            font.kerning: true
                            antialiasing: true
                            placeholderText: "起点"
                            placeholderTextColor: "#a0ffffff"
                            font.weight: Font.Medium
                            font.pixelSize: 28
                            selectByMouse: true
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                    Rectangle {
                        color: "#a0ffffff"
                        radius: 25
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: 4
                        anchors.horizontalCenter: parent.horizontalCenter
                        clip: true
                        border.color: {
                            if (place_to.activeFocus)
                                return "#ffffff"
                            return "#a0ffffff"
                        }
                        border.width: 3
                        width: parent.width
                        height: parent.height / 2.2
                        TextField {
                            id: place_to
                            font.bold: true
                            width: parent.width
                            clip: true
                            font.family: font0.name
                            leftPadding: 25
                            bottomPadding: 0
                            topPadding: 0
                            font.preferShaping: true
                            font.kerning: true
                            antialiasing: true
                            placeholderText: "终点"
                            placeholderTextColor: "#a0ffffff"
                            font.weight: Font.Medium
                            font.pixelSize: 28
                            selectByMouse: true
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }
                Rectangle {
                    id: rectangle_find
                    width: parent.width * 0.1
                    color: "#00ffffff"
                    anchors.top: parent.top
                    anchors.topMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: parent.right
                    anchors.rightMargin: 8
                    Button {
                        id: find
                        anchors.centerIn: parent.Center
                        height: parent.height
                        text: qsTr(">")
                        font.family: font1.name
                        width: parent.width
                        background: Rectangle {
                            color: "#00000000"
                        }
                        leftPadding: 0
                        rightPadding: 0
                        topPadding: 0
                        bottomPadding: 0
                        anchors.verticalCenterOffset: 5
                        anchors.horizontalCenter: parent.horizontalCenter
                        clip: true
                        font.weight: Font.Thin
                        anchors.verticalCenter: parent.verticalCenter
                        display: AbstractButton.TextOnly
                        antialiasing: true
                        font.pointSize: find.pressed ? 100 : 80
                        onClicked: {
                            posfrom.setName(place_from.text)
                            posto.setName(place_to.text)
                            stachk.name = dtransplans.query(posfrom.name,
                                                            posto.name)
                        }
                    }
                }
            }
        }
        Rectangle {
            width: parent.width
            height: 4
            color: "#69f0f0"
            antialiasing: true
        }

        ScrollView {
            id: scrollView
            width: parent.width
            height: parent.height - 100
            clip: true
            spacing: 3
            Loader {
                id: scrollLoad
                width: parent.width
                height: parent.height
                sourceComponent: {
                    if (place_from.activeFocus || place_to.activeFocus) {
                        return sellistView
                    } else if (stachk.name) {
                        console.log(dtransplans.planlst.length)
                        if (dtransplans.planlst.length === 0) {
                            return error
                        } else {
                            return roadsView
                        }
                    } else {
                        return welcome
                    }
                }
            }
            Component {
                id: sellistView
                Rectangle {
                    width: parent.width
                    height: parent.height
                    clip: true
                    color: "#00ffffff"

                    ListView {
                        id: listView_from
                        width: parent.width
                        height: parent.height
                        clip: true
                        antialiasing: true
                        highlightRangeMode: ListView.ApplyRange
                        model: dStaList.stalst
                        delegate: ItemDelegate {
                            clip: true
                            width: parent.width
                            Behavior on height {
                                PropertyAnimation {
                                    duration: 1000
                                    easing.type: Easing.OutQuart
                                }
                            }
                            height: (place_from.activeFocus && isVis(
                                         model.name, place_from.text))
                                    || (place_to.activeFocus && isVis(
                                            model.name, place_to.text)) ? 40 : 0
                            opacity: (place_from.activeFocus && isVis(
                                          model.name, place_from.text))
                                     || (place_to.activeFocus && isVis(
                                             model.name, place_to.text)) ? 1 : 0
                            Behavior on opacity {
                                OpacityAnimator {
                                    duration: 100
                                }
                            }

                            display: AbstractButton.TextOnly
                            contentItem: Rectangle {
                                color: "#00ffffff"
                                anchors.fill: parent
                                antialiasing: true

                                Row {
                                    y: 2
                                    spacing: 10
                                    Text {
                                        text: model.name
                                        font.kerning: true
                                        font.preferShaping: true
                                        font.pointSize: 20
                                        font.family: font0.name
                                    }
                                    Repeater {
                                        id: repeater
                                        model: linelst.length
                                        TextArea {
                                            text: " " + linelst[index].name + " "
                                            anchors.verticalCenter: parent.verticalCenter
                                            verticalAlignment: Text.AlignVCenter
                                            horizontalAlignment: Text.AlignHCenter
                                            enabled: false
                                            padding: 0
                                            rightPadding: 0
                                            leftPadding: 0
                                            bottomPadding: 0
                                            topPadding: 0
                                            font.family: font0.name
                                            font.bold: true
                                            font.kerning: true
                                            font.preferShaping: true
                                            font.weight: Font.Bold
                                            font.pointSize: 14
                                            color: linelst[index].isbus ? linelst[index].color : "#ffffff"
                                            background: Rectangle {
                                                anchors.centerIn: parent.Center
                                                width: parent.width
                                                height: 30
                                                color: linelst[index].isbus ? "#00000000" : linelst[index].color
                                                border.color: linelst[index].color
                                                border.width: linelst[index].isbus ? 3 : 0
                                                radius: 20
                                            }
                                        }
                                    }
                                }
                            }
                            MouseArea {
                                hoverEnabled: true
                                anchors.fill: parent
                                onClicked: {
                                    if (place_from.activeFocus)
                                        place_from.text = model.name
                                    if (place_to.activeFocus)
                                        place_to.text = model.name
                                }
                            }
                        }
                    }
                }
            }

            Component {
                id: roadsView
                Rectangle {
                    width: parent.width
                    height: parent.height
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    color: "#00000000"
                    ScrollView {
                        anchors.fill: parent
                        width: parent.width
                        height: parent.height
                        contentItem: Rectangle {
                            anchors.fill: parent
                            width: parent.width
                            height: parent.height
                            color: "#00000000"
                            ListView {
                                id: roadsShow
                                contentWidth: parent.width
                                anchors.fill: parent
                                model: dtransplans.planlst
                                spacing: 10

                                populate: Transition {
                                    NumberAnimation {
                                        property: "opacity"
                                        from: 0
                                        to: 1.0
                                        duration: 500
                                        easing.type: Easing.InCubic
                                    }
                                    NumberAnimation {
                                        property: "scale"
                                        from: 1.1
                                        to: 1
                                        duration: 500
                                        easing.type: Easing.InCubic
                                    }
                                }
                                delegate: ItemDelegate {
                                    id: itemDelegate
                                    width: parent.parent.width
                                    height: 80
                                    Behavior on height {
                                        PropertyAnimation {
                                            duration: 1000
                                            easing.type: Easing.OutQuart
                                        }
                                    }
                                    padding: 0
                                    leftPadding: 0
                                    rightPadding: 0
                                    bottomPadding: 0
                                    topPadding: 0
                                    display: AbstractButton.TextOnly
                                    MouseArea {
                                        height: 80
                                        anchors.top: parent.top
                                        anchors.topMargin: 0
                                        width: parent.width

                                        onClicked: {
                                            console.log("click" + index)
                                            if (parent.height == 80)
                                                parent.height
                                                        = parent.parent.parent.parent.parent.height
                                            else
                                                parent.height = 80
                                        }
                                    }
                                    contentItem: Rectangle {

                                        width: parent.parent.parent.parent.parent.width
                                        height: parent.height
                                        color: "#20001010"

                                        Column {
                                            //x: 20
                                            spacing: 5
                                            width: parent.width
                                            height: parent.height
                                            Text {
                                                text: "换乘方案 " + (index + 1) + note
                                                font.family: font0.name
                                                font.bold: true
                                                font.pointSize: 12
                                            }

                                            Row {
                                                width: parent.width
                                                height: 50
                                                spacing: 10
                                                Repeater {
                                                    model: linelst
                                                    delegate: Rectangle {
                                                        height: 30
                                                        width: 100
                                                        radius: 20
                                                        color: {
                                                            if (model.isbus)
                                                                return "#00000000"
                                                            return model.color
                                                        }
                                                        border.color: model.color
                                                        border.width: {
                                                            color: model.color
                                                            if (model.isbus) {
                                                                return 3
                                                            } else {
                                                                return 0
                                                            }
                                                        }

                                                        Text {
                                                            color: model.isbus ? model.color : "#ffffff"
                                                            text: model.name
                                                            font.family: font0.name
                                                            font.bold: true
                                                            horizontalAlignment: Text.AlignHCenter
                                                            verticalAlignment: Text.AlignVCenter
                                                            anchors.fill: parent
                                                            anchors.centerIn: parent.Center
                                                            font.pixelSize: 18
                                                        }
                                                    }
                                                }
                                            }
                                            Rectangle {
                                                clip: true
                                                width: parent.parent.width
                                                height: parent.parent.height - 100
                                                color: "#1cffffff"
                                                opacity: parent.height >= 90 ? 1 : 0
                                                visible: parent.height >= 85 ? true : false
                                                Behavior on opacity {
                                                    PropertyAnimation {
                                                        duration: 500
                                                        easing.type: Easing.InCubic
                                                    }
                                                }
                                                Column {
                                                    anchors.fill: parent
                                                    visible: parent.height >= 85 ? true : false
                                                    opacity: parent.height >= 90 ? 1 : 0

                                                    Behavior on opacity {
                                                        PropertyAnimation {
                                                            duration: 500
                                                            easing.type: Easing.InCubic
                                                        }
                                                    }
                                                    ListView {
                                                        width: parent.width
                                                        height: parent.height
                                                        model: infolst
                                                        spacing: 5
                                                        delegate: ItemDelegate {
                                                            width: parent.width
                                                            height: 50
                                                            contentItem: Rectangle {
                                                                color: "#a0ffffff"
                                                                anchors.fill: parent
                                                                clip: true
                                                                border.color: "#6fc0ff"
                                                                border.width: 1
                                                                Row {
                                                                    id: row
                                                                    spacing: 5
                                                                    anchors.fill: parent
                                                                    Rectangle {
                                                                        height: parent.height * 0.9
                                                                        //width: model.sym === 1 ? 20 : 0
                                                                        width: 15
                                                                        visible: model.sym === 1
                                                                                 || model.sym === 3
                                                                        color: model.color
                                                                    }

                                                                    Text {
                                                                        text: {
                                                                            if (model.sym === 1 || model.sym === 3)
                                                                                return model.line
                                                                            return ""
                                                                        }
                                                                        font.bold: true
                                                                        font.pointSize: 18
                                                                        verticalAlignment: Text.AlignVCenter
                                                                        color: model.color
                                                                    }
                                                                    Text {
                                                                        color: model.color
                                                                        text: {
                                                                            if (model.sym === 2)
                                                                                return qsTr("↓")
                                                                            if (model.sym === 3)
                                                                                return qsTr("⇵")
                                                                            if (model.sym === 4)
                                                                                return qsTr("→")
                                                                            return " "
                                                                        }
                                                                        font.family: font0.name
                                                                        font.bold: true
                                                                        verticalAlignment: Text.AlignVCenter
                                                                        font.pointSize: 25
                                                                    }

                                                                    Text {
                                                                        color: "#000000"
                                                                        text: model.text
                                                                        font.family: font0.name
                                                                        verticalAlignment: Text.AlignVCenter
                                                                        font.pointSize: 20
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Component {
                id: welcome
                Rectangle {
                    id: rectangle1
                    anchors.fill: parent
                    color: "#00000000"

                    BorderImage {
                        verticalTileMode: BorderImage.Stretch
                        horizontalTileMode: BorderImage.Stretch
                        antialiasing: true
                        anchors.fill: parent
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/logo_qt.png"
                        anchors.centerIn: parent.Center
                    }
                }
            }
            Component {
                id: error
                Rectangle {
                    id: rectangle1
                    anchors.fill: parent
                    color: "#fff5aeae"
                    Text {
                        id: errorwords
                        text: "没有找到换乘方案\n请检查车站名"
                        fontSizeMode: Text.HorizontalFit
                        anchors.top: parent.top
                        anchors.topMargin: 50
                        anchors.horizontalCenter: parent.horizontalCenter
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        font.family: font0.name
                        font.pointSize: 30
                    }
                    BorderImage {
                        verticalTileMode: BorderImage.Stretch
                        horizontalTileMode: BorderImage.Stretch
                        antialiasing: true
                        anchors.fill: parent
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        source: "qrc:/logo_qt.png"
                        anchors.centerIn: parent.Center
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_width:200;anchors_x:0;anchors_y:6}D{i:9;anchors_width:48}
D{i:8;anchors_height:100}D{i:11;anchors_height:100;anchors_y:3}D{i:16;anchors_height:100;anchors_width:48}
D{i:6;anchors_height:100;anchors_width:480}
}
##^##*/

