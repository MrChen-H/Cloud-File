pragma Singleton

import QtQuick
import FluentUI

FluObject{

    property var navigationView
    property var paneItemMenu

    id:footer_items

    FluPaneItemSeparator{}

    FluPaneItem{
        title:"账户信息"
        icon:FluentIcons.Contact
        onTapListener:function(){
            FluApp.navigate("/Account")
        }
    }

//    FluPaneItem{
//        title:Lang.settings
//        menuDelegate: paneItemMenu
//        icon:FluentIcons.Settings
//        url:"qrc:/example/qml/page/T_Settings.qml"
//        onTap:{
//            navigationView.push(url)
//        }
//    }

}
