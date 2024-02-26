import QtQuick
import FluentUI
import "../global"
Item
{
//    FluButton
//    {
//        text: "Test"
//    }

    FluNavigationView{
        property int clickCount: 0
        id:nav_view
        width: 999900
        height: 999900
        z:999
        hideNavAppBar:true
        displayMode: FluNavigationViewType.Open
        pageMode: FluNavigationViewType.NoStack
        items: MyFileItems

        Component.onCompleted: {
            MyFileItems.navigationView = nav_view
            MyFileItems.paneItemMenu = nav_item_right_menu
        }
    }
    Component
    {
        id:nav_item_right_menu
        FluMenu
        {
            id:menu
            width: 50
            FluMenuItem
            {


            }
        }
    }
}
