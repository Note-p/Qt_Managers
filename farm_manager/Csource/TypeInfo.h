//
// Created by hunto on 2017/8/31 0031.
//

#ifndef CSOURCE_TYPEINFO_H
#define CSOURCE_TYPEINFO_H

#include "VegInfo.h"
#include "ListAll.h"
#include "PlantingInfo.h"

/*蔬菜种类数据路径__debug时用绝对路径*/
#if 0
#define TYPE_INFO_PATH "typeinfo.info"
#else
#define TYPE_INFO_PATH "C:\\Users\\hunto\\Documents\\CHomework\\database\\typeinfo.info"
#endif

/*互相嵌套调用结构体时声明*/
typedef struct veg_info *vegInfo;

/*
 * 蔬菜种类信息结构体
 * next -- 下一节点
 * vInfoList -- 子蔬菜基本信息链表
 * typeCode -- 种类编号
 * typeName -- 种类名称
 */
typedef struct type_info {
    struct type_info *next;
    vegInfo vInfoList;
    char typeCode;
    char typeName[10];
}*typeInfo;

/*
 * @usage: 从文件中读取蔬菜种类信息单向链表
 */
typeInfo loadTypeInfoFromFile (void);

/*
 * @usage：保存蔬菜种类信息链表至文件
 */
void saveTypeInfoToFile(typeInfo head);

/*
 * @usage：新增蔬菜种类信息链接至链表表尾
 */
void addTypeInfoItem (typeInfo head ,char *addItemName);

/*
 * @usage: 删除蔬菜种类信息
 * @param: typeCode -- 要删除的种类编号
 * @return: 0--删除失败  1--删除成功
 */
int deleteTypeInfo (typeInfo head, char typeCode);

/*
 * @usage；修改蔬菜种类信息
 */
int editTypeInfo(typeInfo head, char typeCode, char *typeName);
#endif //CSOURCE_TYPEINFO_H
