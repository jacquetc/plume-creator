import QtQuick 2.15
import QtQml 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import eu.skribisto.taghub 1.0
import eu.skribisto.skr 1.0
import "../Commons"
import "../Items"

Item {
    property alias searchListView: searchListView
    property alias searchTextField: searchTextField
    property alias searchTagPad: searchTagPad
    property alias searchDrawer: searchDrawer
    property alias showTagDrawerButton: showTagDrawerButton
    property alias deselectTagsButton: deselectTagsButton
    readonly property bool searching: searchTextField.text.length !== 0

    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        Layout.fillWidth: true
        RowLayout {
            id: rowLayout

            SkrTextField {
                id: searchTextField
                Layout.fillWidth: true
                placeholderText: qsTr("Search")

                KeyNavigation.tab: showTagDrawerButton

            }

            SkrToolButton {
                id: showTagDrawerButton
                text: qsTr("Show tags list")
                icon.source: "qrc:///icons/backup/tag.svg"
                display: AbstractButton.IconOnly

                KeyNavigation.tab:  deselectTagsButton

            }

            SkrToolButton {
                id: deselectTagsButton
                text: qsTr("Deselect tags")
                icon.source: "qrc:///icons/backup/edit-select-none.svg"
                display: AbstractButton.IconOnly
                visible: false

                KeyNavigation.tab: searchListView

            }

        }

        Item {
            id: viewItem
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true

            ScrollView {
                id: scrollView
                anchors.fill: parent
                focusPolicy: Qt.StrongFocus
                clip: true
                ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
                ScrollBar.vertical.policy: ScrollBar.AsNeeded


                CheckableTree {
                    id: searchListView
                    anchors.fill: parent
                    smooth: true
                    boundsBehavior: Flickable.StopAtBounds
                    flickableDirection: Flickable.VerticalFlick
                    spacing: 5

                    Accessible.name: searching ? qsTr("Note search result list") : qsTr("Note overview list")
                    Accessible.role: Accessible.List

//                    ScrollBar.vertical: ScrollBar {
//                        id: internalScrollBar
//                        parent: searchListView
//                        policy: ScrollBar.AsNeeded
//                    }

                    treeIndentMultiplier: 20
                    elevationEnabled: true                    

                    openActionsEnabled: true
                    renameActionEnabled: true
                    sendToTrashActionEnabled: true
                    cutActionEnabled: true
                    copyActionEnabled: true
                    pasteActionEnabled: !searching
                    addSiblingPaperActionEnabled: !searching
                    addChildPaperActionEnabled: !searching
                    moveActionEnabled: !searching
                }

            }

            SKRDrawer {
                id: searchDrawer
                parent: viewItem
                widthInDrawerMode: viewItem.width /2
                height: viewItem.height
                interactive: true
                dockModeEnabled: false
                edge: Qt.RightEdge
                settingsCategory: "noteOverviewNoteSearchItemDrawer"
                z: 1

                SkrPane {
                    elevation: 3

                TagPad{
                    id: searchTagPad
                    anchors.fill: parent
                    minimalMode: true
                    itemType: SKR.Note
                    selectionEnabled: true
                    multipleSelectionsEnabled: true
                }
                }
            }


        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}
}
##^##*/
