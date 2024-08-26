var baseUrl = "http://192.168.100.50:98"

function createLoginPayload(loginPayload) {
    const payload = {
        "userName": loginPayload.userName,
        "password": loginPayload.password
    };
    return payload
}

function requestJsonPlaceholder(HttpRequest) {
    HttpRequest
    .get("https://jsonplaceholder.typicode.com/posts")
    .set("Content-Type","application/json")
    .timeout(6000)
    .end(function (err,res) {
        if (res.ok) {
            console.log(res.status)
            console.log(JSON.stringify(res.body))
        }
        else {
            console.log(res.response)
            console.log(res.message)
        }
    });
}

function requestAddInvoice(Felgo,body) {
    console.log(JSON.stringify(body))
    let r1 = Felgo.HttpRequest
    .post(`${baseUrl}/api/Invoice/AddInvoice`)
    .set("Content-Type","application/json")
    .send(body)
    .timeout(6000)
    .then(function (res) { ;return res.body; })
    .catch(function(err) {
        Felgo.NativeUtils.displayMessageBox(qsTr("Failed"),qsTr("Failed to add invoice"),2)
    });

    let data = Felgo.Promise.all([r1]);
    return data;
}

function addInvoiceRequests(Felgo,customersBody) {
    let r1 = Felgo.HttpRequest
    .get(`${baseUrl}/api/Invoice/GetCurrency`)
    .set("Content-Type","application/json")
    .timeout(6000)
    .then(function (res) { return res.body; })

    let r2 = Felgo.HttpRequest
    .post(`${baseUrl}/api/Invoice/GetCustomersS`)
    .set("Content-Type","application/json")
    .send({compid: customersBody.InstID})
    .timeout(6000)
    .then(function (res) { return res.body; })

    let data = Felgo.Promise.all([r1, r2]);
    return data;
}

function requestGeneratedInvoiceDetails(Felgo,body,page,limit) {
    let r1 = Felgo.HttpRequest
    .post(`${baseUrl}/api/Invoice/GetSignedDetails?page=${page}&limit=${limit}`)
    .set("Content-Type","application/json")
    .set("Authorization","Bearer " + body.Token)
    .send({compid: body.InstID})
    .timeout(6000)
    .then(function (res) { return res.body; })
    .catch(function(err) {
        console.error(err)
        Felgo.NativeUtils.displayMessageBox(qsTr("Failed"),qsTr("Failed to fetch generated invoices."),2)
    });

    let data = Felgo.Promise.all([r1]);
    return data;
}



