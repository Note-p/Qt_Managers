//
// Created by 黄涛 on 2017/7/17.
//

#include "PlantingInfo.h"


plantStructInfo loadPlantInfoFromFile(void) {
    FILE * plantInfoFile = fopen(PLANT_INFO_PATH, "r");
    plantStructInfo result = (plantStructInfo) malloc(sizeof(struct plant_struct_info));
    plantInfo head = getPlantItemFromFile(plantInfoFile);
    plantInfo current = head;
    head->prev = NULL;
    while (1) {
        plantInfo info = getPlantItemFromFile(plantInfoFile);
        if (info == NULL) {
            current->next = NULL;
            fclose(plantInfoFile);
            result->head = head;
            result->tail = current;
            result->num = current->id;
            return result;
        }
        current->next = info;
        info->prev = current;
        current = info;
    }
}

void savePlantInfoToFile(plantInfo head) {
    plantInfo current = head;
    FILE * plantInfoFile = fopen(PLANT_INFO_PATH, "w");
    while (1) {
        /*种植作物ID*/
        fputs("{\'", plantInfoFile);
        fputs(getStringFromInt(current->id), plantInfoFile);
        fputs("\',\'", plantInfoFile);
        /*蔬菜编号*/
        fputs(getStringFromInt(current->vegCode), plantInfoFile);
        fputs("\',\'", plantInfoFile);
        /*种植面积*/
        fputs(getStringFromInt(current->area), plantInfoFile);
        fputs("\',\'", plantInfoFile);
        /*收获重量*/
        fputs(getStringFromFloat(current->weight), plantInfoFile);
        fputs("\',\'", plantInfoFile);
        /*种植年份*/
        fputs(current->year, plantInfoFile);
        fputs("\'}\n", plantInfoFile);

        current = current->next;
        if (current == NULL) {
            break;
        }
    }
    fclose(plantInfoFile);
}

plantInfo getPlantItemFromFile(FILE * plantInfoFile) {
    if (fgetc(plantInfoFile) != '{') {
        return NULL;
    }
    while (fgetc(plantInfoFile)!='\'');
    char c;
    char *buffer = (char *)malloc(sizeof(char) * 20);
    char *bufferHead = buffer;
    plantInfo result = (plantInfo) malloc(sizeof(struct plant_info));
    /*种植作物id*/
    while((c = fgetc(plantInfoFile)) != '\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    result->id = getIntFromString(bufferHead);
    /*蔬菜编号*/
    fgetc(plantInfoFile);
    fgetc(plantInfoFile);
    buffer = bufferHead;
    while((c = fgetc(plantInfoFile)) != '\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    result->vegCode = getIntFromString(bufferHead);
    /*种植面积*/
    fgetc(plantInfoFile);
    fgetc(plantInfoFile);
    buffer = bufferHead;
    while((c = fgetc(plantInfoFile)) != '\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    result->area = getIntFromString(bufferHead);
    /*收获重量*/
    fgetc(plantInfoFile);
    fgetc(plantInfoFile);
    buffer = bufferHead;
    while((c = fgetc(plantInfoFile)) != '\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    result->weight = getFloatFromString(bufferHead);
    /*种植年份*/
    fgetc(plantInfoFile);
    fgetc(plantInfoFile);
    buffer = bufferHead;
    while((c = fgetc(plantInfoFile)) != '\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    strcpy(result->year, bufferHead);
    fgetc(plantInfoFile);
    fgetc(plantInfoFile);
    result->next = NULL;
    return result;
}

plantInfo createPlantInfoItem(int id, char * vegCode, char * area, char *weight, char * year) {
    plantInfo info = (plantInfo) malloc(sizeof(struct plant_info));
    info->id = id;
    if(*vegCode >= '0' && *vegCode <= '9')
        info->vegCode = getIntFromString(vegCode);
    else {
        vegStructInfo veginfo = loadVegInfoFromFile();
        info->vegCode = getVegInfoByName(veginfo->head, vegCode)->vegCode;
        /*释放内存*/
        freeVegInfo(veginfo->head);
        free(veginfo);
    }
    info->area = getIntFromString(area);
    info->weight = getFloatFromString(weight);
    strcpy(info->year, year);
    return info;
}

void addPlantInfoItem(plantInfo tail,plantInfo addItem) {
    tail->next = addItem;
    addItem->prev = tail;
    addItem->next = NULL;
}

void removePlantInfoItem(plantInfo removeItem) {
    plantInfo current;
    current = removeItem->next;
    for(int i = removeItem->id; current != NULL; i++, current = current->next){
        current->id = i;
    }
    if (removeItem->id == 1) {
        /*删除第一项--直接把第二项复制到第一项*/
        plantInfo next = removeItem->next;
        *removeItem = *next;
        free(next);
    }
    else {
        removeItem->prev->next = removeItem->next;
        removeItem->next->prev = removeItem->prev;
        free(removeItem);
    }
}

void removePlantInfoItems(plantInfo removeItem) {
    if (removeItem->id == 1) {
        /*删除第一项--直接把第二项复制到第一项*/
        plantInfo next = removeItem->next;
        *removeItem = *next;
        free(next);
    }
    else {
        removeItem->prev->next = removeItem->next;
        removeItem->next->prev = removeItem->prev;
        free(removeItem);
    }
}

void renamePlantInfoID(plantInfo head) {
    plantInfo current = head;
    for(int i = 1; current != NULL; i++, current = current->next){
        current->id = i;
    }
}

plantInfo getPlantInfoByID(plantInfo head, int id) {
    plantInfo result = head;
    while (1) {
        if (result->id == id){
            return result;
        }
        result = result->next;
        if (result == NULL) {
            printf("未找到该种植ID: %d", id);
            return NULL;
        }
    }
}

plantInfo getPlantInfoByVegCode(plantInfo head, int vegCode) {
    plantInfo result = head;
    while (1) {
        if (result->id == vegCode){
            return result;
        }
        result = result->next;
        if (result == NULL) {
            printf("未种植该蔬菜");
            return NULL;
        }
    }
}


int getPlantAreaAll(plantInfo head) {
    plantInfo current = head;
    int area = 0;
    for (; current != NULL; current = current->next) {
        area += current->area;
    }
    return area;
}

int getPlantAreaYear(plantInfo head, int year) {
    plantInfo current = head;
    int area = 0;
    for (; current != NULL; current = current->next) {
        if (getIntFromString(current->year) == year)
            area += current->area;
    }
    return area;
}

int getPlantAreaVegType(plantInfo head, vegInfo vegHead, int VegType) {
    plantInfo current = head;
    int area = 0;
    for (; current != NULL; current = current->next) {
        if (getVegInfoByCode(vegHead ,current->vegCode)->vegType - '0' == VegType)
            area += current->area;
    }
    return area;
}

float getPlantWeightAll(plantInfo head) {
    plantInfo current = head;
    float weight = 0;
    for (; current != NULL; current = current->next) {
        weight += current->weight;
    }
    return weight;
}

float getPlantWeightYear(plantInfo head, int year) {
    plantInfo current = head;
    float weight = 0;
    for (; current != NULL; current = current->next) {
        if (getIntFromString(current->year) == year)
            weight += current->weight;
    }
    return weight;
}

float getPlantWeightVegType(plantInfo head, vegInfo vegHead, int VegType) {
    plantInfo current = head;
    float weight = 0;
    for (; current != NULL; current = current->next) {
        if (getVegInfoByCode(vegHead ,current->vegCode)->vegType - '0' == VegType)
            weight += current->weight;
    }
    return weight;
}

void freePlantInfo(plantInfo head) {
    plantInfo current = head, prev = head;
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


