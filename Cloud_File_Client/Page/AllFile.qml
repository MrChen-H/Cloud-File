import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts

FluContentPage {
    FluAutoSuggestBox{
        id:text_box
        iconSource: FluentIcons.Search
        placeholderText: "搜索文件"
    }
    GridView{
        id:grid_view
        cellWidth: 80
        cellHeight: 80
        clip: true
        boundsBehavior: GridView.StopAtBounds
        model:FluTheme.awesomeList()
        ScrollBar.vertical: FluScrollBar {}
        anchors{
            topMargin: 10
            top:text_box.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        delegate: Item {
            width: 68
            height: 80
            FluIconButton{
                id:item_icon
                iconSource:modelData.icon
                anchors.horizontalCenter: parent.horizontalCenter
                onClicked: {
                    var text  ="FluentIcons."+modelData.name;
                    FluTools.clipText(text)
                    showSuccess("您复制了 "+text)
                }
            }
            FluText {
                id:item_name
                font.pixelSize: 10
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: item_icon.bottom
                width:parent.width
                wrapMode: Text.WrapAnywhere
                text: modelData.name
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }
}
