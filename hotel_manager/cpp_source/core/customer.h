#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>

//enum the customer type
enum customer_type {
    ORDINARY, VIP, SVIP
};

enum customer_sort_type {
    CSORTBYNAME, CSORTBYID, CSORTBYTYPE,
    CSORTBYCHECKIN, CSORTBYCHECKOUT, CSORTBYPOINT
};


QString getCustomerTypeName(int customerType);




class Customer
{
public:
    int customerType;
    int customerID;
    QString userName;
    QString phone;
    QString checkInTime;
    QString checkOutTime;
    QString scheduleTime;
    QString vipNumber;
    int point;
    float deposit;
    QString roomNumber;

    /* construction function */
    Customer(int customerType, int customerID, QString userName, QString phone,
             QString checkInTime, QString checkOutTime, QString scheduleTime = "",
             QString roomNumber = "",
             QString vipNumber = "", int point = 0, float deposit = 0) :
        customerType(customerType), customerID(customerID), userName(userName),
        phone(phone),
        checkInTime(checkInTime), checkOutTime(checkOutTime), scheduleTime(scheduleTime),
        vipNumber(vipNumber), point(point), deposit(deposit), roomNumber(roomNumber) {}
};

typedef struct customer_list {
    Customer* customer;
    customer_list* next;
}*CustomerListStruct;

class CustomerList
{
public:

    int size;

    // to initialize a list, you must have a head
    CustomerList(Customer* customer);
    /* insert a item to tail */
    void insert(Customer *customer);
    /* get item */
    Customer* get(int index);
    Customer* get(bool fromHead = false);
    CustomerListStruct getHead();

    /* sort list */
    CustomerList* sort(int by = CSORTBYID, bool replace = true);


private:
    CustomerListStruct head, tail, getCurrent;

    /* merge sort function */
    CustomerListStruct mergeSort(CustomerListStruct first, int by = CSORTBYID);
    int customerCompare (Customer* a, Customer* b, int sortType);
    CustomerListStruct customerListMergeInPlace (CustomerListStruct left, CustomerListStruct right, int sortType);
    void customerListDivide (CustomerListStruct first, CustomerListStruct* left, CustomerListStruct* right);

};

#endif // CUSTOMER_H
