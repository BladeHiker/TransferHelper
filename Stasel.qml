import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml 2.12
import QtQml.Models 2.1
import QtQuick.XmlListModel 2.0
import QtQuick.Shapes 1.12

Rectangle {
    id: stasel
    clip: true
    ListView {
        id: listView_from
        width: parent.width
        height: parent.height
        clip: true
        antialiasing: true
        highlightRangeMode: ListView.ApplyRange
        model: sellist
        delegate: ItemDelegate {
            id: itemDelegate
            width: parent.width
            height: isVis(model.name, place_from.text) ? 40 : 0
            display: AbstractButton.TextOnly
            visible: isVis(model.name, place_from.text)
            contentItem: Rectangle {
                border {
                    color: "#ffffff"
                    width: 2
                }
                color: "#00ffffff"
                anchors.fill: parent
                antialiasing: true
                Row {
                    y: 5
                    
                    Text {
                        text: name
                        font.kerning: true
                        font.preferShaping: true
                        font.weight: Font.Bold
                        font.pointSize: 20
                    }
                    
                    Text {
                        text: line
                        font.family: "思源黑體 Heavy"
                        font.bold: true
                        verticalAlignment: Text.AlignVCenter
                        font.kerning: true
                        font.preferShaping: true
                        font.weight: Font.Bold
                        font.pointSize: 15
                        Rectangle {
                            width: parent.width
                            height: 30
                            color: lcolor
                            border.color: lcolor
                            border.width: 5
                            radius: 5
                            Text {
                                text: line
                                font.family: "思源黑體 Heavy"
                                font.bold: true
                                verticalAlignment: Text.AlignVCenter
                                font.kerning: true
                                font.preferShaping: true
                                font.weight: Font.Bold
                                font.pointSize: 15
                                color: "#ffffff"
                            }
                        }
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        place_from.text = model.name
                    }
                }
            }
        }
    }
}
