import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtMultimedia 5.14
import Qt.labs.settings 1.0

import com.philnav.filters 1.0

Window {
    id: window
    visible: true
    title: qsTr("PhilNav")
    width: 960
    height: 480
    color: "#404040"

    property real fontPointSize: 16
    property color fontColor: "cyan"
    property int horizontalAlignment: Text.AlignHCenter
    property real gradientHeight: 25

    Settings {
        property alias hsvHueLow: hueSlider.first.value
        property alias hsvHueHigh: hueSlider.second.value
        property alias hsvSatLow: satSlider.first.value
        property alias hsvSatHigh: satSlider.second.value
        property alias hsvValLow: valSlider.first.value
        property alias hsvValHigh: valSlider.second.value
    }

    Camera {
        id: camera
        deviceId: QtMultimedia.availableCameras[0].deviceId
    }
    PhilNavFilter {
        id: philNavFilter
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
    Connections {
        target: philNavFilter
        onFrameProcessed: philNavImageTimer.start()
    }

    Flow {
        width: 640
        Item {
            width: 320
            height: 180
            VideoOutput {
                anchors.fill: parent
                source: camera
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

        Column {
            width: parent.width / 2
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
                id: satSlider
                width: parent.width
                from: 0
                to: 255
                first.value: 0
                second.value: 255
            }
        }
        Column {
            width: parent.width / 2
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
                id: valSlider
                width: parent.width
                from: 0
                to: 255
                first.value: 0
                second.value: 255
            }
        }

        Text {
            id: smile
            text: "Camera deviceId: " + camera.deviceId
            width: parent.width
            font.pointSize: window.fontPointSize
            color: window.fontColor
            horizontalAlignment: window.horizontalAlignment
        }
    }
}
