#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char *get_column (char *line, char *copyTarget, int colNum) {

    int i;
    int tabNum = 0;
    int firstLoc = 0;
    int secLoc = 0;

    for (i = 0; i < strlen(line); i++) {
        if (colNum == 1) { /*If first column requested*/
            if (line[i] == '\t') {
                /*printf ("tab detected");*/
                firstLoc = 0;
                secLoc = i;
                break;
            }
        }
        else {
            if (line[i] == '\n') { /*Detect newline (in case of final column)*/
                secLoc = i;
                break;
            }
            if (line[i] == '\t') { /*Detect tab*/
                /*printf ("tab detected");*/
                tabNum++;
                /*Error case for first or final col*/
                if (tabNum == colNum - 1) {
                    firstLoc = i + 1;
                }
                if (tabNum == colNum) {
                    secLoc = i;
                    break;
                }
            }
        }
    }
/*
    printf ("%d, %d\n", secLoc, firstLoc);*/
    copyTarget = malloc(sizeof(char) * (secLoc - firstLoc) + 1);
    strncpy(copyTarget, line + firstLoc, secLoc - firstLoc);
    copyTarget[secLoc - firstLoc] = '\0';
    return copyTarget;
}

char *reverse_word (char *target) {
    int i;
    int first = 0;
    int last = strlen(target) - 1;
    char temp;

    for (i = 0; i < strlen(target)/2; i++) {
        temp = target[first];
        target[first] = target[last];
        target[last] = temp;
        last--;
        first++;
    }

    return target;
}

/*Input getter function*/
char *get_line(FILE *fp) {
    char *line;
    char input;
    int index = 0;
    int size = 1; /*Initial size*/

    line = malloc(sizeof(char)*size);

    if (line != NULL) {
        /*Get character inputs until newline or input has been ended*/
        while ((input = getchar()) != '\n') {
            line[index] = input;
            index++;
            /*Realloc appropriately to maintain size of pointer*/
            if (index == size) {
                size = index + size;
                line = realloc(line, sizeof(char)*size);
            }
        }
        /*Index null character*/
        line[index] = '\0';
    }

    return line;
}

/*Line trimmer function: a bit buggy but works alright here as long as i free after*/
char *trim_line(char *target) {
    char *returnString;
    int i = 0;
    int trailing = 0;
    int count = 0;
    int wordSize = strlen(target);
    int returnSize;

    for (i = 0; i < wordSize; i++) {
        if (target[i] == ' ') {
            count++;
        }
    }
    if (count == 0) {
        return target;
    }

    for (i = 0; i < wordSize; i++) {
        if (!isspace(target[i])) {
            break;
        }
    }

    returnString = malloc(sizeof(char) * (strlen(target) - i) + 1);
    strncpy (returnString, target + i, wordSize);
    returnString[(strlen(target)-i)] = '\0';
    free(target);

    returnSize = strlen(returnString);

    while (returnSize > 0 && isspace(returnString[returnSize-1])) {
        returnSize--;
        trailing = 1;
    }

    if (trailing == 1) {
        returnString[returnSize] = '\0';
        returnString = realloc(returnString, sizeof(char) * (returnSize) + 1);
    }

    return returnString;
}