import QtQuick 2.12
import QtQuick.Controls 2.12
import Qt.labs.platform

import QtQuick.Window 2.12

// This must match the uri and version
// specified in the qml_module in the build.rs script.
import com.kdab.cxx_qt.demo 1.0

ApplicationWindow {
    id: root
    height: 480
    title: qsTr("Hello World")
    visible: true
    // Use these flags to make window not steal focus on startup, we'll change
    // it to a normal window afterwards. This way we can keep writing code :)
    // Might change in the future
    flags: Qt.Window | Qt.WindowTransparentForInput | Qt.WindowDoesNotAcceptFocus
    width: 640
    color: palette.window
    Component.onCompleted: {
        if (Qt.application.screens.length > 1) {
            let targetScreen = Qt.application.screens[1];

            root.screen = targetScreen;

            root.x = targetScreen.virtualX + (targetScreen.width - root.width) / 2;
            root.y = targetScreen.virtualY + (targetScreen.height - root.height) / 2;
        } else {
            console.warn("Only one monitor detected. Defaulting to primary.");
        }

        // Show manually
        root.flags = Qt.Window;
    }

    readonly property MyObject myObject: MyObject {
        number: 1
        string: qsTr("My String with my number: %1").arg(number)
    }

    MenuBar {
        Menu {
            title: 'File'
            MenuItem {
                text: 'New'
                shortcut: StandardKey.New
                onTriggered: console.log("New triggered")
            }
        }
    }

    Column {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 10

        Label {
            text: qsTr("Number: %1").arg(root.myObject.number)
            color: palette.text
        }

        Label {
            text: qsTr("String: %1").arg(root.myObject.string)
            color: palette.text
        }

        Button {
            text: qsTr("Increment Number")

            onClicked: root.myObject.incrementNumber()
        }

        Button {
            text: qsTr("Say Hi!")

            onClicked: root.myObject.sayHi(root.myObject.string, root.myObject.number)
        }

        Button {
            text: qsTr("Quit")

            onClicked: Qt.quit()
        }
    }
}
