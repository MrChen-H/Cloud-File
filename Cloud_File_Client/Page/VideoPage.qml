import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

FluContentPage {
    id: allFilePage
    FluAutoSuggestBox{
        id:text_box
        iconSource: FluentIcons.Search
        placeholderText: "搜索文件"
    }
    ListModel {
        id: myModel
        ListElement { imageType: "vedio";fileName :"美少女.mp4"}
        ListElement { imageType: "vedio";fileName :"原神启动.mp4"}
        ListElement { imageType: "picture";fileName :"高清.jpg"}
        ListElement { imageType: "picture";fileName :"原神.jpg"}
        ListElement { imageType: "picture";fileName :"明日方舟.jpg"}
        ListElement { imageType: "music";fileName :"原神.mp3"}
        ListElement { imageType: "music";fileName :"原神.mp3"}
        ListElement { imageType: "music";fileName :"原神.mp3"}
        ListElement { imageType: "other";fileName :"原神.xsd"}
        ListElement { imageType: "other";fileName :"原神.txt"}
        // 更多ListElement...
    }
    GridView
    {
        id:grid_view
        cellWidth: 80
        cellHeight: 80
        clip: true
        boundsBehavior: GridView.StopAtBounds
        ScrollBar.vertical: FluScrollBar {}
        model:myModel
        anchors{
            topMargin: 10
            top:text_box.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        delegate:Item
        {
            width: 68
            height: 80
            FluIconButton
            {
                id:item_icon
                anchors.horizontalCenter: parent.horizontalCenter
                Component.onCompleted:
                {
                    if(imageType !== "vedio")
                    {
                        destroy()
                    }
                    else
                    {
                        iconSource = FluentIcons.Video
                    }

                }
            }
            FluText {
                id:item_name
                font.pixelSize: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: item_icon.bottom
                width:parent.width
                wrapMode: Text.WrapAnywhere
                text: fileName
                horizontalAlignment: Text.AlignHCenter
                Component.onCompleted:
                {
                    if(imageType !== "vedio")
                    {
                        destroy()
                    }
                }
            }
        }
    }
}
