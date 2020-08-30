import QtQuick 2.12
import ".."

ProjectsPageForm {
    property string pageType: "projects"

    // hide tabbar
    Connections {
        target: plmData.projectHub()
        onProjectCountChanged: function (count){
            if(count <= 1){
                tabBar.visible = false
            }
            else {
                tabBar.visible = true
            }

        }
    }

}
