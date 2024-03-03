import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Dialogs
import QtQuick.Layouts
import AllFileModel
import NetWorkOperation
import UpLoadfileInfoMode
FluContentPage {
    id: allFilePage
    objectName: 'allFilePage'
    property var selectItems: [] ///2024-03-03 23:16:16 MrChen-H:use property selectItems store be selected item,
                                 /// This is to achieve a Windows-like file selection operation
    property var serchItems:[]
    FluAutoSuggestBox{
        id:text_box
        iconSource: FluentIcons.Search
        items: serchItems
        placeholderText: "搜索文件"

    }
    NetWorkOperation
    {
        id:netWork
    }


    Component.onCompleted:
    {
        netWork.get("http://111.229.83.106/GetFileInfo")
    }
    Connections
    {
        target: netWork
        function onSignalRequestStart()
        {
            statusPage.statusMode = FluStatusLayoutType.Loading
            text_box.items.length = 0
            selectItems.length = 0
        }
        function onSignalRequestEnd(getData,errorCode,errorString)
        {
            if (100 > errorCode||errorCode < 200 || errorCode >= 300)
            {
                statusPage.errorText = errorString
                statusPage.statusMode = FluStatusLayoutType.Error
            }
            else if(errorCode >= 200 && errorCode <= 300)
            {
                statusPage.statusMode = FluStatusLayoutType.Success
            }
            else
            {
                statusPage.errorText = errorString
                statusPage.statusMode = FluStatusLayoutType.Error
            }
            console.log("http:",errorCode)
        }
    }

    FileDialog
    {
        id:selectFileDialog
        title: "选择文件"
        nameFilters: ["选择文件 (*.*)"]

        onAccepted:
        {
            ///2024-03-03 23:04:20 MrChen-H: Append an upload task to UpLoadfileInfoMode and start uploading
            UpLoadfileInfoMode.appendByOne(selectedFile)

            ///2024-03-03 23:06:12 MrChen-H: Jump to upload info page
            UpLoadfileInfoMode.jumpToTransportPage()
            UpLoadfileInfoMode.jumpToUploadStatusPage()
        }
    }
    FileDialog
    {
        id:selectAddtoUpLoadFileQueue
        title: "选择文件"
        fileMode: FileDialog.OpenFiles
        nameFilters: ["选择文件 (*.*)"]
        onAccepted:
        {
            ///2024-03-03 23:07:01 MrChen-H: Append some upload tasks to UpLoadfileInfoMode and start uploading task when click upload button
            UpLoadfileInfoMode.append(selectedFiles)
            UpLoadfileInfoMode.jumpToTransportPage()
            UpLoadfileInfoMode.jumpToUploadStatusPage()
        }
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
        FluMenu
        {
           title: "上传"
            FluMenuItem{
                text: "上传文件"
                id: newFile
                visible: true
                iconSource:FluentIcons.OpenFile
                onClicked: {
                    selectFileDialog.open()
                }
            }
            FluMenuItem{
                text: "添加到上传队列"
                id: addToUpLoadQueue
                visible: true
                iconSource:FluentIcons.OpenFile
                onClicked: {
                    selectAddtoUpLoadFileQueue.open()
                }
            }

        }


        FluMenuItem{
            text: "详细信息"
            id: newFloder
            visible: true
            iconSource:FluentIcons.Info
            onClicked: {
            }
        }

    }
    ///2024-03-03 23:10:22 MrChen-H: Flush page on click button
    FluIconButton
    {
        // 刷新按钮
        iconSource:FluentIcons.Refresh
        anchors.right: parent.right
        onClicked:
        {
            selectItems.length = 0
            netWork.get("http://111.229.83.106/GetFileInfo");
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
        FluStatusLayout{
            id:statusPage
            anchors.fill: parent
            color: "transparent"
            statusMode: FluStatusLayoutType.Empty
            visible: false
            ///2024-03-03 23:11:31 MrChen-H: Click reload button get file infomation to refresh the page
            onErrorClicked:
            {
                netWork.get("http://111.229.83.106/GetFileInfo");
            }
        }


        ///2024-03-03 23:13:30 MrChen-H: Show file infomation item
        delegate:Item
        {
            id: modelItem
            width: 68
            height: 80
            property var indexInView: -1
            z:9999

            FluIconButton
            {
                id:item_icon
                anchors.horizontalCenter: parent.horizontalCenter

                FluTooltip
                {
                    id:fileNameTooltip
                    text:fileName
                    visible: false
                    delay: 1000
                }

                ///2024-03-03 23:14:07 MrChen-H: Display different icons by file type Note:this function is not completed
                Component.onCompleted:
                {
                    if(fileType === "video")
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
                    else
                    {
                        iconSource = FluentIcons.Document
                    }
                }
                MouseArea
                {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        fileNameTooltip.visible = true
                    }
                    onExited: {
                        fileNameTooltip.visible = false
                    }
                }
                ///2024-03-03 23:38:24 MrChen-H: show this rectangle when item be selected
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
                Component.onCompleted:
                {
                    serchItems.push({title:fileName})
                }
            }
            MouseArea
            {
                acceptedButtons: Qt.AllButtons
                anchors.fill: parent
                z:999999
                ///2024-03-03 23:33:44 MrChen-H: item's selected statu change
                onPressed:function(mouse)
                {
                    if((mouse.button === Qt.LeftButton) && (mouse.modifiers & Qt.ControlModifier))
                    {
                        ///2024-03-03 23:33:44 MrChen-H: if left mouse button and ctrl click ,mulit select item
                        select_statue.visible = !select_statue.visible
                        selectItems.push(modelItem)
                    }
                    else if(mouse.button === Qt.LeftButton || mouse.button === Qt.RightButton)
                    {
                        if(mouse.button === Qt.RightButton)
                        {
                            menu.popup()
                            if(select_statue.visible)
                            {
                                return;
                            }
                        }
                        ///2024-03-03 23:33:44 MrChen-H: if left mouse button click and this item already be selected
                        if(select_statue.visible)
                        {
                            ///2024-03-03 23:33:44 MrChen-H: There are two possibilities
                            ///     1.only this item be selected and user want cancel selected statu by clicked again 是只有该item被选中想再次点击来取消选中
                            ///     2.this item and other item selected together, at this time click this item should cancel all items selected statu an selected this item  是该Item与其他多个Item一起被选中此时点击该item应取消所有被选中的item的选中状态并选中当前item
                            for(var i = 0;i<selectItems.length;i++)
                            {
                                ///2024-03-03 23:33:44 MrChen-H: claer all be selected item's select status
                                selectItems[i].cancelSelect()
                            }
                            ///2024-03-03 23:33:44 MrChen-H: only this item be selected
                            if(selectItems.length === 0 || selectItems.length === 1)
                            {
                                selectItems.length = 0
                                select_statue.visible = false
                                return;
                            }
                            ///2024-03-03 23:33:44 MrChen-H: Multiple items are selected
                            selectItems.length = 0
                            select_statue.visible = true
                            selectItems.push(modelItem)
                            return;
                        }
                        ///2024-03-03 23:33:44 MrChen-H: mouse left botton click and this item don't be selected
                        ///2024-03-03 23:33:44 MrChen-H: cancel all item's select status and select this item
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
            ///2024-03-03 23:33:44 MrChen-H: clear item select status
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
        onCountChanged:
        {
            if(count === 0)
            {
                ///2024-03-03 23:41:03 MrChen-H: if don't have file info,show empty status page
                statusPage.visible = true
            }
            else
            {
                statusPage.visible = false
            }

        }
        MouseArea
        {
            anchors.fill: parent
            acceptedButtons: Qt.AllButtons
            propagateComposedEvents: true
            onClicked:function(mouse)
            {
                console.log("Test")
            }
            onPressed:function(mouse)
            {
                ///2024-03-03 23:42:26 MrChen-H: if right mouse button click and there is no click to item, show menu
                for(var x = 0; x< selectItems.length;x++)
                {
                    selectItems[x].cancelSelect()
                }
                selectItems.length = 0

                if(mouse.button === Qt.RightButton)
                {
                    menu.popup()
                }

                mouse.accepted = false
            }
            onReleased:function(mouse)
            {
                mouse.accepted = false
            }

        }

    }

    /**
    * @author MrChen-H
    * @date 2024-03-03 23:45:46
    * @brief set this page statu to loading or other statu
    * @param bool isLoading is loading or not
    * @param
    * @return don't have return value
    */
    function setLoading(isLoading)
    {
        if(isLoading === true)
        {
            statusPage.statusMode = FluStatusLayoutType.Loading
        }
        else if(grid_view.count === 0)
        {
            statusPage.statusMode = FluStatusLayoutType.Empty
        }
        else
        {
            statusPage.statusMode = FluStatusLayoutType.Success
        }
    }

}
