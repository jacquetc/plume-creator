import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../Commons"
import "../Items"
import ".."

Item {
    id: base
    property alias modifiableToolButton: modifiableToolButton
    property alias favoriteToolButton: favoriteToolButton
    property alias printableToolButton: printableToolButton


    implicitHeight: mainPageLayout.childrenRect.height

    SkrPane {
        id: mainPage
        anchors.fill: parent
        padding: 0

        ColumnLayout {
            id: mainPageLayout
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right


            SkrGroupBox {
                id: groupBox
                padding: 5
                Layout.fillWidth: true
                title: qsTr("Properties")

                GridLayout {
                    id: gridLayout
                    columns: gridLayout.width / printableToolButton.width - 1
                    anchors.left: parent.left
                    anchors.right: parent.right
                    columnSpacing: 3
                    rowSpacing: 3


                    SkrToolButton {
                        id: printableToolButton
                        text: qsTr("Printable")
                        checkable: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        display: AbstractButton.IconOnly
                    }

                    SkrToolButton {
                        id: modifiableToolButton
                        text: qsTr("Modifiable")
                        checkable: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        display: AbstractButton.IconOnly
                    }

                    SkrToolButton {
                        id: favoriteToolButton
                        visible: false //TODO: unhide and implement
                        text: qsTr("Favorite")
                        checkable: true
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        display: AbstractButton.IconOnly
                    }


                }
            }
        }
    }
}
