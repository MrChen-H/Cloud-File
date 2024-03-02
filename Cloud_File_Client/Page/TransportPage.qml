import QtQuick
import FluentUI
import "../global"
Item
{
    FluNavigationView{
        cellWidth:150
        property int clickCount: 0
        id:nav_view
        width: 800
        height: 400

        z:999

        anchors{
            fill: parent
        }

        hideNavAppBar:true
        displayMode: FluNavigationViewType.Open
        pageMode: FluNavigationViewType.Stack
        items: TransportItems

        Component.onCompleted: {
            TransportItems.navigationView = nav_view
            TransportItems.paneItemMenu = nav_item_right_menu
            nav_view.setCurrentIndex(0)
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
