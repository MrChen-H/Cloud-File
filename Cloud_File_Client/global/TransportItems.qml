pragma Singleton

import QtQuick
import FluentUI
import  "../Page"
import UpLoadfileInfoMode
FluObject{
    property var navigationView
    property var paneItemMenu
    FluPaneItem{
        id:item_downLoadList
        title:"下载列表"
        url:"qrc:/Cloud_File_Client/Page/DownLoadStatePage.qml"
        icon:FluentIcons.Download
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_downLoadList.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_UpLoadList
        title:"上传列表"
        url:"qrc:/Cloud_File_Client/Page/UpLoadStatusPage.qml"
        icon:FluentIcons.OpenFile
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_UpLoadList.count = 0
            }
            navigationView.push(url)
        }
    }
    Connections
    {
        target: UpLoadfileInfoMode
        function onSignalJumpToUploadStatusPage()
        {
            navigationView.push("qrc:/Cloud_File_Client/Page/UpLoadStatusPage.qml")
            navigationView.setCurrentIndex(1)
        }
    }
}
