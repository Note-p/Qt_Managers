//
// Created by 黄涛 on 2017/7/17.
//

#ifndef CHOMEWORK_VEGINFO_H
#define CHOMEWORK_VEGINFO_H

#include "sys.h"
#include "stdio.h"
#include "stdlib.h"
#include "MyStringUtil.h"
#include "string.h"
#include "VegTypeEnum.h"
#include "PlantingInfo.h"
#include "ListAll.h"


/*veginfo数据路径__debug时用绝对路径*/
#if 0
#define VEG_INFO_PATH "veginfo.info"
#else
#define VEG_INFO_PATH "C:\\Users\\hunto\\Documents\\CHomework\\database\\veginfo.info"
#endif


/*
 * 蔬菜信息结构体
 * @vegCode:蔬菜编号  @vegName:蔬菜名称  @vegType:蔬菜种类  @nutritionFacts:营养成分
 */
typedef struct veg_info {
    struct type_info *father;
    plantInfo pInfoList;
    int vegCode;
    char vegName[20];
    char vegType;
    char nutritionFacts[200];
    struct veg_info *prev, *next;
}*vegInfo;

/*
 * 蔬菜信息链表的结构体__用于从文件读取链表返回
 * @head:链表表头  @tail:链表尾部  @itemNum:链表长度
 */
typedef struct veg_struct_info {
    vegInfo head;
    vegInfo tail;
    int itemNum;
}*vegStructInfo;

/*
 * 搜索结果结构体
 * @vegCode:蔬菜编号 @resultNum:符合条件的结果数
 */
typedef struct search_result {
    int resultNum;
    int *vegCodeArray;
}*searchResult;



/*
 * @usage:  通过蔬菜编号获取蔬菜信息结构体
 * @param:  head:链表表头  vegCode:查找的蔬菜编号
 * @return: 蔬菜信息结构体
 */
vegInfo getVegInfoByCode(vegInfo head, int vegCode);

/*
 * @usage:  通过蔬菜名称获取蔬菜信息结构体
 * @param:  head:链表表头  vegCode:查找的蔬菜名称
 * @return: 蔬菜信息结构体
 */
vegInfo getVegInfoByName(vegInfo head, char *vegName);

/*
 * @usage:  从文件中读取蔬菜信息存储为链表
 * @return: 链表信息结构体
 */
vegStructInfo loadVegInfoFromFile(void);

/*
 * @usage:将蔬菜信息链表存储到文件中
 */
void saveVegInfoToFile(vegInfo head);

/*
 * @usage:  从文件指针处开始读取一项蔬菜信息__用于loadVegInfoFromFile中
 * @param:  文件指针
 * @return: 种植信息结构体
 */
vegInfo getItemFromFile(FILE * vegInfoFile);

/*
 * @usage:  添加一项蔬菜信息至链表尾部
 * @params: tail:链表表尾  addItem:要添加的蔬菜信息结构体
 */
void addVegInfoItem(vegInfo tail,vegInfo addItem);



/*
 * @usage:  新建一个蔬菜信息结构体__用于与Qt界面交互
 * @return: 新建的蔬菜信息结构体
 */
vegInfo createVegInfoItem(int vegCode, char * vegName, char * vegType, char * nutritionFacts);

/*
 * @usage:  释放链表内存
 * @param:  链表表头
 */
void freeVegInfo(vegInfo head);

/*
 * @usage： 搜索菜名包含关键字的蔬菜信息
 */
searchResult searchVegName(vegInfo veginfo, char *searchData);

/*
 * @usage： 搜索营养成分包含关键字的蔬菜信息
 */
searchResult searchVegFacts(vegInfo veginfo, char *searchData);

/*删除单项蔬菜基本信息*/
void removeVegInfoItem(vegInfo removeItem);
/*删除多项蔬菜基本信息*/
void removeVegInfoItems(vegInfo removeItem);
/*删除多项后要重新编号*/
void renameVegInfoID(vegInfo head);


#endif //CHOMEWORK_VEGINFO_H
