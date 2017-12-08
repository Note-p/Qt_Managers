//
// Created by hunto on 2017/8/31 0031.
//

#include "ListAll.h"

typeInfo loadFarmListFromFile(void) {
    typeInfo result;
    /*读取蔬菜种类信息*/
    result = loadTypeInfoFromFile();
    typeInfo current = result;
    /*读取蔬菜基本信息*/
    FILE * vegInfoFile = fopen(VEG_INFO_PATH, "r");
    while (1) {
        vegInfo vInfo = getItemFromFile(vegInfoFile);
        if (vInfo == NULL) {
            fclose(vegInfoFile);
            break;
        }
        for (current = result; current != NULL; current = current->next) {
            if (current->typeCode == vInfo->vegType) {
                vInfo->father = current;
                //add to this type
                vegInfo currentVInfoList = current->vInfoList;
                if (currentVInfoList == NULL) {
                    current->vInfoList = vInfo;
                    break;
                }
                while (currentVInfoList->next != NULL) {
                    currentVInfoList = currentVInfoList->next;
                }
                currentVInfoList->next = vInfo;
            }
        }
    }
    /*读取蔬菜种植信息*/
    current = result;
    FILE * plantInfoFile = fopen(PLANT_INFO_PATH, "r");
    while (1) {
        plantInfo pInfo = getPlantItemFromFile(plantInfoFile);
        int isFind = 0; //用于跳出外层循环
        if (pInfo == NULL) {
            fclose(plantInfoFile);
            break;
        }
        for (current = result; current != NULL && isFind == 0; current = current->next) {
             vegInfo currentVInfoList = current->vInfoList;
            for (; currentVInfoList!= NULL; currentVInfoList = currentVInfoList->next) {
                if (currentVInfoList->vegCode == pInfo->vegCode) {
                    isFind = 1;
                    pInfo->father = currentVInfoList;
                    plantInfo currentPInfo = currentVInfoList->pInfoList;
                    if (currentPInfo == NULL) {
                        currentVInfoList->pInfoList = pInfo;
                        break;
                    }
                    while (currentPInfo->next != NULL) {
                        currentPInfo = currentPInfo->next;
                    }
                    currentPInfo->next = pInfo;
                }
            }
        }
    }
    return result;
}


plantInfo getPlantInfoListFromFarmList (typeInfo farmList) {
    /*过程简单不写了，就是从头遍历把种植信息都复制一遍并接起来*/
    typeInfo tInfo = farmList;
    int isFirst = 1;
    plantInfo result;
    result = (plantInfo)malloc(sizeof(struct plant_info));
    plantInfo current = result;
    for (; tInfo != NULL; tInfo = tInfo->next) {
        vegInfo vInfoList = tInfo->vInfoList;
        for (; vInfoList != NULL; vInfoList = vInfoList->next) {
            plantInfo pInfo = vInfoList->pInfoList;
            for (; pInfo != NULL; pInfo = pInfo->next) {
                if (isFirst) {
                    isFirst = 0;
                    *result = *pInfo;
                }
                else {
                    current->next = (plantInfo)malloc(sizeof(struct plant_info));
                    current->next->prev = current;
                    current = current->next;
                    *current = *pInfo;
                }
            }
        }
    }
    current->next = NULL;
    return result;
}


vegInfo getVegInfoFromFarmList (typeInfo farmList) {
    /*过程简单不写了，就是从头遍历把基本信息都复制一遍并接起来*/
    typeInfo tInfo = farmList;
    int isfirst = 1;
    vegInfo result = (vegInfo)malloc(sizeof(struct veg_info));
    vegInfo current = result;
    for (; tInfo != NULL; tInfo = tInfo->next) {
        vegInfo vInfoList = tInfo->vInfoList;
        for (; vInfoList != NULL; vInfoList = vInfoList->next) {
            if (isfirst) {
                isfirst = 0;
                *result = *vInfoList;
            }
            else {
                current->next = (vegInfo)malloc(sizeof(struct veg_info));
                current->next->prev = current;
                current = current->next;
                *current = *vInfoList;
            }
        }
    }
    current->next = NULL;
    return result;
}

