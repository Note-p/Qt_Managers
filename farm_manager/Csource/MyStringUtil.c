//
// Created by 黄涛 on 2017/7/17.
//

#include "MyStringUtil.h"

int  getIntFromString (char * head){
    char * str = head;
    int result = 0;
    while (*(++str)!='\0');
    str--;
    for (int i = 0; ; i++, str--) {
        result += (*str - '0') * pow(10, i);
        if (str == head)
            break;
    }
    return result;
}

char * getStringFromInt (int num) {
    char * buffer = (char *) malloc(sizeof(char) * 10);
    buffer[9] = '\0';
    int a = num,i;
    for (i = 8; i >= 0; i--){
        buffer[i] = a % 10 + '0';
        a = a/10;
    }
    for (i = 0; buffer[i] == '0'; i++);
    return (buffer + i);
}

float getFloatFromString (char *head) {
    return atof(head);
}

char * getStringFromFloat (float num) {
    char *result = (char *) malloc(sizeof(char) * 20);
    sprintf(result, "%.3f", num);
    return result;
}

int strinstr(char *str, char *inthis) {
    char *small = str, *big = inthis;
    while(*big != *small) {
        big++;
    }
    while(*(big++) == *(small++)){
        if (*small == '\n' || *small == '\0') {
            return 1;
        }
    }
    return 0;
}
