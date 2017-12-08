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

RoomList::RoomList(Room* room) {
    RoomListStruct head = (RoomListStruct) malloc(sizeof(struct room_list));
    head->next = NULL;
    head->room = room;
    this->head = head;
    this->tail = head;
    this->size = 1;
    this->getCurrent = head;
}

void RoomList::insert(Room* room) {
    RoomListStruct add = (RoomListStruct) malloc(sizeof(struct room_list));
    add->next = NULL;
    add->room = room;
    tail->next = add;
    tail = add;
    size++;
}

Room* RoomList::get(int index) {
    RoomListStruct current;
    int i;
    for (i = 0, current = head; current != NULL; current = current->next ) {
        if (i == index) {
            return current->room;
        }
    }
    return NULL;
}

Room* RoomList::get(bool fromHead) {
    if (fromHead) {
        getCurrent = head;
    }
    if (getCurrent == NULL) {
        return NULL;
    }
    RoomListStruct result = getCurrent;
    getCurrent = getCurrent->next;
    return result->room;
}




RoomList* RoomList::sort(int by, bool replace) {
    head = mergeSort(head, by);
    return this;
}

RoomListStruct RoomList::mergeSort(RoomListStruct first, int by) {
    RoomListStruct left, right;
    if (first == NULL || first->next == NULL) {
        head = first;
        return first;
    }
    roomListDivide(first, &left, &right);
    left = mergeSort(left, by);
    right = mergeSort(right, by);
    return roomListMergeInPlace(left, right, by);
}


void RoomList::roomListDivide(RoomListStruct first,
                                      RoomListStruct *left,
                                      RoomListStruct *right) {
    RoomListStruct slow = first, fast = first->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }
    *left = first;
    *right = slow->next;
    slow->next = NULL;
}


RoomListStruct RoomList::roomListMergeInPlace
(RoomListStruct left, RoomListStruct right, int sortType) {
    RoomListStruct tmp_head = (RoomListStruct) malloc(sizeof(struct room_list));
    RoomListStruct first = tmp_head;
    for (; left != NULL && right != NULL; first = first->next) {
        if (roomCompare(left->room, right->room, sortType)) {
            first->next = left;
            left = left->next;
        }
        else {
            first->next = right;
            right = right->next;
        }
    }
    first->next = left != NULL? left:right;
    first = tmp_head->next;
    free(tmp_head);
    return first;
}

RoomListStruct RoomList::getHead() {
    return head;
}


int RoomList::roomCompare(Room *a, Room *b, int sortType) {
    switch (sortType) {
    case RSORTID:
        if (a->roomNumber <= b->roomNumber) {
            return 1;
        }
        break;
    case RSORTTYPE:
        if (a->roomType > b->roomType) {
            return 1;
        }
        break;
    case RSORTPRICE:
        if (a->price <= b->price) {
            return 1;
        }
        break;
    case RSORTUSAGE:
        if (a->usage <= b->usage) {
            return 1;
        }
        break;
    case RSORTCLEAN:
        if (a->cleanSituation <= b->cleanSituation) {
            return 1;
        }
        break;
    }
    return 0;
}








