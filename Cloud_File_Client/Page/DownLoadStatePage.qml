import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import DownLoadStateModel

FluContentPage {
    signal signalPauseClick(var beClickItem)
    signal signalPlayClick(var beClickItem)
    signal signaldeleteClick(var beClickItem)
    FluContentDialog {
        id: make_sure_dialog
        title: "全部移除"
        message: "确定要移除所有下载任务吗?这将会中断正在下载的项目"
        buttonFlags:FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton

        positiveText: "确定"
        neutralText: "取消"

        onPositiveClicked: {
            DownLoadStateModel.removeAll();
            showInfo("已全部取消");
        }
    }

    Row
    {
        spacing:10
        FluIconButton
        {
            id:downLoadAll
            iconSource:FluentIcons.Download
            FluTooltip
            {
                text: "全部开始"
                visible: downLoadAll.hovered
                delay: 1000
            }
        }
        FluIconButton
        {
            id:pauseAll
            iconSource: FluentIcons.Pause
            FluTooltip
            {
                text: "全部暂停"
                visible: pauseAll.hovered
                delay: 1000
            }
        }
        FluIconButton
        {
            id:deleteAll
            iconSource:FluentIcons.Delete
            FluTooltip
            {
                text: "全部移除"
                visible: deleteAll.hovered
                delay: 1000
            }
            onClicked:
            {
                make_sure_dialog.open()
            }
        }
    }

    ListView {
        width: parent.width
        height:parent.height-80
        id:downLoadInfoList
        focus: true
        anchors
        {
            bottom:parent.bottom
        }
        highlight:Item {

        }

        highlightFollowsCurrentItem: true
        model: DownLoadStateModel
        ScrollBar.vertical: FluScrollBar {}

        delegate: FluArea
        {
            id:downLoadProcessItem
            width: downLoadInfoList.width
            height: 60
            FluIcon
            {
                id:fileIcon
                anchors.verticalCenter: parent.verticalCenter

                x:10
                Component.onCompleted:
                {
                    if(fileType === "mp3")
                    {
                        iconSource = FluentIcons.MusicNote
                    }
                    else if(fileType === "mp4")
                    {
                        iconSource = FluentIcons.Video
                    }
                    else if(fileType === 'jpg')
                    {
                        iconSource = FluentIcons.Picture
                    }
                    else if(fileType === 'txt')
                    {
                        iconSource = FluentIcons.Document
                    }
                }
            }

            FluText {
                id:item_name
                font.pixelSize: 13
                y:15
                x:fileIcon.x+fileIcon.width+10
                width:200
                elide: Text.ElideRight
                text: fileName
                horizontalAlignment: Text.AlignLeft

            }
            FluText {
                id:downLoadSpeedText
                font.pixelSize: 11
                y:item_name.y+20
                x:fileIcon.x+fileIcon.width+10
                width:200
                wrapMode: Text.WrapAnywhere
                text:countSize
                horizontalAlignment: Text.AlignLeft
                opacity: 0.7
            }
            FluProgressBar{
                width: 250
                id:downLoadProcess
                x:bottonGroup.x-width-40
                progressVisible: true
                anchors
                {
                    verticalCenter: parent.verticalCenter
                }
                indeterminate: false

            }
            FluText {
                id:stateText
                font.pixelSize: 11
                y:downLoadProcess.y+downLoadProcess.height+5
                anchors.left: downLoadProcess.left
                width:50
                wrapMode: Text.WrapAnywhere
                text:"暂停中"
                horizontalAlignment: Text.AlignLeft
                opacity: 0.8
            }


            Row
            {
                id:bottonGroup
                x:parent.x+parent.width-80
                anchors.verticalCenter: parent.verticalCenter
                FluIconButton
                {
                    iconSource:FluentIcons.Play
                    iconSize: 10
                    onClicked:
                    {
                        if(iconSource === FluentIcons.Play)
                        {
                            iconSource = FluentIcons.Pause
                            signalPauseClick(downLoadProcessItem)
                            downLoadProcess.indeterminate = false
                            downLoadProcess.value = 0.5
                            stateText.text  = downLoadSpeed

                        }
                        else
                        {
                            iconSource = FluentIcons.Play
                            signalPlayClick(downLoadProcessItem)
                            downLoadProcess.indeterminate = true
                            stateText.text ="暂停中"

                        }

                    }
                }
                FluIconButton
                {
                    iconSource:FluentIcons.Cancel
                    iconSize: 10
                    onClicked:
                    {
                        signaldeleteClick(downLoadProcessItem)
                    }
                }
            }
        }
    }
}
