//
// Created by hunto on 2017/8/31 0031.
//

#include "VegInfoListSort.h"
#include "VegInfo.h"




void VegInfoListDivide(vegInfo first, vegInfo *left, vegInfo *right);
vegInfo VegInfoListMergeInPlace (vegInfo left, vegInfo right, int sortType);
int VegInfoCompare (vegInfo a, vegInfo b, int sortType);


vegInfo VegInfoListCopy(vegInfo info) {
    vegInfo current, copy = NULL, prev;
    vegInfo result = (vegInfo)malloc(sizeof(struct veg_info));
    *result = *info;
    prev = result;
    current = info->next;
    while (current != NULL) {
        copy = (vegInfo)malloc(sizeof(struct veg_info));
        *copy = *current;
        prev->next = copy;
        prev = copy;
        current = current->next;
    }
    copy->next = NULL;
    return  result;
}



vegInfo VegInfoListMergeSort(vegInfo first, int sortType) {
    vegInfo left, right;
    if (first == NULL || first->next == NULL) {
        return first;
    }
    VegInfoListDivide(first, &left, &right);
    left = VegInfoListMergeSort(left, sortType);
    right = VegInfoListMergeSort(right, sortType);
    return VegInfoListMergeInPlace(left, right, sortType);
}

void VegInfoListDivide(vegInfo first, vegInfo *left, vegInfo *right) {
    vegInfo slow = first, fast = first->next;
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

vegInfo VegInfoListMergeInPlace (vegInfo left, vegInfo right, int sortType) {
    vegInfo tmp_head = (vegInfo)malloc(sizeof(struct veg_info));
    vegInfo first = tmp_head;
    for (; left != NULL && right != NULL; first = first->next) {
        if (VegInfoCompare(left, right, sortType)) {
            first->next = left;
            left = left->next;
        }
        else {
            first->next = right;
            right = right->next;
        }
    }
    first->next = left != NULL ? left : right;
    first = tmp_head->next;
    free(tmp_head);
    return first;
#if 0
    /*方法2*/
    if (left == NULL) {
        return right;
    }
    if (right == NULL) {
        return left;
    }
    vegInfo first;
    if (left->area <= right->area) {
        first = left;
        first->next = vegInfoListMergeInPlaceByArea(left->next, right);
    }
    else {
        first = right;
        first->next = vegInfoListMergeInPlaceByArea(left, right->next);
    }
    return first;
#endif
}

int VegInfoCompare (vegInfo a, vegInfo b, int sortType) {
    switch (sortType) {
        case VEGSORTDEFAULT:
            if (a->vegCode <= b->vegCode) {
                return 1;
            }
            else return 0;
        case VEGSORTTYPE:
            if (a->vegType <= b->vegType) {
                return 1;
            }
            else return 0;
        case VEGSORTFACTSLENTH:
            if (strlen(a->nutritionFacts) <= strlen(b->nutritionFacts)) {
                return 0;
            }
            else return 1;
    }
    return 0;
}


