import QtQuick 2.14
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12

Item {

    id: rootId

    function openDialog(){
        contentDialog.open()
    }

    property alias imageSource: avatar.source
    property alias content: contentDialog.title
    property alias name: nameLabelId.text
    property alias age: ageLabelId.text
    property alias pos: posLabelId.text
    property alias exp: expLabelId.text



    width: contentDialog.implicitWidth + 20
    height: contentDialog.implicitHeight + 20

    Dialog {
        id: contentDialog

        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        width: Math.min(parent.width, parent.height) / 1.3
        height: Math.min(parent.width, parent.height)
        //contentHeight: logo.height * 2
        contentHeight: parent.height/2 // This doesn't cause the binding loop.
        parent: Overlay.overlay

        modal: true
        title: "Profile"

        Flickable {
            id: flickable
            clip: true
            anchors.fill: parent
            //contentHeight: column.height

            Image {
                id: avatar
                width: parent.width / 2
                anchors.left: parent.left
                anchors.leftMargin: 15
                fillMode: Image.PreserveAspectFit
                source: "images/depvkl.jpg"
            }

            StackView {
                id: stackViewId1
                property real offset: 10
                width: 100; height: 100
                anchors.left: avatar.right
                anchors.leftMargin: 20

                initialItem: labelColumn
            }

            StackView {
                id: stackViewId2
                property real offset: 10
                width: parent.width - 30; height: parent.height / 2
                anchors.top: avatar.bottom
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                initialItem: expLabelId
            }

            Column {
                id: labelColumn
                width: parent.width
                anchors.left: avatar.right
                anchors.leftMargin: 20
                spacing: 25
                Label {
                    id: nameLabelId
                    width: parent.width
                    text: "Name label"
                    wrapMode: Label.Wrap
                }

                Label {
                    id: ageLabelId
                    width: parent.width
                    text: "Age label"
                    wrapMode: Label.Wrap
                }

                Label {
                    id: posLabelId
                    width: parent.width
                    text: "Position label"
                    wrapMode: Label.Wrap
                }
            }

            Column {
                id: textEditColumn
                width: parent.width
                anchors.left: avatar.right
                anchors.leftMargin: 20
                spacing: 25
                visible: false
                TextEdit {
                    id: nameTextEdit
                    width: parent.width
                    text: "replaced name"
                }

                TextEdit {
                    id: ageTextEdit
                    width: parent.width
                    text: "replaced age"
                }

                TextEdit {
                    id: posTextEdit
                    width: parent.width
                    text: "replaced position"
                }
            }

            Label {
                id: expLabelId
                width: parent.width + 10
                height: parent.height / 1.5
                anchors.top: avatar.bottom
                anchors.topMargin: 10
                text: "Expereiences"
                wrapMode: Label.Wrap
                background: Rectangle {
                    border.color: "black"
                    border.width: 2
                }
            }

            TextArea {
                id: expTextAreaId
                placeholderText: "Replaced experiences"
                visible: false
                background: Rectangle {
                    border.color: "black"
                    border.width: 2
                }
            }

            RowLayout {
                id: btnListId
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                Layout.alignment: Qt.AlignRight
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 50
                Button{
                    text: "Edit"
                    onClicked: {
                        //change label to Edit: remove olds + create news

                        textEditColumn.visible = true
                        expTextAreaId.visible = true
                        stackViewId1.replace(textEditColumn)
                        stackViewId2.replace(expTextAreaId)
                    }
                }
                Button{
                    text: "Close"
                    onClicked: {
                        //customDialog.privateClicked();
                        close();
                    }
                }

                //            ScrollIndicator.vertical: ScrollIndicator {
                //                parent: contentDialog.contentItem
                //                anchors.top: flickable.top
                //                anchors.bottom: flickable.bottom
                //                anchors.right: parent.right
                //                anchors.rightMargin: -contentDialog.rightPadding + 1
                //            }
            }
        }
    }
}
