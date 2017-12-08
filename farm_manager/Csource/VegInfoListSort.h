//
// Created by hunto on 2017/8/31 0031.
//

#ifndef CSOURCE_VEGINFOLISTSORT_H
#define CSOURCE_VEGINFOLISTSORT_H

#include "VegInfo.h"

/*
 * 蔬菜基本信息的归并排序
 * 基本等同蔬菜种植信息的归并排序
 * 本处不再赘述
 */

enum veg_sort_type {
    VEGSORTTYPE, VEGSORTDEFAULT, VEGSORTFACTSLENTH
};

vegInfo VegInfoListCopy(vegInfo info);
vegInfo VegInfoListMergeSort(vegInfo first, int sortType);


#endif //CSOURCE_VEGINFOLISTSORT_H
