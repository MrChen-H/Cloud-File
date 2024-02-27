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
    width: 800
    height: 400
    visible: true
    title: "Test Window"

    showDark: false

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
        nav_view.setCurrentIndex(0)
    }

    FluNavigationView{

        property int clickCount: 0
        id:nav_view
        width: parent.width
        height: parent.height
        cellWidth:130
        z:999
        pageMode: FluNavigationViewType.NoStack
        items: ItemsOriginal
        footerItems:ItemsFooter
        displayMode: FluNavigationViewType.Open
        hideNavAppBar: true
        topPadding:{
            if(mainWindow.useSystemAppBar){
                return 0
            }
            return FluTools.isMacos() ? 20 : 0
        }
        logo: ""
        onLogoClicked:{

        }
        Component.onCompleted: {
            ItemsFooter.navigationView = nav_view
            ItemsOriginal.navigationView = nav_view
        }
    }

}
