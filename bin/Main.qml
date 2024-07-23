import QtQuick
import QtQuick.Window
import QtPositioning
import QtLocation
//import io.qdebugenv.rendering 1.0 as QDE_Rendering

Window {
    width: 1000
    height: 800
    visible: true
    title: "Hello World"

    Map {
        id: map
        layer {
            enabled: true
            smooth: true
            samples: 8
        }
        anchors.fill: parent
        center: QtPositioning.coordinate(60, 39.7)
        activeMapType: map.supportedMapTypes[1]
        copyrightsVisible: false
        tilt: 15
        zoomLevel: 14
        plugin: Plugin {
            name: "qnx"
        }

        Behavior on center { CoordinateAnimation { duration: 250; easing.type: Easing.InOutQuad } }
        Behavior on zoomLevel { NumberAnimation { duration: 250; easing.type: Easing.InOutCubic } }

        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            onRotationChanged: (delta) => {
                map.bearing -= delta
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            grabPermissions: PointerHandler.TakeOverForbidden
        }

        WheelHandler {
            id: wheel
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                ? PointerDevice.Mouse | PointerDevice.TouchPad
                : PointerDevice.Mouse
            rotationScale: 1/12
            property: "zoomLevel"
        }

        DragHandler {
            id: drag
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }

        Shortcut {
            enabled: map.zoomLevel < map.maximumZoomLevel
            sequences: [ StandardKey.ZoomIn ]
            onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
        }

        Shortcut {
            enabled: map.zoomLevel > map.minimumZoomLevel
            sequence: StandardKey.ZoomOut
            onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
        }
    }
}