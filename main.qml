import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtMultimedia 5.14

import com.philipbrocoum.philnav 1.0

Window {
    id: window
    visible: true
    title: qsTr("PhilNav")
    width: 640
    height: 480
    color: "#404040"

    property real fontPointSize: 16
    property color fontColor: "cyan"
    property int horizontalAlignment: Text.AlignHCenter
    property real gradientHeight: 25

    Camera {
        id: camera
        deviceId: QtMultimedia.availableCameras[0].deviceId
    }
    PhilNavFilter {
        id: philNavFilter
    }
    Connections {
        id: philNavFilterOnFrameProcessedConnection
        target: philNavFilter
        onFrameProcessed: philNavImageTimer.start()
    }
    Timer {
        id: philNavImageTimer
        interval: 1
        running: false
        repeat: false
        onTriggered: {
            smile.color = Qt.rgba(Math.random(), Math.random(),
                                  Math.random(), 1)
            philNavImage.source = ""
            philNavImage.source = "image://philnavimageprovider/0"
        }
    }

    Flow {
        anchors.fill: parent

        Item {
            width: 320
            height: 180
            VideoOutput {
                source: camera
                anchors.fill: parent
                filters: [philNavFilter]
            }
        }
        Item {
            width: 320
            height: 180
            Image {
                id: philNavImage
                anchors.fill: parent
                cache: false
            }
        }

        Text {
            text: qsTr("Hue")
            width: parent.width
            font.pointSize: window.fontPointSize
            color: window.fontColor
            horizontalAlignment: window.horizontalAlignment
        }
        Rectangle {
            width: parent.width
            height: window.gradientHeight
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop {
                    position: 0 / 6
                    color: "red"
                }
                GradientStop {
                    position: 1 / 6
                    color: "yellow"
                }
                GradientStop {
                    position: 2 / 6
                    color: "green"
                }
                GradientStop {
                    position: 3 / 6
                    color: "cyan"
                }
                GradientStop {
                    position: 4 / 6
                    color: "blue"
                }
                GradientStop {
                    position: 5 / 6
                    color: "magenta"
                }
                GradientStop {
                    position: 6 / 6
                    color: "red"
                }
            }
        }
        RangeSlider {
            id: hueSlider
            width: parent.width
            from: 0
            to: 359
            first.value: 0
            second.value: 359
        }

        Text {
            text: qsTr("Saturation")
            width: parent.width
            font.pointSize: window.fontPointSize
            color: window.fontColor
            horizontalAlignment: window.horizontalAlignment
        }
        Rectangle {
            width: parent.width
            height: window.gradientHeight
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop {
                    position: 0
                    color: "gray"
                }
                GradientStop {
                    position: 1
                    color: Qt.hsva(
                               ((hueSlider.first.value + hueSlider.second.value) / 2 / 360),
                               1, 1, 1)
                }
            }
        }
        RangeSlider {
            width: parent.width
            from: 0
            to: 255
            first.value: 0
            second.value: 255
        }

        Text {
            text: qsTr("Value")
            width: parent.width
            font.pointSize: window.fontPointSize
            color: window.fontColor
            horizontalAlignment: window.horizontalAlignment
        }
        Rectangle {
            width: parent.width
            height: window.gradientHeight
            gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop {
                    position: 0
                    color: "black"
                }
                GradientStop {
                    position: 1
                    color: "white"
                }
            }
        }
        RangeSlider {
            width: parent.width
            from: 0
            to: 255
            first.value: 0
            second.value: 255
        }

        Rectangle {
            id: smile
            width: 100
            height: window.gradientHeight
            color: "red"
            border.color: "black"
            border.width: 5
            radius: 10
        }
    }
}
