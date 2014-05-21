/**
 *  #brief: a simple implement of Three-Dimensional Single-Channel Queue
 *
 *  #author Muwaii_Cz
 *  #date 2014_05_18
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef struct threeDimensional {
  int x;
  int y;
  int z;
}innerElem; // inner element of single-channel-queque

typedef struct sigleChannel {
  innerElem **rear; // the rear parts of `QUEUE`
  innerElem *front; // the front parts of `QUEUE`
  int length;       // the total length of `QUEUE`
  int size;         // the current containment of `QUEUE`
}_3dQueue;

////write proper description method of `QUEUE`////

// create a `QUEUE` that initialize length is `i_length`
_3dQueue* createQueue(int i_length);

void destoryQueue(_3dQueue *p_queue);
void clearQueue(_3dQueue *p_queue);
int queueLength(_3dQueue *p_queue);
int queueSize(_3dQueue *p_queue);
int isEmpty(_3dQueue *p_queue);
int queueHead(_3dQueue *p_queue, innerElem **p_elem);
int enterQueue(_3dQueue *p_queue, innerElem *p_elem);
int leaveQueue(_3dQueue *p_queue, innerElem **p_elem);

// traverse current `QUEUE`, at the same time \
// apply {function} `*func` for each inner element
void traverseQueue(_3dQueue *p_queue, void(*func)(innerElem *p_elem));

// *TEST* add a example of callback{function} for `QUEUE` traverse \
// method
void incrElemValue(innerElem p_elem[]);
void printElemValue(innerElem *p_elem);

int main(void) {
  innerElem elem_set_0 = {07, 17, 27};
  innerElem elem_set_1 = {27, 37, 47};
  innerElem elem_set_2 = {47, 57, 67};
  innerElem elem_set_3 = {67, 77, 87};
  innerElem elem_set_4 = {87, 97, 07};

  innerElem elem_set_5 = {7, 7, 7};
  innerElem elem_set_6 = {77, 77, 77};
  innerElem elem_set_7 = {777, 777, 777};
  innerElem elem_set_8 = {7777, 7777, 7777};
  innerElem elem_set_9 = {77777, 77777, 77777};

  // *TEST* {function} create `QUEUE`
  _3dQueue *p_queue_new = createQueue(3);

  // *TEST* {function} enter QUEUE
  enterQueue(p_queue_new, &elem_set_0);
  enterQueue(p_queue_new, &elem_set_1);
  enterQueue(p_queue_new, &elem_set_2);
  printf("\n*TEST* printf all element:\n");

  // *TEST* {function) traverse `QUEUE`
  traverseQueue(p_queue_new, printElemValue);

  // *TEST* {function} isEmpty && queueSize && queueLength
  printf("\n*********************************************************");
  if (isEmpty(p_queue_new) != TRUE) {
    printf("\nthe current length of this `QUEUE`:\n>%d"
        , queueSize(p_queue_new));
    printf("\nthe total containment of this `QUEUE`:\n>%d"
        , queueLength(p_queue_new));
  }

  // *TEST* {function} leave `QUEUE`
  printf("\n\12******************************************************");
  printf("\n*TEST* printf all element:");
  innerElem *p_temp;

  while (leaveQueue(p_queue_new, &p_temp) != -1) {
    printf("\ncurrent element of leave `QUEUE`:\n(%d,%d,%d)"
      , p_temp->x, p_temp->y, p_temp->z);
    printf("\ncurrent length of this `QUEUE`:\n%d"
      , queueLength(p_queue_new));
  }

  // *TEST* {function} clear `QUEUE`
  printf("\n\12******************************************************");
  printf("\nNow continue enter two element to this `QUEUE`\n");
  enterQueue(p_queue_new, &elem_set_3);
  enterQueue(p_queue_new, &elem_set_4);

  traverseQueue(p_queue_new, printElemValue);
  printf("\nclear all element in this `QUEUE`, loading...");

  clearQueue(p_queue_new);
  printf("\nthe total containment of this `QUEUE`:\n%d"
    , queueSize(p_queue_new));
  printf("\nthe current length of this `QUEUE`:\n%d"
    , queueLength(p_queue_new));

  // *TEST* {function} queueHead
  printf("\nNow continue enter ten element to this `QUEUE`\n");

  enterQueue(p_queue_new, &elem_set_0);
  enterQueue(p_queue_new, &elem_set_1);
  enterQueue(p_queue_new, &elem_set_2);
  enterQueue(p_queue_new, &elem_set_3);
  enterQueue(p_queue_new, &elem_set_4);
  enterQueue(p_queue_new, &elem_set_5);
  enterQueue(p_queue_new, &elem_set_6);
  enterQueue(p_queue_new, &elem_set_7);
  enterQueue(p_queue_new, &elem_set_8);
  enterQueue(p_queue_new, &elem_set_9);

  // traverse all element of `Queue`, meanwhile increse each items by 10
  traverseQueue(p_queue_new, incrElemValue);
  // after incresing
  traverseQueue(p_queue_new, printElemValue);
  queueHead(p_queue_new, &p_temp);

  printf("\nfetch the Head element of `QUEUE`:\n(%d,%d,%d)"
    , p_temp->x, p_temp->y, p_temp->z);
  printf("\nthe total containment of this `QUEUE`:\n%d"
    , queueSize(p_queue_new));
  printf("\nthe current length of this `QUEUE`:\n%d\n"
    , queueLength(p_queue_new));

  // *TEST* {function} destory `QUEUE`
  destoryQueue(p_queue_new);

  getchar();
  return TRUE;
}

////The complete datail of archieve `QUEUE` function////

/**
 * # create a new `QUEUE` of specific length
 *
 * @param `i_length` queue initialize length
 * @return a pointer that point to  address of new created `QUEUE`
 */

_3dQueue *createQueue(int i_length) {
  _3dQueue *p_queue = (_3dQueue *)malloc(sizeof(_3dQueue));
  p_queue->rear = (innerElem **)calloc(i_length, sizeof(innerElem **));
  p_queue->front = p_queue->rear[0];
  p_queue->length = 0;
  p_queue->size = i_length;

  return p_queue;
}

/**
 * # Destory `QUEUE`
 *
 * @param `p_queue` a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` is wait destory
 */

void destoryQueue(_3dQueue *p_queue) {
  free(p_queue->rear);
  free(p_queue);
  p_queue = NULL;
}

/**
 * # clear all element in `QUEUE`
 *
 * @param a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` will be handled
 */

void clearQueue(_3dQueue *p_queue) {
  p_queue->front = p_queue->rear[0];
  p_queue->length = 0;
}

/**
 * # Get `QUEUE` current length
 *
 * @param a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` is wait {function} fetch
 * @return current `QUEUE` {length}
 */

int queueLength(_3dQueue *p_queue) {
  return p_queue->length;
}

/**
 * # Get current capcity of this `QUEUE`
 *
 * @param a pointer that point to the address of `QUEUE`,
 *        which `QUEUE` is wait {function} fetch containment
 * @return current capcity of this `QUEUE`
 */

int queueSize(_3dQueue *p_queue) {
  return p_queue->size;
}

/**
 * # Check `QUEUE` is empty or not
 *
 * @param a pointer that point to the address of `QUEUE`, which `QUEUE`
 *        is wait {function} check.
 * @return if `QUEUE` is empty return TRUE, else return FALSE
 */

int isEmpty(_3dQueue *p_queue) {
  return p_queue->length == 0 ? TRUE : FALSE;
}

/**
 * # Fetch current head element of this `QUEUE`
 *
 * @param `p_queue` a pointer that point to the address of `QUEUE`,
 *        whih `QUEUE` is wait fetch head element
 * @param `p_elem` a pointer that point to the address of memory space,
 *         that space use for receiving head element from `QUEUE`
 * @return new head element position(Zero-based numbering,
 *         implying index-numbers count from 0)
 */

int queueHead(_3dQueue *p_queue, innerElem **p_elem) {
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
 */

int enterQueue(_3dQueue *p_queue, innerElem *p_elem) {
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
 *        , that space use for receiving leaved element from `QUEUE`
 * @return {length} if element successful leave `QUEUE` return the \
 *         length of current `QUEUE`(leave one head elemment),
 *         else return FALSE
 */

int leaveQueue(_3dQueue *p_queue, innerElem **p_elem) {
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

void traverseQueue(_3dQueue *p_queue, void(*func)(innerElem *p_elem)) {
  int idx = 0;
  //`QUEUE` front to `QUEUE` rear
  /*
  for (idx = --p_queue->length; idx >= 0; idx--) {
    func(p_queue->rear[idx]);
  }
  */
  // `QUEUE` rear to `QUEUE` front
  for (idx = 0; idx < p_queue->length; ++idx) {
    func(p_queue->rear[idx]);
  }
}

/**
 * # A simple callback{function} for traverse `QUEUE`
 *   print inner element value
 *
 * @param `p_elem` a {pointer} that point to the addess of element,
 *        which element is wait to handle
 */

void printElemValue(innerElem *p_elem) {
  printf("(%d,%d,%d)", (*p_elem).x, p_elem->y, p_elem->z);
  printf("\n");
}

/**
 * # Second callback{function} use for traverse `QUEUE`,
 *   increse inner elemment value
 *
 * @param `p_elem` a {pointer} that point to the addess of element,
 *        which element is wait to handle
 */

void incrElemValue(innerElem p_elem[]) {
  (*p_elem).x += 1;
  (*p_elem).y += 1;
  (*p_elem).z += 1;
}
