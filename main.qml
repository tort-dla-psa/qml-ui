import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.5
import Property 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SplitView {
        id: splitView
        anchors.fill: parent

        ListView {
            id: listView
            width: 100
            Layout.minimumWidth: 100
            visible: true
            Layout.fillHeight: true
            clip:true

            model: PropertyModel{}

            delegate: RowLayout{
                width: parent.width    
                Text{
                    text: model.text
                }
                TextField{
                    text: model.value
                    onEditingFinished: model.value = text
                    Layout.fillWidth: true
                }
            }
        }

        MouseArea {
            id: mouseArea
            visible: true
            Layout.minimumWidth: 50
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

    }
}
