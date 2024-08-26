function toMsecsSinceEpoch(date) {
    return date.getTime()
}

function yearsDatePickerList(currentYear,endYear) {
    // Create an empty array to store the years
    var yearsList = [];

    // Loop from the current year to the end year and add each year to the list
    for (let year = currentYear; year <= endYear; year++) {
        yearsList.push({ title: year });
    }
    return yearsList
}

function switchMonth(month) {
    switch (month) {
    case 0:
        return "January";
    case 1:
        return "February";
    case 2:
        return "March";
    case 3:
        return "April";
    case 4:
        return "May";
    case 5:
        return "Junw";
    case 6:
        return "July";
    case 7:
        return "August";
    case 8:
        return "September";
    case 9:
        return "October";
    case 10:
        return "November";
    case 11:
        return "December";
    default:
        throw new Error("Invalid month value. Must be between 0 and 11.");
    }
}

//returns a date string from format dd/MM/yyyy to format MM/dd/yyyy
function convertDateString(dateString) {
    if (dateString.length) {
        let dates = dateString.split('/')
        return `${dates[1]} ${dates[1]} ${dates[2]}`
    }
    else {
        return "";
    }
}
