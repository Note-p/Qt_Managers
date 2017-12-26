#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <list>

using namespace std;



//enum the customer type
enum customer_type {
    ORDINARY, VIP, SVIP
};

enum customer_sort_type {
    CSORTBYNAME, CSORTBYID, CSORTBYTYPE,
    CSORTBYCHECKIN, CSORTBYCHECKOUT, CSORTBYPOINT
};


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

    /* get customer type name */
    virtual QString getCustomerTypeName();

    /* construction function */
    Customer(){}
};


class OrdinaryCustomer : public Customer {
public:
    OrdinaryCustomer(int customerType, int customerID, QString userName, QString phone,
                   QString checkInTime, QString checkOutTime, QString scheduleTime = "",
                   QString roomNumber = "");

    QString getCustomerTypeName();
};


class VIPCustomer : public Customer
{
public:
    VIPCustomer(int customerType, int customerID, QString userName, QString phone,
                   QString checkInTime, QString checkOutTime, QString scheduleTime = "",
                   QString roomNumber = "", QString vipNumber = "", int point = 0);
    QString getCustomerTypeName();
};


class SVIPCustomer : public Customer
{
public:

    SVIPCustomer(int customerType, int customerID, QString userName, QString phone,
                   QString checkInTime, QString checkOutTime, QString scheduleTime = "",
                   QString roomNumber = "",
                   QString vipNumber = "", int point = 0, float deposit = 0);
    QString getCustomerTypeName();
};

/* STL list */
typedef list<Customer*> CUSTOMERLIST;


class CustomerList {
public:
    CUSTOMERLIST list;
    CustomerList();
    /* add customer to list */
    void add(Customer* customer);
    /* get customer from list */
    Customer* get(int customerID);
    /* sort customer list */
    void sort(int sortType);
private:
    /* compare functions below */
    static bool compareByName(Customer* a, Customer* b);
    static bool compareByID(Customer *a, Customer *b);
    static bool compareByType(Customer *a, Customer *b);
    static bool compareByCheckIn(Customer *a, Customer *b);
    static bool compareByCheckOut(Customer *a, Customer *b);
    static bool compareByPoint(Customer *a, Customer *b);
};



#endif // CUSTOMER_H
