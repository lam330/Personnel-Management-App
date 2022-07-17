import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Button {
        id : getDataBtn
        text: "Get data from Sever"
        width: 500
        height: 40
        z: 30

        anchors.horizontalCenter: grid.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        //anchors.top: mListViewId.bottom
        onClicked: {
            console.log("Clicked on getdataBtn")
//            myModel.deleteData()
            myModel.getDataFromSource()

        }
    }



    GridView {
        id: grid
        anchors.fill: parent
        cellWidth: 150; cellHeight: 120

        model: myModel
        delegate: delegateId
        highlight: highlightId
//        focus: true
        Component {
            id: highlightId
            Rectangle{
                id: highlightRect
                width: parent.width
                color: "lightsteelblue"
                radius: 14
                border.color: "black"
                z : 3
                opacity: 0.2
            }
        }

        Component {
            id: delegateId
            Item {
                width: grid.cellWidth - 10; height: grid.cellHeight - 10
                Column {
                    anchors.fill: parent
                    Image { source: getAvatar(index); anchors.horizontalCenter: parent.horizontalCenter;
                        sourceSize.width: 100; sourceSize.height: 100  }
                    Text { text: name; anchors.horizontalCenter: parent.horizontalCenter }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Clicked on :" + model.name)
                        grid.currentIndex = index;

                    }
                }
            }
        }
    }



    function getAvatar(index) {
        console.log("getAvatar => " + index)
        var avaArray = [
                    "ava_Lam.png",
                    "ava_Dung.png",
                    "ava_Hieu.png"
                ];
        return ("images/" + avaArray[index]);
    }
}






