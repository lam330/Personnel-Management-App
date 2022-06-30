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
//        delegate : ItemDelegate {
//            id: itemDelegateId
//            text: "" + model.name + " " + model.age
//            font.pointSize: 10
//            width: parent.width
//        }
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



//        ListModel {
//            id : mModelId
//            ListElement {
//                name: "Lam Le"
//            }
//            ListElement {
//                name: "Dung ND"
//            }
//            ListElement {
//                name: "Hieu DT"
//            }
//        }


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
                        mListViewId.currentIndex = index;
                        contentDialog.openDialog()

                        //How get right index??
                        contentDialog.name = model.name
                        contentDialog.age = model.age
                        contentDialog.pos = model.position
                        contentDialog.exp = model.experience
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
            console.log("Clicked on button1")
            myModel.getDataFromSource()

        }
    }

    ProfileDialog {
        id: contentDialog
    }

    //Dialog
//    Dialog {
//        id: contentDialog

//        x: (parent.width - width) / 2
//        y: (parent.height - height) / 2
//        width: Math.min(parent.width, parent.height) / 3 * 2
//        //contentHeight: logo.height * 2
//        contentHeight: parent.height/2 // This doesn't cause the binding loop.
//        parent: Overlay.overlay

//        modal: true
//        title: "Profile"
//        standardButtons: Dialog.Close//

//        Flickable {
//            id: flickable
//            clip: true
//            anchors.fill: parent
//            contentHeight: column.height

//            Column {
//                id: column
//                spacing: 20
//                width: parent.width

//                Image {
//                    id: logo
//                    width: parent.width / 2
//                    anchors.horizontalCenter: parent.horizontalCenter
//                    fillMode: Image.PreserveAspectFit
//                    source: "images/depvkl.jpg"
//                }

//                Label {
//                    width: parent.width
//                    text: "Experiences"
//                    wrapMode: Label.Wrap
//                }
//            }

//            ScrollIndicator.vertical: ScrollIndicator {
//                parent: contentDialog.contentItem
//                anchors.top: flickable.top
//                anchors.bottom: flickable.bottom
//                anchors.right: parent.right
//                anchors.rightMargin: -contentDialog.rightPadding + 1
//            }
//        }
//    }

}




