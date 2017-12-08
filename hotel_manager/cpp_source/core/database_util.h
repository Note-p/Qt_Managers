#ifndef DATABASE_UTIL_H
#define DATABASE_UTIL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "room.h"
#include "customer.h"

#define DATABASE_USERNAME "test"
#define DATABASE_PASSWORD "test"
#define ROOM_DATABASE_NAME "room_sql"
#define CUSTOMER_DATABASE_NAME "customer_sql"
#define ROOM_DATABASE_FILE "RoomDatabase.db"
#define CUSTOMER_DATABASE_FILE "CustomerDatabase.db"



class DatabaseUtil
{
public:
    DatabaseUtil();
    QSqlDatabase roomDatabase;
    QSqlDatabase customerDatabase;

    /* insert a room data to database */
    bool insertRoomData (int roomType, float price, int usage = 0, QString clean = "",
                         QString discountTime = "", int roomID = -1);
    bool insertRoomData(Room* room);

    /* get max room id in database */
    int getMaxRoomID ();

    /* delete a room in database */
    void deleteRoomData (int roomId);

    /* get room data from database */
    Room* getRoomData (int roomId);

    /* get room datas & build list */
    RoomList* getRoomDataList();

    /* update room data in database */
    void updateRoomData (int roomID, int roomType = -1, float price = -1,
                         int usage = -1, QString clean = "null", QString addiction = "null");

    /* insert customer data to database */
    bool insertCustomerData (int customerType, QString userName, QString phone,
                             QString checkInTime, QString checkOutTime,
                             QString scheduleTime = "", QString vipNumber = "",
                             int point = 0, float deposit = 0, int customerID = -1,
                             QString roomNumber = NULL);
    bool insertCustomerData (Customer* customer);

    /* these functions below are the same as the room functions above */
    int getMaxCustomerID ();
    void deleteCustomerData (int customerId);
    Customer* getCustomerData (int customerId);
    Customer* getCustomerDataByVIP (int vipNumber);
    Customer* getCustomerDataByRoom(int roomID);
    CustomerList* getCustomerDataList();
    void updateCustomerData (int customerID, int customerType = -1, QString userName = NULL,
                             QString phone = NULL, QString checkInTime = NULL,
                             QString checkOutTime = NULL, QString scheduleTime = NULL,
                             QString vipNumber = NULL, int point = -1, float deposit = -1,
                             QString roomNumber = NULL);
};

#endif // DATABASE_UTIL_H
