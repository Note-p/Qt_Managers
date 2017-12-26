#include "room.h"


QString getRoomTypeName(int roomType) {
    switch (roomType) {
    case STANDARDROOM:
        return "standard room";
    case BUSINESSSUIT:
        return "business suit";
    case HOURLYRATEROOM:
        return "hourly rate room";
    case SPECIALDISCOUNTROOM:
        return "special discount room";
    default:
        return "";
    }
}


StandardRoom::StandardRoom(int roomType, int roomNumber, float price,
                                         int usage, QString cleanSituation, QString addiction) {
    this->roomType = roomType;
    this->roomNumber = roomNumber;
    this->price = price;
    this->usage = usage;
    this->cleanSituation = cleanSituation;
    this->addiction = addiction;
}

HourlyRateRoom::HourlyRateRoom(int roomType, int roomNumber, float price,
                                         int usage, QString cleanSituation, QString addiction) {
    this->roomType = roomType;
    this->roomNumber = roomNumber;
    this->price = price;
    this->usage = usage;
    this->cleanSituation = cleanSituation;
    this->addiction = addiction;
}

BusinessRoom::BusinessRoom(int roomType, int roomNumber, float price,
                                         int usage, QString cleanSituation, QString addiction) {
    this->roomType = roomType;
    this->roomNumber = roomNumber;
    this->price = price;
    this->usage = usage;
    this->cleanSituation = cleanSituation;
    this->addiction = addiction;
}


SpecialDiscountRoom::SpecialDiscountRoom(int roomType, int roomNumber, float price,
                                         int usage, QString cleanSituation, QString addiction) {
    this->roomType = roomType;
    this->roomNumber = roomNumber;
    this->price = price;
    this->usage = usage;
    this->cleanSituation = cleanSituation;
    this->addiction = addiction;
}


QString StandardRoom::getRoomTypeName() {
    return QString("standard room");
}

QString BusinessRoom::getRoomTypeName() {
    return QString("business room");
}


QString SpecialDiscountRoom::getRoomTypeName() {
    return QString("special discount room");
}


QString HourlyRateRoom::getRoomTypeName() {
    return QString("hourly rate room");
}


void RoomList::add(Room *room) {
    roomList.push_back(room);
}


void RoomList::sort(int sortType) {
    switch (sortType) {
    case RSORTID:
        roomList.sort(compareByID);
        break;
    case RSORTTYPE:
        roomList.sort(compareByType);
        break;
    case RSORTPRICE:
        roomList.sort(compareByPrice);
        break;
    case RSORTUSAGE:
        roomList.sort(compareByUsage);
        break;
    case RSORTCLEAN:
        roomList.sort(compareByClean);
        break;
    default:
        break;
    }
}


bool RoomList::compareByID(Room *a, Room *b) {
    return a->roomNumber <= b->roomNumber;
}


bool RoomList::compareByPrice(Room *a, Room *b) {
    return a->price <= b->price;
}


bool RoomList::compareByType(Room *a, Room *b) {
    return a->roomType <= b->roomType;
}


bool RoomList::compareByClean(Room *a, Room *b) {
    return a->cleanSituation <= b->cleanSituation;
}


bool RoomList::compareByUsage(Room *a, Room *b) {
    return a->usage <= b->usage;
}










