/**
 * @file q.h
 *
 * @description A fast queue implementation for pre-allocated entries.
 *
 * @note The function names that end in -S stand for "synchronized". These
 *       first lock the queue, before they do their thing, and unlock it
 *       afterwards. The functions that end in -U stand for "unsynchronized"
 *       and simply access the queue directly. Note that these functions may
 *       still, under water, lock or unlock the queue as they see fit.
 *
 * Example usage:
 *
 *   1a. Create a new queue dynamically:
 *
 *       <pre> Q q = Q_create(); </pre>
 *
 *   1b. Or statically:
 *
 *       <pre>
 *       struct Q_Struct q;
 *       Q_init(&q);
 *       </pre>
 *
 *   2.  Create a struct data type to en/dequeue:
 *
 *       <pre>
 *       typedef struct {
 *         Q_THIS_IS_A_Q_ITEM;
 *         int   my_one_value;
 *         char* my_other_value;
 *       } MyItem;
 *       </pre>
 *
 *   3.  En/dequeue/remove items of this type:
 *
 *       <pre>
 *       MyItem a, *b;
 *       Q_enqS(q, (Q_Item) &a);
 *       b = (MyItem) Q_deqS(q);
 *       </pre>
 *       
 * Copyright (c) 2013 Q-Free Netherlands B.V.
 */


#ifndef _Q_H
#define _Q_H

#include "qthreads.h"

#define Q_LIB_MAJOR            "1"
#define Q_LIB_MINOR            "0"
#define Q_LIB_MAINTENANCE      "3"
#define Q_LIB_DOTTED_VERSION \
  Q_LIB_MAJOR "." Q_LIB_MINOR "." Q_LIB_MAINTENANCE

/**
 * Handy macro to place at the beginning of the struct type that is going to be
 * en/dequeued.
 */
#define Q_THIS_IS_A_Q_ITEM   struct Q_ItemStruct q_item

/**
 * Handy macro to retrieve the size of the overhead that is added to every
 * struct data type that is going to end up in a queue.
 */
#define Q_ITEM_OVERHEAD_SIZE   sizeof(struct Q_ItemStruct)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * This must be the first element in the struct type that is going to be
 * en/dequeued.
 *
 * You can use the #Q_THIS_IS_A_Q_ITEM macro for convenience.
 *
 * <pre>
 * typedef struct {
 *   Q_THIS_IS_A_Q_ITEM;
 *   int   my_first_value;
 *   char* my_other_value;
 * } MyItem;
 * </pre>
 */
typedef struct Q_ItemStruct {
  struct Q_ItemStruct* prev;  /**< Points to the next item. */
  struct Q_ItemStruct* next;  /**< Points to the previous item. */
}* Q_Item;


/**
 * Specifies the time to wait for an item when trying to remove one from the
 * queue.
 *
 * Value range:
 *
 * @li = -1 Block until an item is available
 * @li =  0 Do not block
 * @li >  0 Block for at most this many milliseconds
 */
typedef int Q_Timeout;


#define Q_WAIT   -1  /**< #Q_deqU and #Q_deqS wait until an item is present */
#define Q_NOWAIT  0  /**< #Q_deqU and #Q_deqS return NULL if no item is present */


/**
 * The queue data type.
 */
typedef struct Q_Struct {
  volatile Q_Item   head;       /**< Points to the first element in the queue. */
  volatile Q_Item   tail;       /**< Points to the last element in the queue. */
  QThread_Mutex     mutex;      /**< Mutex to regulate access to the queue. */
  QThread_Semaphore fillCount;  /**< Semaphore to count the number of items in the queue. */
}* Q;


/**
 * A predicate function used in #Q_findU and #Q_findS that should return
 * non-zero if an #item is the one looked for, and zero otherwise.
 *
 * @param[in]     item     The item to analyse.
 * @param[inout]  context  A caller-supplied context.
 *
 * @retval !0 if the #item is the one to find
 * @retval  0 if not
 */
typedef int (*Q_Predicate) (Q_Item item, void* context);


/**
 * Dynamically creates a new queue.
 *
 * @return The newly created queue, which must be destroyed by #Q_destroy.
 */
Q Q_create (void);


/**
 * Destroys a dynamically created queue.
 *
 * @param[inout]  q  The queue to destroy.
 */
void Q_destroy (Q q);


/**
 * Initializes a statically created queue.
 *
 * @param[inout]  q  The queue.
 */
void Q_init (Q q);


/**
 * Finalizes a statically created queue.
 *
 * @param[inout]  q  The queue.
 */
void Q_finit (Q q);


/**
 * Returns the number of items in a queue.
 *
 * @param[in]  q  The queue.
 *
 * @return The number of items in #q.
 */
size_t Q_fillCount (Q q);


/**
 * Locks a queue.
 *
 * @param[inout]  q  The queue to lock.
 */
void Q_lock (Q q);


/**
 * Unlocks a queue.
 *
 * @param[inout]  q  The queue to unlock.
 */
void Q_unlock (Q q);


/**
 * Enqueues an item in a locked queue.
 *
 * @param[inout]  q     The queue to enqueue the item in.
 * @param[in]     item  The item to enqueue.
 */
void Q_enqU (Q q, Q_Item item);


/**
 * Enqueues an item in an unlocked queue.
 *
 * @param[inout]  q     The queue to enqueue the item in.
 * @param[in]     item  The item to enqueue.
 */
void Q_enqS (Q q, Q_Item item);


/**
 * Dequeues an item from a locked queue.
 *
 * Possible values for the #timeout parameter are:
 *
 * @li #Q_WAIT   if the queue is empty, blocks until an item is enqueued.
 * @li #Q_NOWAIT if the queue is empty, returns NULL.
 * @li Any other value is treated as a timeout in milliseconds. The function
 *     blocks until an item is enqueued, or the timeout has expired, in which
 *     case it returns NULL.
 *
 * @param[inout]  q        The queue to dequeu an item from.
 * @param[in]     timeout  The timeout determines the behaviour in case the
 *                         queue is empty.
 *
 * @return The dequeued item, or NULL.
 */
Q_Item Q_deqU (Q q, Q_Timeout timeout);


/**
 * Dequeues an item from an unlocked queue.
 *
 * @see #Q_deqU for a description of the #timeout parameter.
 *
 * @param[inout]  q        The queue to dequeu an item from.
 * @param[in]     timeout  The timeout determines the behaviour in case the
 *                         queue is empty.
 *
 * @return The dequeued item, or NULL.
 */
Q_Item Q_deqS (Q q, Q_Timeout timeout);


/**
 * Removes an item from a locked queue.
 *
 * @param[inout]  q     The queue to remove an item from.
 * @param[inout]  item  The item to remove from the queue.
 */
void Q_remU (Q q, Q_Item item);


/**
 * Removes an item from an unlocked queue.
 *
 * @param[inout]  q     The queue to remove an item from.
 * @param[inout]  item  The item to remove from the queue.
 */
void Q_remS (Q q, Q_Item item);


/**
 * Finds an item in a locked queue.
 *
 * @param[in]     q        The queue to look in.
 * @param[in]     pred     A predicate function that is used to locate the item.
 * @param[inout]  context  A context for #pred.
 *
 * @return The found item, or NULL.
 */
Q_Item Q_findU (Q q, Q_Predicate pred, void *context);


/**
 * Finds an item in an unlocked queue.
 *
 * @param[in]     q        The queue to look in.
 * @param[in]     pred     A predicate function that is used to locate the item.
 * @param[inout]  context  A context for #pred.
 *
 * @return The found item, or NULL.
 */
Q_Item Q_findS (Q q, Q_Predicate pred, void *context);

#ifdef __cplusplus
} /* Close scope of 'extern "C"', declaration which encloses file. */
#endif

#endif /* _Q_H */


