pragma Singleton

import QtQuick
import FluentUI

FluObject{

    property var navigationView
    property var paneItemMenu
    FluPaneItem{
        id:item_otherFile
        title:"全部"
        icon:FluentIcons.FileExplorer
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_vdieo.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_vdieo
        title:"视频"
        icon:FluentIcons.Video
        url:"qrc:/Cloud_File_Client/Page/VideoPage.qml"
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_vdieo.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_picture
        title:"图片"
        icon:FluentIcons.Picture
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_vdieo.count = 0
            }
            navigationView.push(url)
        }
    }
    FluPaneItem{
        id:item_music
        title:"音乐"
        icon:FluentIcons.MusicNote
        onTap:{
            if(navigationView.getCurrentUrl()){
                item_vdieo.count = 0
            }
            navigationView.push(url)
        }
    }

}
