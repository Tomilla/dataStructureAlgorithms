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

/* remove the M$ pre-compiler secure warnings */
#ifdef _MSC_VER         /* M$ Visual Studio */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXITEM 77
#define ASC "ascending"
#define DES "descending"

/* pointer to function return void */
typedef void (*func_ptr_void)();

typedef int ELEM ;
#define KEY(A) (A)
#define LESS(A, B) (KEY(A) < KEY(B))
#define EXCH(A, B) { ELEM t = A; A = B; B = t; }
#define CMP_EXCH(A, B) if (LESS(B, A)) EXCH(A, B)
/* since x ^ x = 1, except that x equal 0x0 */
//#define EXCH(A, B) { A ^= B; B ^= A;  A ^= B; }

/* index of internal part loop, index of external part loop */
static int idx_inn, idx_ext, i_temp, i_total_elem;
/* string array use for store user input data */
static char s_user_input[MAXITEM];
/* buffer array for disorder elements */
static long l_arr_buf[MAXITEM];

void to_lower_case(char *);
void to_upper_case(char *);
void input_prompt(char *);
void output_prompt(char *);
void bubble_sort(void);
void selection_sort(void);
void dir_ins_sort(void);
int  bin_search(void);
void bin_ins_sort(void);
void shell_sort(void);
char interactive_select_mode(void);
void inject_func(func_ptr_void);
void execute_sort(func_ptr_void, char *);
void interactive_select_scheme(void);
void interactive_inquiry_again(void);

int main(int argc, char **argv)
{
        interactive_select_scheme();

        printf("\12See you later :-)\n\xc");
        getchar();
        return 0;
}

void to_lower_case(char *s_ptr)
{
        char *p = s_ptr;
        /* loop through the string and convert *
         * each character to lowercase.        */
        //for (idx_ext = 0; p[idx_ext]; idx_ext++)
        //        p[idx_ext] = tolower(p[idx_ext]);

        /* to convert to lower case is equivalent to    *
         * rise bit 0x40 or add 0x20. [ASCII knowledge] */

        for (; *p; ++p)
                /* if current character in the range *
                 *   0x40 < {A-Z} < 0x5B             *
                 *   then convert it to lower case.  */
                *p = *p >='A' && *p <='Z'  ? *p + 0x20 : *p;
}

void to_upper_case(char *s_ptr)
{
        char *p = s_ptr;
        /* one liners version, design by J.F. Sebastian */
        for (; *p; ++p) *p = toupper(*p);
}

void input_prompt(char *order)
{
        printf("\12Evaluate %s order...\12", order);
        printf("Please input total elements:\12");
        scanf("%d", &i_total_elem);

        printf("\12Please enter %d element%s Or press 'q/Q' key"
               "\40to leave Command-Line-Interface.. :)\12"
               , i_total_elem, (i_total_elem > 1) ? "s" : "");

        idx_ext = 0;

        while (1) {
                i_temp = (idx_ext + 1) % 100;
                printf("%d%s integral element: ", idx_ext + 1
                       , i_temp < 10 ? i_temp == 3 ? "rd" : i_temp == 2
                       ? "nd" : i_temp == 1 ? "st" : "th"
                       : "th");
                scanf("%s", s_user_input);

                if (strcmp(s_user_input, "q") == 0 ||
                    strcmp(s_user_input, "Q") == 0) {
                        /* resetting total elements *
                         * to actual lower bound. ^_*/
                        i_total_elem = idx_ext;
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
                for (; idx_ext >= 0; idx_ext--)
                        printf("%ld ", l_arr_buf[idx_ext]);
        }

        interactive_inquiry_again();
}

void bubble_sort(void)
{
        for (idx_ext = i_total_elem - 2; idx_ext >= 0; idx_ext--) {
                for (idx_inn = 0; idx_inn <= idx_ext; idx_inn++)
                        CMP_EXCH(l_arr_buf[idx_inn],
                                 l_arr_buf[idx_inn + 1]);
        }
}

void selection_sort(void)
{
        /**
         * Advance the position through the entire array
         * Why could i do idx_ext < i_total - 1, because
         *   single element is also mininum element.
         * Find the min element in the unsorted array
         *   l_arr_buf[idx_ext ... i_total_elem - 1].
         */
        for (idx_ext = 0; idx_ext < i_total_elem; idx_ext++) {
                /* assume the min is the first element */
                int i_min = idx_ext;
                /* test against after idx_ext to find the smallest */
                idx_inn = idx_ext + 1;
                for (; idx_inn < i_total_elem; idx_inn++) {
                        /* if result is less, it is the new minimum */
                        /* found new minimum; remember its index */
                        if (l_arr_buf[idx_inn] < l_arr_buf[i_min])
                                i_min = idx_inn;
                }

                if (i_min != idx_inn)
                        EXCH(l_arr_buf[idx_ext], l_arr_buf[i_min]);
        }
}

void dir_ins_sort(void)
{
        for (idx_ext = 1; idx_ext < i_total_elem; idx_ext++) {
                idx_inn = idx_ext - 1;          /* previous element*/
                i_temp = l_arr_buf[idx_ext];    /* current element*/
                for (; i_temp < l_arr_buf[idx_inn] && idx_inn >= 0;
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
                        return mid + 1;
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
                int
                ins_pos = bin_search();
                idx_inn = idx_ext -  1;
                for (; l_arr_buf[idx_inn] > i_temp &&
                     (idx_inn + 1) > ins_pos; idx_inn--) {
                        /* swap adjacent target elements */
                        l_arr_buf[idx_inn + 1] = l_arr_buf[idx_inn];
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
                        for (; l_arr_buf[idx_inn] > i_temp &&
                             idx_inn >= 0; idx_inn -= gap) {

                                l_arr_buf[idx_inn + gap] =
                                  l_arr_buf[idx_inn];
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

/* Express Dependency Injection Mechanism */
void inject_func(void (*sort_func)())
{
        char
        select_mode = interactive_select_mode();
        /* 0-1 implying ASCII DEC 48-49, respectively */
        while ( 48 <= select_mode < 50) {
                if (select_mode == '0') {
                        execute_sort(sort_func, ASC);
                        break;
                } else if (select_mode  == '1') {
                        execute_sort(sort_func, DES);
                        break;
                } else {
                        printf("ERROR: illegal option,"
                                " please retry.. :p\12");
                        select_mode = interactive_select_mode();
                        continue;
                }
        }

}

void interactive_select_scheme(void)
{
        char s_feature_info[] =
                "\12What sorting scheme you want to use?\
                 \12A)\11-->\11Bubble sort algorithm.\
                 \12B)\11-->\11Selection sort algorithm.\
                 \12C)\11-->\11Direct insertion sort algorithm.\
                 \12D)\11-->\11Donald shell insertion sort algorithm.\
                 \12E)\11-->\11Binary search insertion sort algorithm.\
                 \12";
        printf("%s", s_feature_info);
        scanf("%s", s_user_input);

        /* occurred implicit conversion */
        char select_scheme = s_user_input[0];

        switch (select_scheme) {
                case 'a':
                case 'A':
                        inject_func(bubble_sort);
                        break;
                case 'b':
                case 'B':
                        inject_func(selection_sort);
                        break;
                case 'c':
                case 'C':
                        inject_func(dir_ins_sort);
                        break;
                case 'd':
                case 'D':
                        inject_func(shell_sort);
                        break;
                case 'e':
                case 'E':
                        inject_func(bin_ins_sort);
                        break;
                default:
                        printf("ERROR: Encounter illegal options value,"
                               " please retry.. :D\12");
                        interactive_select_scheme();
                        break;
        }
}

void interactive_inquiry_again(void)
{
        char
        *select_answer, *s_taste_other =
            "\12Are you want to taste other interesting algorithm? XD\
             \12\
             \12(Yes to continue :)\
             \12"
            ;
        printf("%s", s_taste_other);
        scanf("%s", s_user_input);

        /* Remove Case Sensitive */
        //to_upper_case(s_user_input);
        to_lower_case(s_user_input);
        select_answer = s_user_input;

        if (!(strcmp(select_answer, "yes")))
                interactive_select_scheme();
}
