import QtQuick
import QtCore 6.4
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    visible: true

    width: 640
    height: 480

    minimumWidth: 640
    minimumHeight: 480

    title: "DameGameBoy"

    Text {
        id: helloText
        anchors.centerIn: parent
        text: "Hello Emulator World!"
        color: parent.palette.text
    }

    Text {
        id: romLocation

        anchors.horizontalCenter: helloText.horizontalCenter

        anchors.top: helloText.bottom
        anchors.topMargin: 10

        text: ""
        color: parent.palette.text
    }

    MenuBar {
        Menu {
            title: "File"
            MenuItem {
                text: "&Open"
                onTriggered: fileDialog.open();
            }
            MenuItem {
                text: "Exit"
                onTriggered: Qt.quit();
            }
        }

        Menu {
            title: "Help"
            MenuItem {
                text: "About"
                onTriggered: popup.open();
            }
        }
    }

    FileDialog {
        id: fileDialog
        options: FileDialog.ReadOnly
        currentFolder: StandardPaths.standardLocations(StandardPaths.DocumentsLocation)[0]
        onAccepted: romLocation.text = selectedFile
    }

    Popup {
        id: popup

        width: 320
        height: 200

        anchors.centerIn: parent

        modal: true
        focus: true
        closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutside

        ColumnLayout {
            spacing: 5

            Text {
                text: "Version 0.0.0"
                color: parent.palette.text
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                Layout.maximumWidth: popup.width - 10
            }

            Text {
                text: "Cross-platform GameBoy/GameBoyColor emulator written using QML and C++"
                color: parent.palette.text
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                wrapMode: Text.WordWrap
                Layout.maximumWidth: popup.width - 10
            }

            Text {
                text: "Made because of curiosity and interest towards emulation as well as for practice"
                color: parent.palette.text
                Layout.leftMargin: 5
                Layout.rightMargin: 5
                wrapMode: Text.WordWrap
                Layout.maximumWidth: popup.width - 10
            }
        }

        Text {
            id: linkText
            text: "Source can be found at <a href='https://github.com/rekolae/DameGameBoy'>Github</a>"
            color: parent.palette.text
            linkColor: "cyan"
            bottomPadding: 10
            wrapMode: Text.WordWrap
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: popupCloseButton.top

            onLinkActivated: (link) => Qt.openUrlExternally(link)

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.NoButton
                cursorShape: parent.hoveredLink ? Qt.PointingHandCursor : Qt.ArrowCursor
            }
        }

        Button {
            id: popupCloseButton
            text: "Close"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            onClicked: popup.close()
        }
    }
}
