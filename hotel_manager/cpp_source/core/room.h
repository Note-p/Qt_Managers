#ifndef ROOM_H
#define ROOM_H

#include <QString>

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
    Room(int roomType, int roomNumber, float price, int usage,
         QString cleanSituation, QString addiction = "") :
        roomType(roomType), roomNumber(roomNumber), price(price), usage(usage),
        cleanSituation(cleanSituation), addiction(addiction) {}
};

typedef struct room_list {
    Room* room;
    room_list* next;
}*RoomListStruct;

class RoomList
{
public:

    int size;

    // to initialize a list, you must have a head
    RoomList(Room* room);
    void insert(Room *room);

    Room* get(int index);
    Room* get(bool fromHead = false);
    RoomListStruct getHead();
    RoomList* sort(int by = RSORTID, bool replace = true);


private:
    RoomListStruct head, tail, getCurrent;

    int roomCompare (Room* a, Room* b, int sortType);
    RoomListStruct roomListMergeInPlace (RoomListStruct left, RoomListStruct right, int sortType);
    void roomListDivide (RoomListStruct first, RoomListStruct* left, RoomListStruct* right);
    RoomListStruct mergeSort(RoomListStruct first, int by = RSORTID);

};

#endif // ROOM_H
