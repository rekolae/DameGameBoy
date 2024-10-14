import QtQuick
import QtQuick.Controls

QtObject {
    id: root

    property var mainWindow: ApplicationWindow {
        id: mainWindow

        width: 320
        height: 240
        visible: true
        title: qsTr("DameGameBoy " + Qt.application.version)

        Text {
            id: helloTextMain
            anchors.centerIn: parent
            text: "Hello Emulator World!"
            color: parent.palette.text
        }

        Item {
            //focus: true

            // Cmd+D when on macos
            Shortcut {
                sequence: "Ctrl+D"
                onActivated: debugWindow.visible = !debugWindow.visible;
            }
        }
    }

    property var debugWindow: ApplicationWindow {
        id: debugWindow

        width: 320
        height: 240
        visible: false
        title: qsTr("DameGameBoy Debug")
        x: 100
        y: 100

        Text {
            id: textDebug
            anchors.centerIn: parent
            text: "I'm a debug window!"
            color: parent.palette.text
        }

        Item {
            // Cmd+D when on macos
            Shortcut {
                sequence: "Ctrl+D"
                onActivated: debugWindow.visible = !debugWindow.visible;
            }
        }

        // Move debug window next to main window when visible
        onVisibleChanged: {
            if (visible) {
                if (mainWindow.x < width + 10) {
                    x = mainWindow.x + width + 10;
                    y = mainWindow.y;
                } else {
                    x = mainWindow.x - width - 10;;
                    y = mainWindow.y;
                }
            }
        }
    }
}
