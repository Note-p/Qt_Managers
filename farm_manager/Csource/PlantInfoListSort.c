//
// Created by hunto on 2017/8/31 0031.
//

#include "PlantInfoListSort.h"
#include "MyStringUtil.h"
#include "VegInfo.h"

/*仅需内部调用因此在内部声明保证代码整洁性*/
void PlantInfoListDivide(plantInfo first, plantInfo *left, plantInfo *right);
plantInfo PlantinfoListMergeInPlace (plantInfo left, plantInfo right, int sortType);
int PlantInfoCompare (plantInfo a, plantInfo b, int sortType);


plantInfo PlantInfoListCopy(plantInfo info) {
    plantInfo current, copy = NULL, prev;
    plantInfo result = (plantInfo)malloc(sizeof(struct plant_info));
    *result = *info;
    prev = result;
    current = info->next;
    while (current != NULL) {
        copy = (plantInfo)malloc(sizeof(struct plant_info));
        *copy = *current;
        prev->next = copy;
        prev = copy;
        current = current->next;
    }
    copy->next = NULL;
    return  result;
}



plantInfo PlantInfoListMergeSort(plantInfo first, int sortType) {
    plantInfo left, right;
    if (first == NULL || first->next == NULL) {
        return first;
    }
    PlantInfoListDivide(first, &left, &right);
    left = PlantInfoListMergeSort(left, sortType);
    right = PlantInfoListMergeSort(right, sortType);
    return PlantinfoListMergeInPlace(left, right, sortType);
}

void PlantInfoListDivide(plantInfo first, plantInfo *left, plantInfo *right) {
    plantInfo slow = first, fast = first->next;
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

plantInfo PlantinfoListMergeInPlace (plantInfo left, plantInfo right, int sortType) {
    plantInfo tmp_head = (plantInfo)malloc(sizeof(struct plant_info));
    plantInfo first = tmp_head;
    for (; left != NULL && right != NULL; first = first->next) {
        if (PlantInfoCompare(left, right, sortType)) {
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
    plantInfo first;
    if (left->area <= right->area) {
        first = left;
        first->next = PlantinfoListMergeInPlaceByArea(left->next, right);
    }
    else {
        first = right;
        first->next = PlantinfoListMergeInPlaceByArea(left, right->next);
    }
    return first;
#endif
}

/*
 * @usage:  按照指定的排序条件判断两结构体位置先后
 * @param:  sortType:排序类型
 * @return: 0-- a在b后  1-- a在b前
 */
int PlantInfoCompare (plantInfo a, plantInfo b, int sortType) {
    switch (sortType) {
    case SORTAREA:
        if (a->area <= b->area) {
            return 1;
        }
        else return 0;
    case SORTAREAR:
        if (a->area <= b->area) {
            return 0;
        }
        else return 1;
    case SORTWEIGHT:
        if (a->weight <= b->weight) {
            return 1;
        }
        else return 0;
    case SORTWEIGHTR:
        if (a->weight <= b->weight) {
            return 0;
        }
        else return 1;
    case SORTYEAR:
        if (getIntFromString(a->year) <= getIntFromString(b->year)) {
            return 1;
        }
        else return 0;
    case SORTYEARR:
        if (getIntFromString(a->year) <= getIntFromString(b->year)) {
            return 0;
        }
        else return 1;
    case SORTTYPE:
        if (a->father->vegType <= b->father->vegType) {
            return 1;
        }
        else return 0;
    case SORTDEFAULT:
        if (a->id <= b->id) {
            return 1;
        }
        else return 0;
    }
    return 0;
}


























