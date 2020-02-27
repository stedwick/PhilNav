import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import QtMultimedia 5.14

import com.philnav.classes 1.0

Window {
    visible: true
    width: 640
    height: 480
    color: "#00000000"
    title: qsTr("PhilNav")

    CvDetectFilter
    {
        id: hsvFilter
        onObjectDetected :
        {
            smile.color = Qt.rgba(Math.random(),Math.random(),Math.random(),1);
        }
    }

    Camera {
        id: camera
    }
    Camera {
        id: camera_hsv
    }

    Flow {
        anchors.fill: parent

        Item {
            width: 320
            height: 180

            VideoOutput {
                source: camera
                anchors.fill: parent
            }

        }
        Item {
            width: 320
            height: 180
            VideoOutput {
                source: camera_hsv
                anchors.fill: parent
                filters : [hsvFilter]
            }
        }

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Hue")
            font.pointSize: 16
            color: "cyan"
        }
        Rectangle {
            width: parent.width
            height: 25
            gradient: Gradient {
                GradientStop { position: 0/6; color: "red" }
                GradientStop { position: 1/6; color: "yellow" }
                GradientStop { position: 2/6; color: "green" }
                GradientStop { position: 3/6; color: "cyan" }
                GradientStop { position: 4/6; color: "blue" }
                GradientStop { position: 5/6; color: "magenta" }
                GradientStop { position: 6/6; color: "red" }
                orientation: Gradient.Horizontal
            }
        }
        RangeSlider {
            id: hueSlider
            width: parent.width;
            from: 0
            to: 359
            first.value: 0
            second.value: 359
        }

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Saturation")
            font.pointSize: 16
            color: "cyan"
        }
        Rectangle {
            width: parent.width;
            height: 25
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 1; color: Qt.hsva(((hueSlider.first.value + hueSlider.second.value)/2/360), 1, 1, 1) }
                orientation: Gradient.Horizontal
            }
        }
        RangeSlider {
            width: parent.width;
            from: 0
            to: 255
            first.value: 0
            second.value: 255
        }

        Text {
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: qsTr("Value")
            font.pointSize: 16
            color: "cyan"
        }
        Rectangle {
            width: parent.width;
            height: 25
            gradient: Gradient {
                GradientStop { position: 0; color: "black" }
                GradientStop { position: 1; color: "white" }
                orientation: Gradient.Horizontal
            }
        }
        RangeSlider {
            width: parent.width;
            from: 0
            to: 255
            first.value: 0
            second.value: 255
        }

        Rectangle {
            id: smile
            width: 100
            height: 25
            color: "red"
            border.color: "black"
            border.width: 5
            radius: 10
        }
    }
}
