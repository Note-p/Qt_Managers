//
// Created by 黄涛 on 2017/7/17.
//

#ifndef CHOMEWORK_PLANTINGINFO_H
#define CHOMEWORK_PLANTINGINFO_H

#include "sys.h"
#include "stdio.h"
#include "stdlib.h"
#include "MyStringUtil.h"
#include "string.h"
#include "VegInfo.h"
#include "ListAll.h"

/*plantinfo数据路径__debug时用绝对路径*/
#if 0
#define PLANT_INFO_PATH "plantinfo.info"
#else
#define PLANT_INFO_PATH "C:\\Users\\hunto\\Documents\\CHomework\\database\\plantinfo.info"
#endif

/*
 * 种植信息结构体
 * @id: 种植编号  @vegCode: 蔬菜编号  @area:面积  @weight:收成  @year:年份
 */
typedef struct veg_info *vegInfo;

typedef struct plant_info {
    struct plant_info *prev, *next;
    vegInfo father;
    int id;
    int vegCode;
    int area;
    float weight;
    char year[5];
}*plantInfo;

/*
 * 存储种植信息链表的结构体
 * @head:链表表头  @tail:链表尾部  @num:链表成员数量
 */
typedef struct plant_struct_info {
    plantInfo head, tail;
    int num;
}*plantStructInfo;



/*
 * @usage:  从文件中读取种植信息存储至链表中
 * @return: 链表信息
 */
plantStructInfo loadPlantInfoFromFile(void);

/*
 * @usage: 将种植信息链表保存到文件
 * @param: 链表表头
 */
void savePlantInfoToFile(plantInfo head);

/*
 * @usage:  从文件指针处开始读取一项种植信息__用于loadPlantInfoFromFile中
 * @param:  文件指针
 * @return: 种植信息结构体
 */
plantInfo getPlantItemFromFile(FILE * plantInfoFile);

/*
 * @usage:  增加一项种植信息到链表尾部
 * @params: tail:链表尾部  additem:要增加的种植信息结构体
 */
void addPlantInfoItem(plantInfo tail,plantInfo addItem);

/*
 * @usage: 从链表移除一项种植信息
 * @param: 要移除的种植信息结构体
 */
void removePlantInfoItem(plantInfo removeItem);

/*
 * @usage: 从链表移除一项种植信息__用于需要同时删除多项的情况--不会重排编号
 * @param: 要移除的种植信息结构体
 */
void removePlantInfoItems(plantInfo removeItem);

/*
 * @usage: 种植信息重新编号--表头为1从小到大编号
 * @param: 种植信息链表表头
 */
void renamePlantInfoID(plantInfo head);

/*
 * @usage:  通过种植编号获取种植信息结构体
 * @params: head:种植信息链表表头  id:要获取的编号
 * @return: 获取的种植信息结构体  NULL为未找到
 */
plantInfo getPlantInfoByID(plantInfo head, int id);

/*
 * @usage:  通过蔬菜编号获取种植信息结构体
 * @params: head:种植信息链表表头  vegCode:要获取的蔬菜编号
 * @return: 获取的种植信息结构体  NULL为未找到
 */
plantInfo getPlantInfoByVegCode(plantInfo head, int vegCode);

/*
 * @usage:  创建种植信息结构体__用于与C++的UI交互
 * @params: 同结构体成员变量
 * @return: 创建的种植信息结构体  NULL为未创建
 */
plantInfo createPlantInfoItem(int id, char * vegCode, char * area, char * weight, char * year);

/*
 * @usage: 释放链表
 * @param: 链表表头
 */
void freePlantInfo(plantInfo head);

/*
 * @usage:  统计种植面积总和
 * @param:  链表表头
 * @return: 面积总和
 */
int getPlantAreaAll(plantInfo head);

/*
 * @usage:  统计一年的种植面积总和
 * @params: head:链表表头  year:要统计的年份
 * @return: 该年面积总和
 */
int getPlantAreaYear(plantInfo head, int year);

/*
 * @usage:  统计一年的种植面积总和
 * @params: head:链表表头  vegHead:蔬菜种类信息的链表表头  vegType:蔬菜种类
 * @return: 该种类面积总和
 */
int getPlantAreaVegType(plantInfo head, vegInfo vegHead, int VegType);

/*
 * @usage:  统计收成总和
 * @param:  链表表头
 * @return: 收成总和
 */
float getPlantWeightAll(plantInfo head);

/*
 * @usage:  统计一年的收成总和
 * @params: head:链表表头  year:要统计的年份
 * @return: 该年收成总和
 */
float getPlantWeightYear(plantInfo head, int year);

/*
 * @usage:  统计一年的收成总和
 * @params: head:链表表头  vegHead:蔬菜种类信息的链表表头  vegType:蔬菜种类
 * @return: 该种类收成总和
 */
float getPlantWeightVegType(plantInfo head, vegInfo vegHead, int VegType);

#endif //CHOMEWORK_PLANTINGINFO_H
