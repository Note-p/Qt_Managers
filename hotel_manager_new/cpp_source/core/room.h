#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <list>

using namespace std;

//enum the room type
enum room_type {
    STANDARDROOM, BUSINESSSUIT, HOURLYRATEROOM, SPECIALDISCOUNTROOM
};

enum sort_type {
    RSORTID, RSORTTYPE, RSORTPRICE, RSORTUSAGE, RSORTCLEAN
};

QString getRoomTypeName(int roomType);


/* these functions are very familiar with customer.h functions ,
 * see customer.h for more info*/

class Room
{
public:
    int roomType;
    int roomNumber;
    float price;
    int usage;
    QString cleanSituation;
    QString addiction;
    Room() {}
    virtual QString getRoomTypeName();
};


class StandardRoom : public Room {
public:
    StandardRoom(int roomType, int roomNumber, float price, int usage,
                 QString cleanSituation, QString addiction = "");
    QString getRoomTypeName();
};


class BusinessRoom : public Room {
public:
    BusinessRoom(int roomType, int roomNumber, float price, int usage,
                 QString cleanSituation, QString addiction = "");
    QString getRoomTypeName();
};


class HourlyRateRoom : public Room {
public:
    HourlyRateRoom(int roomType, int roomNumber, float price, int usage,
                 QString cleanSituation, QString addiction = "");
    QString getRoomTypeName();
};


class SpecialDiscountRoom : public Room {
public:
    SpecialDiscountRoom(int roomType, int roomNumber, float price, int usage,
                 QString cleanSituation, QString addiction = "");
    QString getRoomTypeName();
};





typedef list<Room*> ROOMLIST;


class RoomList
{
public:

    ROOMLIST roomList;
    RoomList() {}
    void add(Room* room);
//    Room* get(int roomID);
    void sort(int sortType = RSORTID);


private:
    static bool compareByID(Room* a, Room* b);
    static bool compareByType(Room* a, Room* b);
    static bool compareByPrice(Room* a, Room* b);
    static bool compareByUsage(Room* a, Room* b);
    static bool compareByClean(Room* a, Room* b);
};

#endif // ROOM_H
