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
        url:"qrc:/Cloud_File_Client/Page/HomePage.qml"
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
        id:item_DownLoadState
        title:"传输状态"

        infoBadge:FluBadge{
            count: item_DownLoadState.count
        }
        icon:FluentIcons.BulletedListMirrored
        url:"qrc:/Cloud_File_Client/Page/DownLoadStatePage.qml"
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_DownLoadState.count = 0
            }
            navigationView.push(url)
        }
    }
}
