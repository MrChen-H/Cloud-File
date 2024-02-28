import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import AllFileModel 1.0

FluContentPage {
    id: allFilePage
    FluAutoSuggestBox{
        id:text_box
        iconSource: FluentIcons.Search
        placeholderText: "搜索文件"
    }
    GridView
    {
        id:grid_view
        cellWidth: 80
        cellHeight: 80
        clip: true
        boundsBehavior: GridView.StopAtBounds
        ScrollBar.vertical: FluScrollBar {}
        model:AllFileModel
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
                    if(fileType !== "vedio")
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
