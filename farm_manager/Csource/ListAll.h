//
// Created by hunto on 2017/8/31 0031.
//

#ifndef CSOURCE_LISTALL_H
#define CSOURCE_LISTALL_H

#include "VegInfo.h"
#include "PlantingInfo.h"
#include "TypeInfo.h"


/*结构体互相嵌套调用*/
typedef struct type_info *typeInfo;
typedef struct plant_info *plantInfo;
typedef struct veg_info *vegInfo;

/*
 * @usage:  从文件中读取数据并建立十字交叉链表
 * @return: 建立好的十字交叉链表表头
 */
typeInfo loadFarmListFromFile(void);

/*
 * @usage:  从十字交叉链表中构建种植信息单向链表
 * @return: 建立好的种植信息链表表头
 */
plantInfo getPlantInfoListFromFarmList (typeInfo farmList);

/*
 * @usage:  从十字交叉链表中构建基本信息单向链表
 * @return: 建立好的基本信息链表表头
 */
vegInfo getVegInfoFromFarmList (typeInfo farmList);

#endif //CSOURCE_LISTALL_H
