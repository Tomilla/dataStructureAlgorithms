/**********************************************************************
	> File Name: insertion_sort.c
	> Author: Pero.rin
	> E-Mail: Gero.rim@gmail.com
	> Created Time: Sat 28 Jun 2014 06:36:25 PM HKT
 **********************************************************************/

/*!
 * Source code of simple insertion sort implementation using array in
 * ascending or descending order in C programming language.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 77

/* index of internal part loop, index of external part loop */
static int idx_inn, idx_ext, i_temp, i_total_elem;
/* buffer array ofr disorder elements */
static long l_arr_buf[MAXSIZE];

void input_prompt(char *order)
{
        printf("\12Evalute %s order ...\12", order);
        printf("Please input elements:\12");
        scanf("%d", &i_total_elem);

        printf("Please input %d elements..\12", i_total_elem);

        for (idx_ext = 0; idx_ext < i_total_elem; idx_ext++) {
                scanf("%ld", &l_arr_buf[idx_ext]);
        }
}

void output_prompt(char *order)
{
        printf("Array elements sorting in %s order:\12", order);

        for (idx_ext = 0; idx_ext < i_total_elem; idx_ext++)
                printf("%ld ", l_arr_buf[idx_ext]);

        putchar('\12');
        getchar();
}

void insertion_sort_desc(void)
{
        input_prompt("descending");

        idx_ext = 1;
        while (idx_ext < i_total_elem) {
                idx_inn = idx_ext - 1;
                i_temp = l_arr_buf[idx_ext];
                while (i_temp > l_arr_buf[idx_inn] && idx_inn >= 0) {
                        l_arr_buf[idx_inn + 1] = l_arr_buf[idx_inn];
                        idx_inn -= 1;
                }
                l_arr_buf[idx_inn + 1] = i_temp;
                idx_ext += 1;
        }

        output_prompt("descending");
}

int main(int argc, char **argv)
{
        insertion_sort_desc();

        putchar('\12');
        getchar();
        return 0;
}
