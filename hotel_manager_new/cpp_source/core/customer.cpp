#include "customer.h"
#include "QDateTime"


/* construction functions below */
OrdinaryCustomer::OrdinaryCustomer(int customerType, int customerID, QString userName,
                                   QString phone, QString checkInTime, QString checkOutTime,
                                   QString scheduleTime, QString roomNumber) {
    this->customerType = customerType;
    this->customerID = customerID;
    this->userName = userName;
    this->phone = phone;
    this->checkInTime = checkInTime;
    this->checkOutTime = checkOutTime;
    this->scheduleTime = scheduleTime;
    this->roomNumber = roomNumber;
}


VIPCustomer::VIPCustomer(int customerType, int customerID, QString userName,
                         QString phone, QString checkInTime, QString checkOutTime,
                         QString scheduleTime, QString roomNumber, QString vipNumber, int point) {
    this->customerType = customerType;
    this->customerID = customerID;
    this->userName = userName;
    this->phone = phone;
    this->checkInTime = checkInTime;
    this->checkOutTime = checkOutTime;
    this->scheduleTime = scheduleTime;
    this->roomNumber = roomNumber;
    this->vipNumber = vipNumber;
    this->point = point;
}

SVIPCustomer::SVIPCustomer(int customerType, int customerID, QString userName,
                           QString phone, QString checkInTime, QString checkOutTime,
                           QString scheduleTime, QString roomNumber, QString vipNumber,
                           int point, float deposit) {
    this->customerType = customerType;
    this->customerID = customerID;
    this->userName = userName;
    this->phone = phone;
    this->checkInTime = checkInTime;
    this->checkOutTime = checkOutTime;
    this->scheduleTime = scheduleTime;
    this->roomNumber = roomNumber;
    this->vipNumber = vipNumber;
    this->point = point;
    this->deposit = deposit;
}


/* get type name functions below */
QString OrdinaryCustomer::getCustomerTypeName() {
    return QString("ordinary");
}


QString VIPCustomer::getCustomerTypeName() {
    return QString("VIP");
}


QString SVIPCustomer::getCustomerTypeName() {
    return QString("SVIP");
}


CustomerList::CustomerList() {

}



void CustomerList::add(Customer* customer) {
    list.push_back(customer);
}


Customer* CustomerList::get(int customerID) {
    CUSTOMERLIST::iterator i;
    for (i = list.begin(); i != list.end(); i++) {
        if ((*i)->customerID == customerID) {
            return *i;
        }
    }
    return NULL;
}


void CustomerList::sort(int sortType) {
#if 1
    switch (sortType) {
    case CSORTBYNAME:
        list.sort(compareByName);
        break;
    case CSORTBYID:
        list.sort(compareByID);
        break;
    case CSORTBYCHECKIN:
        list.sort(compareByCheckIn);
        break;
    case CSORTBYCHECKOUT:
        list.sort(compareByCheckOut);
        break;
    case CSORTBYTYPE:
        list.sort(compareByType);
        break;
    case CSORTBYPOINT:
        list.sort(compareByPoint);
        break;
    default:
        break;
    }
#endif
}

bool CustomerList::compareByName(Customer *a, Customer *b) {
    return (a->userName <= b->userName);
}

bool CustomerList::compareByID(Customer *a, Customer *b) {
    return (a->customerID <= b->customerID);
}

bool CustomerList::compareByCheckIn(Customer* a, Customer* b) {
    return (a->checkInTime <= b->checkInTime);
}

bool CustomerList::compareByCheckOut(Customer* a, Customer* b) {
    return (a->checkOutTime <= b->checkOutTime);
}

bool CustomerList::compareByType(Customer* a, Customer* b) {
    return (a->customerType <= b->customerType);
}

bool CustomerList::compareByPoint(Customer *a, Customer *b) {
    return (a->point > b->point);
}

