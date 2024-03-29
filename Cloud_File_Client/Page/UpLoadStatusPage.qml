﻿import QtQuick
import FluentUI
import QtQuick.Controls
import QtQuick.Window
import QtQuick.Layouts
import UpLoadfileInfoMode

FluContentPage {
    signal signalPauseClick(var beClickItem)
    signal signalPlayClick(var beClickItem)
    signal signaldeleteClick(var beClickItem)
    FluContentDialog {
        id: make_sure_dialog
        title: "全部移除"
        message: "确定要移除所有上传任务吗?这将会中断正在上传的项目"
        buttonFlags:FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton

        positiveText: "确定"
        neutralText: "取消"

        onPositiveClicked: {
            if(UpLoadfileInfoMode.getExistingTaskSize() === 0)
            {
                showWarning("没有上传任务");
            }
            else
            {
                UpLoadfileInfoMode.removeAll();
                showInfo("已全部移除");
            }


        }
    }
    FluContentDialog {
        id: cancelUploadTipBox
        title: "移除任务"
        message: "确定要移除该上传任务吗?"
        buttonFlags:FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton

        positiveText: "确定"
        neutralText: "取消"
        property var index: -1

        onPositiveClicked: {
            UpLoadfileInfoMode.remove(index)
            showInfo("已移除");
        }
    }

    Row
    {
        spacing:10
        FluIconButton
        {
            id:startAll
            iconSource:FluentIcons.Upload
            FluTooltip
            {
                text: "全部开始"
                visible: startAll.hovered
                delay: 1000
            }
            onClicked:
            {
                if(UpLoadfileInfoMode.getExistingTaskSize() === 0)
                {
                    showWarning("没有上传任务");
                }
                else
                {
                    UpLoadfileInfoMode.startUploadAll()
                    showInfo("已全部开始")
                }

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
            onClicked:
            {
                if(UpLoadfileInfoMode.getExistingTaskSize() === 0)
                {
                    showWarning("没有正在上传的任务")
                }
                else
                {
                    UpLoadfileInfoMode.pauseAllTask()
                    showInfo("已全部暂停")
                }


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
        id:upLoadInfoList
        focus: true
        spacing:10
        anchors
        {
            bottom:parent.bottom
        }

        model: UpLoadfileInfoMode
        ScrollBar.vertical: FluScrollBar {}

        delegate: FluArea
        {
            id:upLoadProcessItem
            width: upLoadInfoList.width-20
            height: 60
            FluIcon
            {
                id:fileIcon
                anchors.verticalCenter: parent.verticalCenter

                x:10
                Component.onCompleted:
                {

                    iconSource = FluentIcons.Document
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
                id:countSizeText
                font.pixelSize: 11
                y:item_name.y+20
                x:fileIcon.x+fileIcon.width+10
                width:200
                wrapMode: Text.WrapAnywhere
                text:alreadyUpload
                horizontalAlignment: Text.AlignLeft
                opacity: 0.7
            }
            FluProgressBar{
                width: 250
                id:upLoadProcess
                x:bottonGroup.x-width-60
                progressVisible: true
                anchors
                {
                    verticalCenter: parent.verticalCenter
                }
                indeterminate: false
                value:upLoadProess
            }
            FluText {
                id:stateText
                font.pixelSize: 11
                y:upLoadProcess.y+upLoadProcess.height+5
                anchors.left: upLoadProcess.left
                width:100
                wrapMode: Text.WrapAnywhere
                text:upLoadSpeed
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
                        if(stop === false)
                        {
                            UpLoadfileInfoMode.stopUploadByIndex(infoIndex)
                        }
                        else
                        {
                            UpLoadfileInfoMode.startUpLoadByIndex(infoIndex)
                        }
                    }
                    property var stop: isStop
                    onStopChanged:
                    {
                        if(stop === true)
                        {
                            iconSource = FluentIcons.Play
                        }
                        else
                        {
                            iconSource = FluentIcons.Pause
                        }
                    }
                }
                FluIconButton
                {
                    iconSource:FluentIcons.Cancel
                    iconSize: 10
                    onClicked:
                    {
                        cancelUploadTipBox.index = infoIndex
                        cancelUploadTipBox.open()
                    }
                }
            }
        }
    }
}
