import QtQuick

ListModel {
    ListElement {
        stat: 12
        label: "Transaction"
        img: "../../assets/img/transaction.png"
        increased: true
        navToIndex: 2
    }
    ListElement {
        stat: 0
        label: "Due"
        img: "../../assets/img/check-mark.png"
        increased: false
        navToIndex: 2
    }
    ListElement {
        stat: 0
        label: "Expired"
        img: "../../assets/img/man.png"
        increased: false
        navToIndex: 3
    }
    ListElement {
        stat: 0
        label: "Customer(s)"
        img: "../../assets/img/customer-review.png"
        increased: true
        navToIndex: 1
    }

}
