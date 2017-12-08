#include "customer.h"
#include "QDateTime"

QString getCustomerTypeName(int customerType) {
    switch (customerType) {
    case ORDINARY:
        return "ordinary";
    case VIP:
        return "VIP";
    case SVIP:
        return "SVIP";
    default:
        return "";
    }
}

CustomerList::CustomerList(Customer* customer) {
    CustomerListStruct head = (CustomerListStruct) malloc(sizeof(struct customer_list));
    head->next = NULL;
    head->customer = customer;
    this->head = head;
    this->tail = head;
    this->size = 1;
    this->getCurrent = head;
}

void CustomerList::insert(Customer* customer) {
    CustomerListStruct add = (CustomerListStruct) malloc(sizeof(struct customer_list));
    add->next = NULL;
    add->customer = customer;
    tail->next = add;
    tail = add;
    size++;
}

Customer* CustomerList::get(int index) {
    CustomerListStruct current;
    int i;
    for (i = 0, current = head; current != NULL; current = current->next ) {
        if (i == index) {
            return current->customer;
        }
    }
    return NULL;
}

Customer* CustomerList::get(bool fromHead) {
    if (fromHead) {
        getCurrent = head;
    }
    if (getCurrent == NULL) {
        return NULL;
    }
    CustomerListStruct result = getCurrent;
    getCurrent = getCurrent->next;
    return result->customer;
}

CustomerListStruct CustomerList::getHead() {
    return head;
}

CustomerList* CustomerList::sort(int by, bool replace) {
    head = mergeSort(head, by);
    return this;
}

CustomerListStruct CustomerList::mergeSort(CustomerListStruct first, int by) {
    CustomerListStruct left, right;
    if (first == NULL || first->next == NULL) {
        head = first;
        return first;
    }
    customerListDivide(first, &left, &right);
    left = mergeSort(left, by);
    right = mergeSort(right, by);
    return customerListMergeInPlace(left, right, by);
}


void CustomerList::customerListDivide(CustomerListStruct first,
                                      CustomerListStruct *left,
                                      CustomerListStruct *right) {
    CustomerListStruct slow = first, fast = first->next;
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


CustomerListStruct CustomerList::customerListMergeInPlace
(CustomerListStruct left, CustomerListStruct right, int sortType) {
    CustomerListStruct tmp_head = (CustomerListStruct) malloc(sizeof(struct customer_list));
    CustomerListStruct first = tmp_head;
    for (; left != NULL && right != NULL; first = first->next) {
        if (customerCompare(left->customer, right->customer, sortType)) {
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




int CustomerList::customerCompare(Customer *a, Customer *b, int sortType) {
    switch (sortType) {
    case CSORTBYID:
        if (a->customerID <= b->customerID) {
            return 1;
        }
        break;
    case CSORTBYNAME:
        if (a->userName <= b->userName) {
            return 1;
        }
        break;
    case CSORTBYTYPE:
        if (a->customerType > b->customerType) {
            return 1;
        }
        break;
    case CSORTBYPOINT:
        if (a->point > b->point) {
            return 1;
        }
        break;
    case CSORTBYCHECKIN:
        if (QDateTime::fromString(a->checkInTime) <= QDateTime::fromString(b->checkInTime)) {
            return 1;
        }
        break;
    case CSORTBYCHECKOUT:
        if (QDateTime::fromString(a->checkOutTime) <= QDateTime::fromString(b->checkOutTime)) {
            return 1;
        }
        break;
    }
    return 0;
}



