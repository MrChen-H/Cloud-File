import QtQuick
import QtQuick.Window
import FluentUI
import "./global"


FluWindow
{
    id: mainWindow
    objectName: 'mainWindow'

    // 避免双屏情景下的宽度溢出
    minimumWidth: 1000
    minimumHeight: 400
    width: 1000
    height: 500
    visible: true
    title: "Test Window"
    autoCenter: true
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
        nav_view.setCurrentIndex(0)
        mainWindow.hide()
        showMinimized()
        showMaximized()
        mainWindow.show()
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
