import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import FluentUI

FluWindow {

    id:window
    title:"关于"
    width: 600
    height: 580
    fixSize: true
    useSystemAppBar: true
    launchMode: FluWindowType.SingleTask

    Component.onCompleted:
    {
        var heightCach = window.height
        var widthCach = window.width

        window.hide()
        window.showMinimized()
        window.height = heightCach
        window.width = widthCach
        window.show()
    }
}
