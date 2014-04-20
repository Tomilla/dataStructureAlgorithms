#include <stdio.h>
#define left 0
#define right 5
#define maxSize 5

/* Quick Sort Algorithm
 * sort array[left] ... array[rigth] int to increasing order.
 */

void qsort(int ai_v[], int i_left, int i_rigth) {
    int i, last;
    void swap (int ai_v[], int m, int n);

    if (i_left >= i_rigtt) {            //do nothing if integeral array 'ai_v'...
        return;                         //contains fewer than two element.
    }
    swap (ai_v, i_left, (left+right)/2);//move partition element to 'ai_v[0]'
    last = i_left;
    for (m = i_left + 1; m <= i_right; m++) {
        if (ai_v[m] < ai_v[i_left]) {
            swap (ai_v[], ++left, m);
        }
    }
    swap (ai_v[], i_left, i_right);
    swap (ai_v[], i_left, last + 1);
    swap (ai_v[], last + 1, i_right);
}

void opResult(int ai_v) {               //output Result
    for (int m = 0; m < maxSize; m++) {
        printf("%d", ai_v[m]);
    }
}

int main(void) {
    int ai_v[maxSize] = {8, 9, 4, 7, 0};
    qsort[ai_v, 0, maxSize];
    printf("press any keys display result");
    getchar();
    opResult(ai_v);
    getchar();
}
