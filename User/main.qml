import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Manage information of members!")

    ListView {
        id : mListViewId
        anchors.fill: parent
        model : myModel
        delegate: delegateId

        header: headerId
        highlight: highlightId

        //Decoration: header, highlight
        Component {
            id : headerId
            Rectangle {
                id : headerRectId
                width: parent.width
                height: 50
                color: "light blue"
                border {color: "#9EDDF2"; width: 2}

                Text {
                    anchors.centerIn: parent
                    text : "Project's members"
                    font.pointSize: 20
                }
            }
        }

        Component {
            id: highlightId
            Rectangle{
                id: highlightRect
                width: parent.width
                color: "yellowgreen"
                radius: 14
                border.color: "black"
                z : 3
                opacity: 0.1
            }
        }

        Component {
            id : delegateId
            Rectangle {
                id : rectangleId
                width: parent.width
                height: 50
                color: "light gray"
                border.color: "black"
                radius: 10

                Text {
                    id : textId
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text : model.name + " " + model.age
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("Clicked on :" + model.name)
                        mListViewId.currentIndex = index;//no this lead to problem

                        console.log("Clicked on index:" + mListViewId.currentIndex)
                        contentDialog.openDialog()

                        //How get right index??
                        contentDialog.name = model.name
                        contentDialog.age = model.age
                        contentDialog.pos = model.position
                        contentDialog.exp = model.experience
                        contentDialog.imageSource = getAvatar(mListViewId.currentIndex);
                    }
                }
            }
        }
    }

    Button {
        id : getDataBtn
        text: "Get data from Sever"
        width: 500
        height: 40

        anchors.horizontalCenter: mListViewId.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        //anchors.top: mListViewId.bottom
        onClicked: {
            console.log("Clicked on getdataBtn")
            myModel.deleteData()
            myModel.getDataFromSource()
        }
    }

    Button {
        id : storeModelBtn
        text: "Store model"
        width: 500
        height: 40

        anchors.horizontalCenter: mListViewId.horizontalCenter
        anchors.bottom: getDataBtn.top
        anchors.bottomMargin: 30
        onClicked: {
            console.log("Clicked on storeBtn")
            myDatabase.generateTables()
            myModel.storeModel()
        }
    }

    Button {
        id : loadDataBtn
        text: "Load model from database"
        width: 500
        height: 40

        anchors.horizontalCenter: mListViewId.horizontalCenter
        anchors.bottom: storeModelBtn.top
        anchors.bottomMargin: 30
        onClicked: {
            console.log("Clicked on loadDataBtn")
            myModel.deleteData()
            myModel.loadDataFromDatabase()
        }
    }

    ProfileDialog {
        id: contentDialog
    }

    function getAvatar(index) {
        var avaArray = [
                    "ava_Lam.png",
                    "ava_Dung.png",
                    "ava_Hieu.png"
                ];
        return ("images/" + avaArray[index]);
    }


}




