//
// Created by 黄涛 on 2017/7/17.
//

#ifndef CHOMEWORK_MYSTRINGUTIL_H
#define CHOMEWORK_MYSTRINGUTIL_H

#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
 * @param:  字符串
 * @usage:  字符串转int
 * @return: int
 */
int  getIntFromString (char * head);

/*
 * @param:  int
 * @usage:  int转字符串
 * @return: 字符串
 */
char * getStringFromInt (int num);

/*
 * @param:  字符串
 * @usage:  字符串转float
 * @return: float
 */
float getFloatFromString (char *head);

/*
 * @param:  float
 * @usage:  float转字符串
 * @return: 字符串
 */
char * getStringFromFloat (float num);

/*
 * @params: str:检测包含性的字符串   inthis:大的字符串
 * @usage:  检测一个字符串是否包含在另一字符串中
 * @return: 包含--1  不包含--0
 */
int strinstr(char *str, char *inthis);

#endif //CHOMEWORK_MYSTRINGUTIL_H
