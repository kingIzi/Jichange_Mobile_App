import QtQuick
import QtQuick.Controls.Material as QC2
import Felgo as Felgo

Felgo.App {
    id: _root
    readonly property alias _extraBoldFont: _interExtraBoldFont
    FontLoader {
        id: _interRegularFont
        source: "../assets/fonts/Inter-Regular.ttf" // loaded from your assets folder
    }
    FontLoader {
        id: _interExtraBoldFont
        source: "../assets/fonts/Inter-ExtraBold.ttf" // loaded from your assets folder
    }
    signal toPotrait()
    signal toLandscape()
    onInitTheme: {
        Felgo.Theme.normalFont = _interRegularFont
        Felgo.Theme.boldFont = _interExtraBoldFont
        Felgo.Theme.navigationBar.backgroundColor = Qt.color("#8196FE")
        Felgo.Theme.navigationAppDrawer.backgroundColor = Qt.color("#ffffff")
        Felgo.Theme.tabBar.backgroundColor = Qt.color("#ffffff")
        Felgo.HttpRequest.config({ cache: true });
        //Felgo.Theme.appButton.backgroundColor = Qt.color("#8196FE")
        //Felgo.Theme.appButton.backgroundColorHovered = Qt.color("#516efe")
        //Felgo.Theme.tintColor = Qt.color("#8196FE")
    }
//    onPortraitChanged: {
//        if (portrait) {
//            console.log("TO POTRAIT")
//            _root.toPotrait()
//        }
//    }
//    onLandscapeChanged: {
//        if (landscape) {
//            console.log("TO LANDSCAPE")
//            _root.toLandscape()
//        }
//    }

    Loader {
        id: _mainLoader
        anchors.fill: parent
        visible: true
        active: visible
        source: "./AuthPage.qml"
        //state: "Vendor"
        state: _authRequests.isLoggedIn ? "Vendor" : "Auth"
        //state: false ? "Vendor" : "Auth"
        states: [
            State {
                name: "Auth"
                PropertyChanges {
                    target: _mainLoader
                    source: "./AuthPage.qml"
                }
            },
            State {
                name: "Vendor"
                PropertyChanges {
                    target: _mainLoader
                    source: "./VendorNavigation.qml"
                }
            }
        ]
    }
}
