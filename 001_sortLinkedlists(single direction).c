#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeList {
    long value;
    struct nodeList *next;
}NL, *PNL;

void inputNum(PNL nodeList) {
    int maxLen = 10;        //max length of input numeral
    int curLen = 1;         //current length of input numeral
    char str[10];

    printf("please input %d integeral number Or press 'q/Q' key to quit Command-Line-Interface..\n", maxLen);

    while (1) {
            printf("NO.%-2d integeral number:", curLen);
            scanf("%s", str);
            PNL temp = (PNL)malloc(sizeof(NL));
            if (temp == NULL) {
                return;
            }
            temp->value = strtol(str, 0, 0);
            temp->next = NULL;
            if (strcmp(str, "q") != 0 && strcmp(str, "Q") != 0 && curLen < maxLen) {
            nodeList->next = temp;
            nodeList = nodeList->next;
            ++curLen;
        }
        else {
            break;
        }
    }
}

void sortList(PNL node) {
    if (node == NULL) {
        return;
    }
    PNL nextP = node;
    PNL startP = node->next;

    while (startP != 0x0) {
        nextP = node->next;
        while (nextP != 0x0) {
            if (startP->value > nextP->value) {
                long temp = startP->value;
                startP->value = nextP->value;
                nextP->value = temp;
            }
            nextP = nextP->next;
        }
        startP = startP->next;
    }
}

void outputResult(PNL node) {
    if (node == NULL){
        return;
    }
    PNL temp = node;
    printf("The sorted numeral list:");
    while (temp->next != NULL) {
        printf("%ld ", temp->next->value);
        temp = temp->next;
    }
}

int main() {
    PNL nodeList = (PNL)malloc(sizeof(NL));
    if (nodeList == NULL) {
        return;
    }
    inputNum(nodeList);
    sortList(nodeList);
    outputResult(nodeList);
//    free(nodeList);
    putchar('\n');
    getchar();
    getchar();

    return 0;
}
