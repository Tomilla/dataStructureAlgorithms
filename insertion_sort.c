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

#define MAXITEM 77
#define ASC "ascending"
#define DES "descending"

/* index of internal part loop, index of external part loop */
static int idx_inn, idx_ext, i_temp, i_total_elem;
/* string array use for store user input data */
static char s_user_input[MAXITEM];
/* buffer array for disorder elements */
static long l_arr_buf[MAXITEM];

void input_prompt(char *order)
{
        printf("\12Evaluate %s order...\12", order);
        printf("Please input total elements:\12");
        scanf("%d", &i_total_elem);

        printf("\12Please enter %d element%s Or press 'q/Q' key"
               "to leave Command-Line-Interface.. :)\12"
               , i_total_elem, (i_total_elem > 1) ? "s" : "");

        idx_ext = 0;

        while (1) {
                i_temp = (idx_ext + 1) % 100;
                printf("%d%s integral element: ", idx_ext + 1
                       , i_temp < 10 ? i_temp == 3 ? "rd" : i_temp == 2
                       ? "nd" : i_temp == 1 ? "st" : "th"
                       : "th");
                scanf("%s", s_user_input);

                if (strcmp(s_user_input, "q") == 0
                    || strcmp(s_user_input, "Q") == 0) {
                        i_total_elem--;
                        break;
                }

                l_arr_buf[idx_ext] = strtol(s_user_input, 0, 0);

                if ((idx_ext + 1) >= i_total_elem) return;

                idx_ext++;
        }
}

void output_prompt(char *order)
{
        printf("\12Array elements sorting in %s order:\12", order);

        if (strcmp(order, ASC) == 0)
                for (idx_ext = 0; idx_ext < i_total_elem; idx_ext++)
                        printf("%ld ", l_arr_buf[idx_ext]);
        else {
                idx_ext = i_total_elem - 1;
                for ( ; idx_ext >= 0; idx_ext--)
                        printf("%ld ", l_arr_buf[idx_ext]);
        }

        putchar('\12');
        getchar();
}

void insertion_sort(void)
{
        for (idx_ext = 1; idx_ext < i_total_elem; idx_ext++) {
                idx_inn = idx_ext - 1;          /* previous element*/
                i_temp = l_arr_buf[idx_ext];    /* current element*/
                for ( ; i_temp < l_arr_buf[idx_inn] && idx_inn >= 0;
                     idx_inn--) {
                        l_arr_buf[idx_inn + 1] = l_arr_buf[idx_inn];
                }
                l_arr_buf[idx_inn + 1] = i_temp;
        }
}

int bin_search(void)
{
        int low, high, mid;
        low = 0;
        high = idx_ext - 1;
        while (low <= high) {
                mid = (low + high) / 2;
                if (i_temp < l_arr_buf[mid])
                        high = mid - 1;
                else if (i_temp > l_arr_buf[mid])
                        low  = mid + 1;
                else
                        return mid;
        }
        return low;
}

void bin_ins_sort(void)
{
        for (idx_ext = 1; idx_ext < i_total_elem; idx_ext++) {
                /* Store elements that routines will insert later */
                i_temp = l_arr_buf[idx_ext];
                /* Using binary search algorithm find the position where
                 * routines ready insert.
                 * Note: binary-search must working on increasing order
                 * sequences(array) */
                int ins_pos = bin_search();
                for (idx_inn = idx_ext; l_arr_buf[idx_inn - 1] > i_temp
                     && idx_inn > ins_pos; idx_inn--) {
                        /* swap adjacent target elements */
                        l_arr_buf[idx_inn] = l_arr_buf[idx_inn - 1];
                }
                l_arr_buf[ins_pos] = i_temp;
        }
}

/**
 * "I know how it works, however, I don't want to tell you!" 233..
 *
 * This method starts by sorting elements far apart form each other and
 *   progressively reducing the gap between them.
 * Starting with far apart elements can move some out-of-place elements
 *   into position faster than a simple nearest neighbor exchange.
 */

void shell_sort(void)
{
        /* performs an insertion sort on elements of array l_arr_buf[]
         *   with the given gap.
         * Shell sort using Shell's (original) gap sequences:
         *   n/2, n/4, ... , 1.
         *   if gap == 1, performs an ordinary insertion sort */
        int gap = i_total_elem / 2;
        /* loop over gap */
        for (; gap > 0; gap /= 2) {
                /* do the insertion sort */
                for (idx_ext = gap; idx_ext < i_total_elem; idx_ext++) {
                        i_temp = l_arr_buf[idx_ext];
                        idx_inn = idx_ext - gap;
                        for (; l_arr_buf[idx_inn] > i_temp
                             && idx_inn >= 0; idx_inn -= gap) {
                                l_arr_buf[idx_inn + gap]
                                  = l_arr_buf[idx_inn];
                        }
                        l_arr_buf[idx_inn + gap] = i_temp;
                }
        }

}

void execute_sort(void (*sort_func)(), char *order) {
        input_prompt(order);
        sort_func();
        output_prompt(order);
}

char interactive_select_mode(void)
{

        char s_user_guide[] =
                "\12Please choose algorithm order mode\
                 \n0)\11-->\11ascending\
                 \n1)\11-->\11descending\12"
        ;
        printf("%s", s_user_guide);
        scanf("%s", s_user_input);
        return (char) s_user_input[0];
}

void interactive_select_scheme(void)
{
        char s_feature_info[] =
                "\12what sorting scheme you want to use?\
                 \12A)\11-->\11Direct insertion sort algorithm.\
                 \12B)\11-->\11Binary search insertion sort algorithm.\
                 \12C)\11-->\11Donald shell  insertion sort algorithm.\
                 \12";
        printf("%s", s_feature_info);
        scanf("%s", s_user_input);

        /* occurred implicit conversion */
        char select_mode, select_scheme = s_user_input[0];

        switch (select_scheme) {
                case 'a':
                case 'A':
                        select_mode = interactive_select_mode();
                        /* 0-1 implying ASCII DEC 48-49, respectively */
                        while (48 <= select_mode <= 49) {
                                if (select_mode == '0') {
                                        execute_sort(insertion_sort
                                                     , ASC);
                                        break;
                                } else if (select_mode  == '1') {
                                        execute_sort(insertion_sort
                                                     , DES);
                                        break;
                                } else {
                                        printf("ERROR: illegal option,"
                                               " please retry.. :p\12");
                                        select_mode
                                         = interactive_select_mode();
                                        continue;
                                }
                        }
                        break;
                case 'b':
                case 'B':
                        select_mode = interactive_select_mode();
                        while ( 48<= select_mode < 50) {
                                if (select_mode == '0') {
                                        execute_sort(bin_ins_sort
                                                     , ASC);
                                        break;
                                } else if (select_mode  == '1') {
                                        execute_sort(bin_ins_sort
                                                     , DES);
                                        break;
                                } else {
                                        printf("ERROR: illegal option,"
                                               " please retry.. :p\12");
                                        select_mode
                                          = interactive_select_mode();
                                        continue;
                                }
                        }
                        break;
                case 'c':
                case 'C':
                        select_mode = interactive_select_mode();
                        while ( 48<= select_mode < 50) {
                                if (select_mode == '0') {
                                        execute_sort(shell_sort
                                                     , ASC);
                                        break;
                                } else if (select_mode  == '1') {
                                        execute_sort(shell_sort
                                                     , DES);
                                        break;
                                } else {
                                        printf("ERROR: illegal option,"
                                               " please retry.. :p\12");
                                        select_mode
                                          = interactive_select_mode();
                                        continue;
                                }
                        }
                        break;

                default:
                        printf("ERROR: Encounter illegal options value,"
                               " please retry.. :D");
                        interactive_select_scheme();
                        break;
        }

}

int main(int argc, char **argv)
{
        interactive_select_scheme();

        putchar('\12');
        getchar();
        return 0;
}
