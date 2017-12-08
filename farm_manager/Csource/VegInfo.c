//
// Created by 黄涛 on 2017/7/17.
//
/*
 * usage : 蔬菜信息链表
 */

#include "VegInfo.h"

/*
 * @params : 链表表头，查找的蔬菜ID
 * @return : 蔬菜ID对应的蔬菜信息结构体
 */
vegInfo getVegInfoByCode(vegInfo head, int vegCode) {
    vegInfo result = head;
    while (1) {
        if (result->vegCode == vegCode){
            return result;
        }
        result = result->next;
        if (result == NULL) {
            printf("未找到该蔬菜ID: %d", vegCode);
            return NULL;
        }
    }
}


/*
 * @params : 链表表头，查找的蔬菜名
 * @return : 蔬菜名对应的蔬菜信息结构体
 */
vegInfo getVegInfoByName(vegInfo head, char *vegName) {
    vegInfo result = head;
    while (1) {
        if (strcmp(result->vegName, vegName)==0){
            return result;
        }
        result = result->next;
        if (result == NULL) {
            printf("未找到该蔬菜: %s", vegName);
            return NULL;
        }
    }
}

/*
 *  @return : 蔬菜信息链表的头尾及长度
 */
vegStructInfo loadVegInfoFromFile(void) {
    FILE * vegInfoFile = fopen(VEG_INFO_PATH, "r");
    vegStructInfo result = (vegStructInfo) malloc(sizeof(struct veg_struct_info));
    vegInfo head = getItemFromFile(vegInfoFile);
    head->prev = NULL;
    vegInfo current = head;
    while (1) {
        vegInfo info = getItemFromFile(vegInfoFile);
        if (info == NULL){
            current->next=NULL;
            result->head = head;
            result->tail = current;
            result->itemNum = current->vegCode;
            fclose(vegInfoFile);
            return result;
        }
        current->next = info;
        info->prev = current;
        current = info;

    }
}

void saveVegInfoToFile(vegInfo head) {
    vegInfo current = head;
    FILE * vegInfoFile = fopen(VEG_INFO_PATH, "w");
    while (1) {
        /*蔬菜ID*/
        fputs("{\'", vegInfoFile);
        fputs(getStringFromInt(current->vegCode), vegInfoFile);
        fputs("\',\'", vegInfoFile);
        /*蔬菜名*/
        fputs(current->vegName, vegInfoFile);
        fputs("\',\'", vegInfoFile);
        /*蔬菜种类*/
        fputc(current->vegType, vegInfoFile);
        fputs("\',\'", vegInfoFile);
        /*蔬菜营养成分*/
        fputs(current->nutritionFacts, vegInfoFile);
        fputs("\'}\n", vegInfoFile);


        if (current->next == NULL) {
            fputs("\n", vegInfoFile);
            break;
        }
        current = current->next;
    }
    fclose(vegInfoFile);
}

/*
 *  @param : 存储蔬菜信息文件的FILE指针
 *  @return : 一项蔬菜信息
 */
vegInfo getItemFromFile(FILE * vegInfoFile) {
    if (fgetc(vegInfoFile) != '{'){
        return NULL;
    }
    while (fgetc(vegInfoFile)!='\'');
    char c;
    char *buffer = (char *)malloc(sizeof(char) * 200);
    char *bufferHead = buffer;
    vegInfo result = (vegInfo) malloc(sizeof(struct veg_info));
    /*蔬菜编号*/
    while ((c = fgetc(vegInfoFile))!='\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    result->vegCode = getIntFromString(bufferHead);
    /*蔬菜名*/
    fgetc(vegInfoFile);
    fgetc(vegInfoFile);
    buffer = bufferHead;
    while ((c = fgetc(vegInfoFile))!='\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    char *vegName = result->vegName;
    strcpy(vegName, bufferHead);
    /*蔬菜种类编号*/
    fgetc(vegInfoFile);
    fgetc(vegInfoFile); //移2位以忽略,"
    result->vegType = fgetc(vegInfoFile);
    fgetc(vegInfoFile);
    /*蔬菜营养成分*/
    fgetc(vegInfoFile);
    fgetc(vegInfoFile); //移2位以忽略,"
    buffer = bufferHead;
    while ((c = fgetc(vegInfoFile))!='\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    char *nutritionFacts = result->nutritionFacts;
    strcpy(nutritionFacts, bufferHead);
    free(bufferHead);
    fgetc(vegInfoFile);  //'}'
    fgetc(vegInfoFile);  //'\n'
    result->next = NULL;
    result->pInfoList = NULL;
    return result;
}


void addVegInfoItem(vegInfo tail,vegInfo addItem) {
    tail->next = addItem;
    addItem->prev = tail;
    addItem->next = NULL;
}



vegInfo createVegInfoItem(int vegCode, char * vegName, char * vegType, char * nutritionFacts) {
    vegInfo info = (vegInfo) malloc(sizeof(struct veg_info));
    info->vegCode = vegCode;
    strcpy(info->vegName, vegName);
    if(*vegType >= '0' && *vegType <= '9')
        info->vegType = *vegType;
    else {
        info->vegType = getTypeCodeByName(vegType) + '0';
    }
    strcpy(info->nutritionFacts, nutritionFacts);
    return info;
}


void freeVegInfo(vegInfo head) {
    vegInfo current = head, prev;
    while (1) {
        if (current->next == NULL){
            free(current);
            break;
        }
        prev = current;
        current = current->next;
        free(prev);
    }
}

searchResult searchVegName(vegInfo veginfo, char *searchData) {
    int resultNum = 0;
    int *result;
    vegInfo current = veginfo;
    do {
        if(strstr(current->vegName, searchData) != NULL) {
            if (resultNum == 0){
                result = (int *)malloc(sizeof(int));
                resultNum = 1;
                result[0] = current->vegCode;
            }
            else {
                resultNum++;
                result = realloc(result, resultNum * sizeof(int));
                result[resultNum - 1] = current->vegCode;
            }
        }
        current = current->next;
    } while(current != NULL);
    if(resultNum == 0) {
        return NULL;
    }
    else {
        searchResult searchresult = (searchResult)malloc(sizeof(struct search_result));
        searchresult->resultNum = resultNum;
        searchresult->vegCodeArray = result;
        return searchresult;
    }
}


searchResult searchVegFacts(vegInfo veginfo, char *searchData) {
    int resultNum = 0;
    int *result;
    vegInfo current = veginfo;
    do {
        if(strstr(current->nutritionFacts, searchData)!=NULL) {
            if (resultNum == 0){
                result = (int *)malloc(sizeof(int));
                resultNum = 1;
                result[0] = current->vegCode;
            }
            else {
                resultNum++;
                result = realloc(result, resultNum * sizeof(int));
                result[resultNum - 1] = current->vegCode;
            }
        }
        current = current->next;
    } while(current != NULL);
    if(resultNum == 0) {
        return NULL;
    }
    else {
        searchResult searchresult = (searchResult)malloc(sizeof(struct search_result));
        searchresult->resultNum = resultNum;
        searchresult->vegCodeArray = result;
        return searchresult;
    }
}


void removeVegInfoItem(vegInfo removeItem) {
    /*删除的是最后一项*/
    if(removeItem->next == NULL) {
        removeItem->prev->next = NULL;
        free (removeItem);
        return ;
    }
    vegInfo current;
    current = removeItem->next;
    for(int i = removeItem->vegCode; current != NULL; i++, current = current->next){
        current->vegCode = i;
    }
    if (removeItem->vegCode == 1) {
        /*删除第一项--直接把第二项复制到第一项*/
        vegInfo next = removeItem->next;
        *removeItem = *next;
        free(next);
    }
    else {
        removeItem->prev->next = removeItem->next;
        removeItem->next->prev = removeItem->prev;
        free(removeItem);
    }
}

void removeVegInfoItems(vegInfo removeItem) {
    if (removeItem->vegCode == 1) {
        /*删除第一项--直接把第二项复制到第一项*/
        vegInfo next = removeItem->next;
        *removeItem = *next;
        free(next);
    }
    else {
        removeItem->prev->next = removeItem->next;
        removeItem->next->prev = removeItem->prev;
        free(removeItem);
    }
}

void renameVegInfoID(vegInfo head) {
    vegInfo current = head;
    for(int i = 1; current != NULL; i++, current = current->next){
        current->vegCode = i;
    }
}
