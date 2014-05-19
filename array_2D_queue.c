/*
 *  #brief: a simple implement of Two-Dimensional Single-Channel Queue
 *  #author Muwaii_Cz
 *  #date 2014_05_18
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef struct twoDimensional {
  int x;
  int y;
}innerElem; // inner element of single-channel-queque

typedef struct sigleChannel {
  innerElem **rear; // the rear parts of `QUEUE`
  innerElem *front; // the front parts of `QUEUE`
  int length;       // the total length of `QUEUE`
  int size;         // the current containment of `QUEUE`
}_2dQueue;

// write proper description method of `QUEUE`

// create a `QUEUE` that initialize length is `i_length`
_2dQueue* createQueue(int i_length);

void destoryQueue(_2dQueue *p_queue);
void clearQueue(_2dQueue *p_queue);
int queueLength(_2dQueue *p_queue);
int queueSize(_2dQueue *p_queue);
int isEmpty(_2dQueue *p_queue);
int queueHead(_2dQueue *p_queue, innerElem **p_elem);
int enterQueue(_2dQueue *p_queue, innerElem *p_elem);
int leaveQueue(_2dQueue *p_queue, innerElem **p_elem);

// traverse current `QUEUE`, at the same time \
// apply {function} `*func` for each inner element
void traverseQueue(_2dQueue *p_queue, void(*func)(innerElem *p_elem));

// *TEST* add a example of callback{function} for `QUEUE` traverse method
void printElem(innerElem *p_elem);

int main(void) {
  innerElem elem_set_1 = {07, 17};
  innerElem elem_set_2 = {27, 37};
  innerElem elem_set_3 = {47, 57};
  innerElem elem_set_4 = {67, 77};
  innerElem elem_set_5 = {87, 97};

  // *TEST* {function} create `QUEUE`
  _2dQueue *p_queue_new = createQueue(3);

  // *TEST* {function} enter QUEUE
  enterQueue(p_queue_new, &elem_set_1);
  enterQueue(p_queue_new, &elem_set_2);
  enterQueue(p_queue_new, &elem_set_3);
  enterQueue(p_queue_new, &elem_set_4);
  enterQueue(p_queue_new, &elem_set_5);

  // *TEST* {function) traverse `QUEUE`
  traverseQueue(p_queue_new, printElem);

  // *TEST* {function} isEmpty && queueSize && queueLength
    printf("\n\n*****************************************************");
    if (isEmpty(p_queue_new) != TRUE) {
      printf("\nthe current length of this `QUEUE`:\n>%d"
          , queueSize(p_queue_new));
      printf("\nthe total containment of this `QUEUE`:\n>%d"
          , queueLength(p_queue_new));
    }

  // *TEST* {function} leave `QUEUE`
  printf("\n\12******************************************************");
  printf("\n*TEST*printf all element:");
  innerElem *p_temp;

  while (leaveQueue(p_queue_new, &p_temp) != -1) {
    printf("\ncurrent element of leave `QUEUE`:\n(%d,%d)"
        , p_temp->x, p_temp->y);
    printf("\ncurrent length of this `QUEUE`:\n%d"
        , queueLength(p_queue_new));
  }

  // *TEST* {function} clear `QUEUE`
  printf("\n\12*****************************************************");
  printf("\nNow continue enter two element to this `QUEUE`\n");
  enterQueue(p_queue_new, &elem_set_1);
  enterQueue(p_queue_new, &elem_set_2);

  traverseQueue(p_queue_new, printElem);
  printf("\nclear all element in this `QUEUE`, loading...");

  clearQueue(p_queue_new);
  printf("\nthe total containment of this `QUEUE`:\n%d"
      , queueLength(p_queue_new));
  printf("\nthe current length of this `QUEUE`:\n%d"
      , queueLength(p_queue_new));

  // *TEST* {function} queueHead
  printf("\nNow continue enter three element to this `QUEUE`\n");
  enterQueue(p_queue_new, &elem_set_3);
  enterQueue(p_queue_new, &elem_set_4);
  enterQueue(p_queue_new, &elem_set_5);

  traverseQueue(p_queue_new, printElem);
  queueHead(p_queue_new, &p_temp);

  printf("\nfetch the Head element of `QUEUE`:\n(%d,%d)"
      , p_temp->x, p_temp->y);
  printf("\nthe total containment of this `QUEUE`:\n%d"
      , queueLength(p_queue_new));
  printf("\nthe current length of this `QUEUE`:\n%d\n"
      , queueLength(p_queue_new));

  // *TEST* {function} destory `QUEUE`
  destoryQueue(p_queue_new);

  getchar();
  return TRUE;
}

// The complete datail of archieve `QUEUE` function

/**
 * # create a new `QUEUE` of specific length
 *
 * @param `i_length` queue initialize length
 * @return a pointer that point to  address of new created `QUEUE`
 */

_2dQueue *createQueue(int i_length) {
  _2dQueue *p_queue = (_2dQueue *)malloc(sizeof(_2dQueue));
  p_queue->rear = (innerElem **)calloc(i_length, sizeof(innerElem **));
  p_queue->front = p_queue->rear[0];
  p_queue->length = 0;
  p_queue->size = i_length;

  return p_queue;
}

/**
 * # destory `QUEUE`
 *
 * @param `p_queue` a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` is wait destory
 */
void destoryQueue(_2dQueue *p_queue) {
  free(p_queue->rear);
  free(p_queue);
  p_queue = NULL;
}

void clearQueue(_2dQueue *p_queue) {
  p_queue->front = p_queue->rear[0];
  p_queue->length = 0;
}

int queueLength(_2dQueue *p_queue) {
  return p_queue->length;
}

int queueSize(_2dQueue *p_queue) {
  return p_queue->size;
}

int isEmpty(_2dQueue *p_queue) {
  return p_queue->length == 0 ? TRUE : FALSE;
}

int queueHead(_2dQueue *p_queue, innerElem **p_elem) {
  if (p_queue->length == 0) {
    *p_elem = NULL;
    return FALSE;
  }

  *p_elem = p_queue->rear[p_queue->length - 1];
  return p_queue->length - 1;
}

/**
 * # insert element `p_elem` to the tial of `2D1C-QUEUE`
 *
 * @param `p_queue` a pointer that point to the address of `QUEUE`,
 *        which address is a free space
 * @param `p_elem` a pointer that point to the address of element,
 *        which element is wait processor insert
 * @return new length of `QUEUE`, after successful insert new element
 *
 */

int enterQueue(_2dQueue *p_queue, innerElem *p_elem) {
  // verify: need to expand `QUEUE` capacity?
  if (p_queue->length == p_queue->size) {
    // by default, the realloc capacity is twice the origin
    p_queue->rear = realloc(p_queue->rear
        , 2 * p_queue->size * sizeof(innerElem *));
    p_queue->size *= 2;
  }
  int idx = 0;
  for (idx = p_queue->length; idx > 0; idx--) {
    p_queue->rear[idx] = p_queue->rear[idx - 1];
  }
  p_queue->rear[0] = p_elem;
  p_queue->front = p_queue->rear[p_queue->length];

  return ++p_queue->length;
}
/**
 * # Specific first element leave current `QUEUE`
 *
 * @param `p_queue` a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` is wait leave element
 * @param `p_elem` a pointer that point to the adress of memory space \
 *        , that space used to receiving leaved element from `QUEUE`
 * @return {length} if element successful leave `QUEUE` return the \
 *         length of current `QUEUE`(leave one head elemment),
 *         else return FALSE
 */

int leaveQueue(_2dQueue *p_queue, innerElem **p_elem) {
  if (p_queue->length == 0) {
      *p_elem = NULL;
      return FALSE;
  }
  *p_elem = p_queue->front;
  p_queue->length--; // decreasing
  p_queue->front = p_queue->rear[p_queue->length - 1];

  return p_queue->length;
}
/**
 * # Traverse `QUEUE` element, meantime apply {function} `func` for \
 *   each element
 *
 * @param `p_queue` a {pointer} that point to the address of `QUEUE`,
 *        which `QUEUE` is wait program handle
 * @param `p_elem` a {pointer} that point to the address of {function} \
 *        `func`, which `func` is a callback {function}
 */

void traverseQueue(_2dQueue *p_queue, void(*func)(innerElem *p_elem)) {
  int idx = 0;
  for (idx = 0; idx < p_queue->length; ++idx) { //*//
    func(p_queue->rear[idx]);
  }
}

/**
 * # A simple callback{function} for traverse `QUEUE`
 *
 * @param `p_elem` a {pointer} that point to the addess of element,
 *        which element is wait to handle
 *
 */

void printElem(innerElem *p_elem) {
  printf("(%d, %d)", p_elem->x, p_elem->y);
}
