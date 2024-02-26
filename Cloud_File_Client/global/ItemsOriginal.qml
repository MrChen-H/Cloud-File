pragma Singleton

import QtQuick
import FluentUI

FluObject{

    property var navigationView
    property var paneItemMenu
    FluPaneItem{
        id:item_home
        title:"主页"

        infoBadge:FluBadge{
            count: item_home.count
        }
        icon:FluentIcons.Home
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_home.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_myFile
        title:"我的文件"

        icon:FluentIcons.ContactInfoMirrored
        url:"qrc:/Cloud_File_Client/Page/MyFile.qml"
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_myFile.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_AllFile
        title:"全部文件"

        infoBadge:FluBadge{
            count: item_AllFile.count
        }
        icon:FluentIcons.BulletedListMirrored
        url:"qrc:/Cloud_File_Client/Page/AllFile.qml"
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_AllFile.count = 0
            }
            navigationView.push(url)
        }
    }
}
