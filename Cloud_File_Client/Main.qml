import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window
import FluentUI
import "./global"

ApplicationWindow
{
    id: app
    flags: Qt.SplashScreen
    // 一定要是false
    visible: false
    Component.onCompleted: {
        // 初始化FluApp，实质是记录了app这个根组件实例用以获取QQmlEngine
        // 然后从engine中以initialRoute文本找到用户定义的组件.qml(在这里是AppMainWindow.qml)
        // 实例化AppMainWindow，在窗口实例表中对照是否已有相同窗口存在，若存在则会判断launchMode
        // 所以AppMainWindow要继承自FluWindow, 否则必须自行添加Property: _pageRegister 、 argument、 _route、 launchMode
        FluApp.init(app)
        // 相关枚举大部分都在Def.h里
        FluTheme.darkMode = FluThemeType.Light
        // 开启动画
        FluTheme.enableAnimation = true
        // 切换主题色
        // FluTheme.primaryColor = FluColors.Orange
        // 路由表
        FluApp.routes = {
            "/": "qrc:/Cloud_File_Client/AppMainWindow.qml",
            "/Account" : "qrc:/Cloud_File_Client/Page/AccountPage.qml",
            "/MyFile" : "qrc:/Cloud_File_Client/Page/MyFile.qml",
            "/AllFile" : "qrc:/Cloud_File_Client/Page/AllFile.qml"
        }
        // 初始化路径
        FluApp.initialRoute = "/"
        FluApp.run()
    }

}
