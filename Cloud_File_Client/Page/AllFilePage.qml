import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import AllFileModel
FluContentPage {
    id: allFilePage
    property var selectItems: []
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

    FluMenu{
        id:menu
        width: 130
        FluMenuItem{
            text: "下载"
            visible: true
            iconSource:FluentIcons.Download
            onClicked: {
                if(selectItems.length === 0)
                {
                    showWarning("没有选中的文件")
                    return;
                }
            }
        }
        FluMenuItem{
            text: "复制"
            visible: true
            iconSource:FluentIcons.Copy
            onClicked: {
                if(selectItems.length === 0)
                {
                    showWarning("没有选中的文件")
                    return;
                }
            }
        }
        FluMenuItem{
            text: "粘贴"
            visible: true
            iconSource:FluentIcons.Paste
            onClicked: {
                if(selectItems.length === 0)
                {
                    showWarning("没有选中的文件")
                    return;
                }
            }
        }
        FluMenuItem{
            text: "剪切"
            visible: true
            iconSource:FluentIcons.Cut
            onClicked: {
                if(selectItems.length === 0)
                {
                    showWarning("没有选中的文件")
                    return;
                }
            }
        }
        FluMenuItem{
            text: "删除"
            visible: true
            iconSource:FluentIcons.Delete
            onClicked: {
                AllFileModel.test()
                if(selectItems.length === 0)
                {
                    showWarning("没有选中的文件")
                    return;
                }
            }
        }
        FluMenuItem{
            text: "上传文件"
            id: newFile
            visible: true
            iconSource:FluentIcons.OpenFile
            onClicked: {
            }
        }
        FluMenuItem{
            text: "新建目录"
            id: newFloder
            visible: true
            iconSource:FluentIcons.FileExplorer
            onClicked: {
            }
        }

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
            id: modelItem
            width: 68
            height: 80
            property var indexInView: -1
            FluIconButton
            {
                id:item_icon
                anchors.horizontalCenter: parent.horizontalCenter
                Component.onCompleted:
                {
                    if(fileType === "vedio")
                    {
                        iconSource = FluentIcons.Video
                    }
                    else if(fileType === "picture")
                    {
                        iconSource = FluentIcons.Picture
                    }
                    else if(fileType === "music")
                    {
                        iconSource = FluentIcons.MusicNote
                    }
                    else if(fileType === "other")
                    {
                        iconSource = FluentIcons.FileExplorer
                    }
                }
                Rectangle
                {
                    id:select_statue
                    anchors.fill: parent
                    color: "black"
                    radius: 5
                    opacity: 0.2
                    visible: false
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
            }
            MouseArea
            {
                acceptedButtons: Qt.AllButtons
                anchors.fill: parent
                z:999999
                /// 这段逻辑是实现item之间的选中状态改变
                onPressed:function(mouse)
                {
                    /// 在Item上右键打开菜单
                    if(mouse.button === Qt.RightButton)
                    {
                        menu.popup()
                    }
                    else if((mouse.button === Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier))
                    {
                        /// 如果是 Ctrl+右键 点击则多选Item
                        select_statue.visible = !select_statue.visible
                        selectItems.push(modelItem)
                    }
                    else if(mouse.button === Qt.LeftButton)
                    {
                        /// 左键点击且item已选中
                        if(select_statue.visible)
                        {
                            /// 如果被点击的item已经是选中状态则有两种情况
                            ///     1.是只有该item被选中想再次点击来取消选中
                            ///     2.是该Item与其他多个Item一起被选中此时点击该item应取消所有被选中的item的选中状态并选中当前item
                            for(var i = 0;i<selectItems.length;i++)
                            {
                                /// 清空所有选中item的选中状态
                                selectItems[i].cancelSelect()
                            }
                            /// 只有当前item选中的情况
                            if(selectItems.length === 0 || selectItems.length === 1)
                            {
                                selectItems.length = 0
                                select_statue.visible = false
                                return;
                            }
                            /// 多个item选中的情况
                            selectItems.length = 0
                            select_statue.visible = true
                            selectItems.push(modelItem)
                            return;
                        }
                        /// 左键点击且item没有被选中
                        /// 此时应取消所有item的选中状态并选中当前item
                        for(var j = 0;j<selectItems.length;j++)
                        {
                            selectItems[j].cancelSelect()
                        }
                        selectItems.length = 0
                        select_statue.visible = !select_statue.visible
                        selectItems.push(modelItem)
                        return;

                    }
                }
            }
            /// 清空item的选中状态
            function cancelSelect()
            {
                select_statue.visible = false
            }
            function setShowItem(isHide)
            {
                newFile.visible = isHide
                newFloder.visible = isHide
            }
        }
    }

}
