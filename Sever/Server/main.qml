import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.5

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Connections{
        target: Sever
        onNotifyQml : {
            console.log(parameter)
            progressBarId.indeterminate = false
            progressBarId.value = 1;
        }
    }

    ProgressBar {
        id : progressBarId
        indeterminate: false
        anchors.horizontalCenter: parent.horizontalCenter
    }

    //test get API
    Rectangle {
        id: rectAPI
        width: 200
        height: 100
        color: "green"
        Text {
            id: rectTextId
            text: qsTr("Fetch data")
            anchors.centerIn: parent

        }
        anchors.centerIn: parent

        MouseArea {
            anchors.fill: parent
            onClicked: {
                //fetch
                Sever.fetchData("http://localhost:8080/")
                progressBarId.indeterminate = true;
            }
        }
    }

    //test create file database
    Rectangle {
        id: rectData
        width: 200
        height: 100
        anchors.top: rectAPI.bottom
        anchors.topMargin: 50
        anchors.horizontalCenter: rectAPI.horizontalCenter
        color: "blue"

        Text {
            id: rect1TextId
            text: qsTr("Create data file")
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }
}
