//
// Created by hunto on 2017/8/31 0031.
//

#ifndef CSOURCE_LISTSORT_H
#define CSOURCE_LISTSORT_H

#include "Csource/PlantingInfo.h"

/*
 * @usage:  将蔬菜种植信息链表按条件归并排序
 * @params: first--蔬菜种植信息链表表头   sortType--排序类型
 * @return: 排序后的蔬菜种植信息链表表头
 */
plantInfo PlantInfoListMergeSort (plantInfo first, int sortType);

/*
 * @usage:  将蔬菜种植信息链表复制一份
 * @param:  蔬菜种植信息链表表头
 * @return: 复制后的蔬菜种植信息链表表头
 */
plantInfo PlantInfoListCopy(plantInfo info);

/* 排序种类的枚举，从前至后分别为，按面积升降序排列、
 * 按重量升降序排列、按年份升降序排列、按类型排列、默认排序*/
enum sort_type {
    SORTAREA, SORTAREAR, SORTWEIGHT, SORTWEIGHTR,
    SORTYEAR, SORTYEARR, SORTTYPE, SORTDEFAULT
};

#endif //CSOURCE_LISTSORT_H
