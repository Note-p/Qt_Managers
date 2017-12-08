//
// Created by hunto on 2017/9/6 0006.
//

#include "VegDataBackupUtil.h"
#include "VegInfo.h"
#include "PlantingInfo.h"
#include "TypeInfo.h"

int backupDataFileTo (char *filePath) {
    char ch;
    FILE *backupFile = fopen(filePath, "w");
    if(backupFile == NULL) {
        //文件打开失败
        return 0;
    }
    //typeInfo
    //文件识别码
    fputs("#\n", backupFile);
    FILE * typeInfoFile = fopen(TYPE_INFO_PATH, "r");
    while ((ch = fgetc(typeInfoFile)) != EOF) {
        fputc(ch, backupFile);
    }
    fclose(typeInfoFile);
    //vegInfo
    //文件识别码
    fputs("#\n", backupFile);
    FILE * vegInfoFile = fopen(VEG_INFO_PATH, "r");
    while ((ch = fgetc(vegInfoFile)) != EOF) {
        fputc(ch, backupFile);
    }
    fclose(vegInfoFile);
    //plantInfo
    //文件识别码
    fputs("#\n", backupFile);
    FILE * plantInfoFile = fopen(PLANT_INFO_PATH, "r");
    while ((ch = fgetc(plantInfoFile)) != EOF) {
        fputc(ch, backupFile);
    }
    fclose(plantInfoFile);
    fclose(backupFile);
    return 1;
}

int getDataFileFromBackupFile (char *filePath) {
    char ch;
    FILE *backupFile = fopen(filePath, "r");
    if ((ch = fgetc(backupFile)) != '#') {
        /*标志不对，不是备份文件*/
        return 0;
    }
    fgetc(backupFile); // '\n'
    //typeInfo
    FILE *typeInfoFile = fopen(TYPE_INFO_PATH, "w");
    while ((ch = fgetc(backupFile)) != '#') {
        fputc(ch, typeInfoFile);
    }
    fclose(typeInfoFile);
    fgetc(backupFile); // '\n'
    //vegInfo
    FILE *vegInfoFile = fopen(VEG_INFO_PATH, "w");
    while ((ch = fgetc(backupFile)) != '#') {
        fputc(ch, vegInfoFile);
    }
    fclose(vegInfoFile);
    fgetc(backupFile); // '\n'
    //plantInfo
    FILE *plantInfoFile = fopen(PLANT_INFO_PATH, "w");
    while ((ch = fgetc(backupFile)) != EOF) {
        fputc(ch, plantInfoFile);
    }
    fclose(plantInfoFile);
    fclose(backupFile);
    return 1;
}
