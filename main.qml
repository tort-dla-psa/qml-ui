import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import Property 1.0
import "./CustomColors"

Window {
    id:win
    visible: true
    width: 640
    height: 480
    color: Colors.black0
    title: qsTr("Hello World")

    GridLayout {
        id: grid
        rows: 1
        columns: 1
        anchors.fill: parent

        ListView {
            id: listView
            width: 100
            Layout.fillWidth: false
            Layout.column: 0
            Layout.minimumWidth: 100
            visible: true
            Layout.fillHeight: true
            clip:true

            model: PropertyModel{
                props: PropertiesList
            }

            delegate: RowLayout{
                width: parent.width    
                Text{
                    text: model.text
                    color: Colors.white0
                }
                TextField{
                    color: Colors.white0
                    background: Rectangle {
                        color: Colors.black0
                        border.width: 1
                        border.color: Colors.white0
                    }
                    text: model.value
                    onEditingFinished: model.value = text
                    Layout.fillWidth: true
                }
            }
        }

        Canvas{
            id: canvas
            objectName: "canvas"
            visible: true
            Layout.minimumWidth: 50
            Layout.column: 1
            property int x_beg: 0
            property int y_beg: 0
            property int x_end: 0
            property int y_end: 0
            property bool paint_line: false

            signal mousePress(int x, int y)
            signal mouseRelease(int x, int y)
            signal mouseMove(int x, int y)
            Layout.fillHeight: true
            Layout.fillWidth: true

            function setDrawLine(x,y, x_end, y_end){
                canvas.x_beg = x
                canvas.y_beg = y
                canvas.x_end = x_end
                canvas.y_end = y_end
                canvas.paint_line = true
                requestPaint()
            }

            MouseArea {
                id: mouseArea
                smooth: true
                antialiasing: true
                anchors.fill: parent
                onPressed: canvas.mousePress(mouseX, mouseY)
                onReleased: canvas.mouseRelease(mouseX, mouseY)
                onPositionChanged: canvas.mouseMove(mouseX, mouseY)
            }

            onPaint:{
                if(canvas.paint_line){
                    var ctx = getContext("2d")
                    ctx.reset()
                    ctx.lineWidth = 2;
                    ctx.strokeStyle = Colors.white0
                    ctx.beginPath()
                    ctx.moveTo(canvas.x_beg, canvas.y_beg)
                    ctx.lineTo(canvas.x_end, canvas.y_end)
                    ctx.stroke()
                    canvas.paint_line = false
                }
            }
        }
    }
}
