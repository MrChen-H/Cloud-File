﻿pragma Singleton

import QtQuick
import FluentUI
import UpLoadfileInfoMode

FluObject{

    property var navigationView
    property var paneItemMenu

    Connections
    {
        target:UpLoadfileInfoMode
        function onSignalJumpToTransportPage()
        {
            navigationView.push("qrc:/Cloud_File_Client/Page/TransportPage.qml")
            navigationView.setCurrentIndex(2)
        }
    }

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
        url:"qrc:/Cloud_File_Client/Page/TransportPage.qml"
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_DownLoadState.count = 0
            }
            navigationView.push(url)
        }

    }
}
