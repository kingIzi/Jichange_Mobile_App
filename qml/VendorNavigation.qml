import QtQuick
import Felgo as Felgo
import "./pages"

Felgo.Navigation {
    id: _vendorNavigation
    //anchors.fill: parent
    //drawerLogoBackgroundColor: Qt.color("#8196FE")
    Felgo.NavigationItem {
        title: qsTr("Dashboard")
        iconType: Felgo.IconType.dashboard
        Felgo.NavigationStack {
            id: _dashboardStack
            initialPage: DashboardPage{}
        }
    }
    Felgo.NavigationItem {
        title: qsTr("Customer")
        iconType: Felgo.IconType.users
        Felgo.NavigationStack {
            id: _customerStack
            initialPage: CustomersPage{}
        }
    }
    Felgo.NavigationItem {
        title: qsTr("Company Users")
        iconType: Felgo.IconType.building
        Felgo.NavigationStack {
            id: companyUsersStack
            initialPage: CompanyUsersPage{}
        }
    }
    Felgo.NavigationItem {
        title: qsTr("Invoice Details")
        iconType: Felgo.IconType.filetext
        Felgo.NavigationStack {
            id: _invoiceDetailsStack
            initialPage: InvoiceDetailsPage{}
        }
    }
    Felgo.NavigationItem {
        title: qsTr("Generated Invoice")
        iconType: Felgo.IconType.exchange
        Felgo.NavigationStack {
            initialPage: GeneratedInvoicePage{}
        }
    }
    Felgo.NavigationItem {
        title: qsTr("Profile")
        iconType: Felgo.IconType.user
        Felgo.NavigationStack {
            initialPage: UserProfilePage{}
        }
    }
}
