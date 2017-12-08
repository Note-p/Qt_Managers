//
// Created by hunto on 2017/8/31 0031.
//

#include "TypeInfo.h"

typeInfo getTypeItemFromFile(FILE * typeInfoFile);

typeInfo loadTypeInfoFromFile (void) {
    FILE * typeInfoFile = fopen(TYPE_INFO_PATH, "r");
    typeInfo head = getTypeItemFromFile(typeInfoFile);
    typeInfo current = head;
    while (1) {
        current->next = getTypeItemFromFile(typeInfoFile);
        if (current->next == NULL){
            current->next=NULL;
            fclose(typeInfoFile);
            return head;
        }
        current = current->next;
    }
}

void saveTypeInfoToFile(typeInfo head) {
    typeInfo current = head;
    FILE * typeInfoFile = fopen(TYPE_INFO_PATH, "w");
    while (1) {
        /*种类编号*/
        fputs("{\'", typeInfoFile);
        fputc(current->typeCode, typeInfoFile);
        fputs("\',\'", typeInfoFile);
        /*种类名称*/
        fputs(current->typeName, typeInfoFile);
        fputs("\'}\n", typeInfoFile);

        if (current->next == NULL) {
            fputs("\n", typeInfoFile);
            break;
        }
        current = current->next;
    }
    fclose(typeInfoFile);
}


typeInfo getTypeItemFromFile(FILE * typeInfoFile) {
    if (fgetc(typeInfoFile) != '{'){
        return NULL;
    }
    while (fgetc(typeInfoFile)!='\'');
    char c;
    char *buffer = (char *)malloc(sizeof(char) * 20);
    char *bufferHead = buffer;
    typeInfo result = (typeInfo) malloc(sizeof(struct type_info));
    /*种类编号*/
    result->typeCode = fgetc(typeInfoFile);
    /*种类名*/
    fgetc(typeInfoFile);
    fgetc(typeInfoFile);
    fgetc(typeInfoFile);
    buffer = bufferHead;
    while ((c = fgetc(typeInfoFile))!='\'') {
        * (buffer++) = c;
    }
    *buffer = '\0';
    strcpy(result->typeName, bufferHead);
    free(bufferHead);
    fgetc(typeInfoFile);  //'}'
    fgetc(typeInfoFile);  //'\n'
    result->next = NULL;
    result->vInfoList = NULL;
    return result;
}

void addTypeInfoItem (typeInfo head ,char *addItemName) {
    typeInfo current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    typeInfo addItem = (typeInfo)malloc(sizeof(struct type_info));
    addItem->next = NULL;
    addItem->vInfoList = NULL;
    addItem->typeCode = current->typeCode + 1;
    strcpy(addItem->typeName, addItemName);
    current->next = addItem;
}

int deleteTypeInfo (typeInfo head, char typeCode) {
    typeInfo current = head;
    typeInfo prev = NULL;
    for (; current != NULL; prev = current, current = current->next) {
       if (current->typeCode == typeCode) {
           if (prev == NULL) {
               prev = current->next;
               *current = *(current->next);
               free (prev);
           }
           else {
               prev->next = current->next;
               free(current);
           }
           current = head;
           for (char code = '1'; current != NULL; code++, current = current->next) {
               current->typeCode = code;
           }
           return 1;
       }
    }
    return 0;
}

int editTypeInfo(typeInfo head, char typeCode, char *typeName) {
    typeInfo current = head;
    for (; current != NULL; current = current->next) {
        if (current->typeCode == typeCode) {
            strcpy(current->typeName, typeName);
            return 1;
        }
    }
    return 0;
}




