//
// Created by 黄涛 on 2017/7/17.
//
#include "VegTypeEnum.h"

/*
 * enum table:
 * RHIZOMES , FRUITVEG , MELONVEG , LEAFVEG , FUNGUS
 * 根茎类、    果菜类、    瓜类、      叶菜类、   菌类
 */
enum vegetable_type {
    RHIZOMES = 1, FRUITVEG , MELONVEG , LEAFVEG , FUNGUS
};

int getTypeCodeByName (char * typeName) {
    if (strcmp(typeName, "根茎类") == 0) {
        return RHIZOMES;
    }
    else if (strcmp(typeName, "果菜类") == 0) {
        return FRUITVEG;
    }
    else if (strcmp(typeName, "瓜类") == 0) {
        return MELONVEG;
    }
    else if (strcmp(typeName, "叶菜类") == 0) {
        return LEAFVEG;
    }
    else if (strcmp(typeName, "菌类") == 0) {
        return FUNGUS;
    }
    else {
        return ERRORCODE;
    }
}

char * getTypeNameByCode (int typeCode) {
    switch (typeCode) {
    case RHIZOMES:
        return "根茎类";
    case FRUITVEG:
        return "果菜类";
    case MELONVEG:
        return "瓜类";
    case LEAFVEG:
        return "叶菜类";
    case FUNGUS:
        return "菌类";
    default:
        return NULL;
    }
}


