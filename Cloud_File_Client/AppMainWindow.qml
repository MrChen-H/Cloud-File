import QtQuick
import QtQuick.Window
import FluentUI
import "./global"

FluWindow
{
    id: mainWindow

    // 避免双屏情景下的宽度溢出
    minimumWidth: 600
    minimumHeight: 400
    visible: true
    title: "Test Window"

    showDark: true

    closeListener: function (event) {

        dialog_close.open()
        // 取消窗口关闭
        event.accepted = false
    }
    // 退出软件确认提示框
    FluContentDialog {
        id: dialog_close
        title: "退出"
        message: "确定要退出程序吗？"
        negativeText: "最小化"
        buttonFlags: FluContentDialogType.NegativeButton | FluContentDialogType.NeutralButton
                     | FluContentDialogType.PositiveButton
        onNegativeClicked: {
            mainWindow.showMinimized()
        }
        positiveText: "退出"
        neutralText: "取消"
        onNeutralClicked:
        {
            showInfo("Cancel Click",2000)
        }

        onPositiveClicked: {
            FluApp.exit()
        }
    }


    Component.onCompleted:
    {
        var heightCach = mainWindow.height
        var widthCach = mainWindow.width

        mainWindow.hide()
        mainWindow.showMinimized()
        mainWindow.height = heightCach
        mainWindow.width = widthCach
        mainWindow.show()
    }

    Flipable{
        id:flipable
        anchors.fill: parent
        property bool flipped: false
        property real flipAngle: 0
        transform: Rotation {
            id: rotation
            origin.x: flipable.width/2
            origin.y: flipable.height/2
            axis { x: 0; y: 1; z: 0 }
            angle: flipable.flipAngle

        }
        states: State {
            PropertyChanges { target: flipable; flipAngle: 180 }
            when: flipable.flipped
        }
        transitions: Transition {
            NumberAnimation { target: flipable; property: "flipAngle"; duration: 1000 ; easing.type: Easing.OutCubic}
        }
        back: Item{
            anchors.fill: flipable
            visible: flipable.flipAngle !== 0
            Row{
                id:layout_back_buttons
                z:8
                anchors{
                    top: parent.top
                    left: parent.left
                    topMargin: FluTools.isMacos() ? 20 : 5
                    leftMargin: 5
                }
                FluIconButton{
                    iconSource: FluentIcons.ChromeBack
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        flipable.flipped = false
                    }
                }
                FluIconButton{
                    iconSource: FluentIcons.Sync
                    width: 30
                    height: 30
                    iconSize: 13
                    onClicked: {
                        loader.reload()
                    }
                }
            }
        }

        front: Item{
            id:page_front
            visible: flipable.flipAngle !== 180
            anchors.fill: flipable

            FluNavigationView{
                property int clickCount: 0
                id:nav_view
                width: parent.width
                height: parent.height
                z:999
                pageMode: FluNavigationViewType.NoStack
                footerItems:ItemsFooter

                topPadding:{
                    if(mainWindow.useSystemAppBar){
                        return 0
                    }
                    return FluTools.isMacos() ? 20 : 0
                }
                logo: ""
//                title:"FluentUI"

                /// log 点击事件
                onLogoClicked:{

                }
                autoSuggestBox:FluAutoSuggestBox{
                    iconSource: FluentIcons.Search

                    placeholderText: "搜索"
                    onItemClicked:
                        (data)=>{
                            ItemsOriginal.startPageByItem(data)
                        }
                }
                Component.onCompleted: {
                    AccountPage.navigationView = nav_view
                    ItemsFooter.navigationView = nav_view
                    ItemsFooter.paneItemMenu = nav_item_right_menu
                }
            }
        }
    }
    Component
    {
        id:nav_item_right_menu
        FluMenu
        {
            id:menu
            width: 130
            FluMenuItem
            {


            }
        }
    }
}
