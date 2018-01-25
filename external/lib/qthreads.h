/**
 * @file qthreads.h
 *
 * @brief Q-Threads.
 *
 * Copyright (c) 2011-2014 Q-Free Netherlands B.V.
 */

#ifndef _QTHREADS_H
#define _QTHREADS_H

/** @{ */
/** Version information */

#define QTHREAD_LIB_MAJOR       "1"
#define QTHREAD_LIB_MINOR       "0"
#define QTHREAD_LIB_MAINTENANCE "8"
#define QTHREAD_LIB_DOTTED_VERSION \
  QTHREAD_LIB_MAJOR "." QTHREAD_LIB_MINOR "." QTHREAD_LIB_MAINTENANCE

/** @} */
/** @{ */
/** Return values */

#define QTHREAD_RETURN_OK                    0
#define QTHREAD_RETURN_TIMEOUT               1
#define QTHREAD_RETURN_WOULD_BLOCK           2
#define QTHREAD_RETURN_ERROR                -1
#define QTHREAD_RETURN_ILLEGAL_VERSION      -2

/** @} */
/** @{ */
/** Threads */

#ifdef __cplusplus
extern "C" {
#endif

/** Forward declaration */
typedef struct _QThreadStruct *QThread;

/** Signature for thread function */
typedef void* (*QThread_Function)(void *);

/**
 * Creates a thread and starts it.
 * 
 * @param[out] thread          handle to the created thread
 * @param[in]  threadName      name of the thread
 * @param[in]  threadFunction  function to execute
 * @param[in]  threadData      argument passed to threadFunction
 *
 */ 
int QThread_create(QThread *thread, const char * const threadName, QThread_Function threadFunction, void * threadData);

/** 
 * Waits until the thread exits, and collects its return value.
 *
 * @param[in]   thread         the thread to wait on
 * @param[out]  threadReturn   optionally, will contain the threads' return value 
 *
 */
int QThread_join(QThread thread, void **threadReturn);

/**
 * Returns for a thread a handle to itself 
 */
QThread QThread_self(void);

/**
 * Sleeps for a specified timeout.
 *
 * @param[in] timeout  The timeout in milliseconds
 */
void QThread_sleep(unsigned int timeout);

/** @} */
/** @{ */
/** Mutex */

/** Forward declaration */
typedef struct _QThread_MutexStruct *QThread_Mutex;

/**
 * Creates a unlocked mutex 
 * 
 * @param[out] mutex  The created mutex
 * 
 * On error the returned mutex will be NULL.
 */
int QThread_Mutex_create(QThread_Mutex *mutex);

/**
 * Destroys a mutex
 *
 * @param[in, out] mutex  The mutex to destroy
 */
int QThread_Mutex_destroy(QThread_Mutex *mutex);


/**
 * Tries to acquire the mutex, blocks until it can be acquired
 *
 * @param[in, out] mutex  The mutex to acquire
 * 
 * Only on return success the mutex has been acquired
 */
int QThread_Mutex_P(QThread_Mutex mutex);


/**
 * Releases the mutex.
 *
 * @param[in, out] mutex  The mutex to release
 */
int QThread_Mutex_V(QThread_Mutex mutex);

/** @} */
/** @{ */
/** Semaphores */

/** Forward declaration */
typedef struct _QThread_SemaphoreStruct *QThread_Semaphore;

/**
 * Creates a semaphore with a given initial count
 * 
 * @param[out] semaphore     The created semaphore
 * @param[in]  initialCount  The initial count
 *
 * On error the returned semaphore will be NULL.
 */

int QThread_Semaphore_create(QThread_Semaphore *semaphore, unsigned int initialCount);

/**
 * Destroys a semaphore
 *
 * @param[in,out] semaphore  The semaphore to destroy
 */
int QThread_Semaphore_destroy(QThread_Semaphore *semaphore);

/**
 * Tries to pass the semaphore, blocks until the semaphore can be passed.
 * 
 * @param[in, out] semaphore  The semaphore to pass
 *
 * On return success the semaphore has been passed
 */
int QThread_Semaphore_wait(QThread_Semaphore semaphore);

/**
 * Tries to pass the semaphore, but do not block when it cannot pass.
 *
 * @param[in, out] semaphore  The semaphore to try and pass
 *
 * On return success the semaphore has been passed
 * On return timeout the semaphore could not be passed without waiting
 */
int QThread_Semaphore_trywait(QThread_Semaphore semaphore);

/**
 * Tries to pass the semaphore within a specified timeout. 
 * Blocks till it can pass, or the timeout has elapsed.
 *
 * @param[in, out] semaphore  The semaphore to try and pass
 * @param[in]      timeout    The maximum waiting time in milliseconds
 *
 * On return success the semaphore has been passed
 * On return timeout the semaphore could not be passed without waiting longer
 *   than the timeout.
 */

int QThread_Semaphore_timedwait(QThread_Semaphore semaphore, unsigned int timeout);

/**
 * Signals the semaphore, allowing another thread to pass the semaphore.
 *
 * @param[in, out] semaphore  The semaphore to signal
 */
int QThread_Semaphore_post(QThread_Semaphore semaphore);

/**
 * Returns (an approximate) count of the semaphore
 * 
 * @param[in]  semaphore  The semaphore to retrieve the count for
 * @param[out] value      The (approximate) count of the semaphore.
 */
int QThread_Semaphore_value(QThread_Semaphore semaphore, unsigned int *value);

/** @} */
/** @{ */
/** Initialization and finalization */

/** 
 * Returns library version information and description.
 *
 * @param[in, out] major        The major version number of the library
 * @param[in, out] minor        The minor version number of the library
 * @param[in, out] maintenance  The maintenance version number of the library
 * @param[in, out] description  The description string of the library
 * @retval The dotted version, plus description and date and time of build.
 */
const char * const QThread_getVersion(
    const char * * const major,
    const char * * const minor,
    const char * * const maintenance,
    const char * * const description);
/**
 * Initializes the Q-Thread library.
 */
#define QThread_initialize() QThread_initializeVersion(QTHREAD_LIB_DOTTED_VERSION)
int QThread_initializeVersion(const char * const version);

/**
 * Finalizes and cleans up the Q-Thread library.
 */
void QThread_finalize(void);

#ifdef __cplusplus
} /* Close scope of 'extern "C"', declaration which encloses file. */
#endif

#endif /* _QTHREADS_H */
