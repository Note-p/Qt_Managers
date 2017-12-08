//
// Created by 黄涛 on 2017/7/17.
//

#ifndef CHOMEWORK_VEGTYPEENUM_H
#define CHOMEWORK_VEGTYPEENUM_H

#include <string.h>
#include "sys.h"

/*
 * @usage: 通过蔬菜种类名获取蔬菜种类编号
 * @param: 蔬菜种类名称
 * @return:蔬菜种类编号
 */
int getTypeCodeByName (char * typeName);

/*
 * @usage: 通过蔬菜种类编号获取蔬菜种类名称
 * @param: 蔬菜种类编号
 * @return:蔬菜名称
 */
char * getTypeNameByCode (int typeCode);

#endif //CHOMEWORK_VEGTYPEENUM_H
