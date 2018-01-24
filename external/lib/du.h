 /*-----------------------------------------------------------------------------
* FILE:
*   du.h
*
* DESCRIPTION:
*   Include file for the Dacolian Utilities Module (DU-module).
*
* Compile time available variation points:
*   DU_TIME_LOGGING_ENABLE:
*    Define to include time logging functionality. (+TL)
*   DU_MEMORY_MANAGER: 
*    Define to include Du-memory manager. All standard memory allocation
*    routines will be remapped to Du-alternatives. Routine replaced are:
*    calloc(), malloc(), strdup(), free(), and realloc(). (+M)
*   DU_ALT_MEM_NO_MEMORY_TRACE:
*    Define to include memory trace functionality into the DU-memory manager.
*    Will only have effect if also DU_MEMORY_MANAGER is defined. (+MT)
*   DU_DEBUG_ENABLE:
*    Define to include verbosity functionality. (+D)                  
*
* MODIFICATION HISTORY:
*  2015-12-02: Solved wrong newline in printing help in case argument explanation
*              reached exactly position 80 (cmd box width). 8.3.3 [JS]
*  2015-10-20: Solved overflow problem in DuSerializeObjectToBytes() 8.3.2 [MTB]
*  2015-07-01: Added SerializeObject compression routines 8.3.0 [MTB]
*  2014-11-06: Added timing functions 8.2.0
*  2014-03-18: Correct error code return value 8.1.3 [JN]
*  2013-12-16: Increased version to 8.0.0 to have unique not already issued
*              version number 8.0.0 [JN]
*  2013-12-13: Version increase to signal various updates (6.0.0) [JN]
*  2012-08-03: correct bug in unused graph function 
*              MarkReachableOutVertices() (5.1.3) [JN]
*  2012-06-01: correct small memory lead in du_altmem.c not closing a file
*              in debugging mode (5.1.2) [JN]
*  2012-02-22: Correct memory leak in memory traches 5.1.1 (jn)
*  2012-01-18: Added support for loading env-variables from a string 5.1.0 (jn)
*  2011-07-25: Added DU_DEBUG_ENABLE 5.0.7) (jn)
*  2009-02-19: Made thread-safe (5.0.4) (wh)
*  2008-12-17: Ported to the DSP platform (jb)
*  2008-03-06: Ported to ppc603 (5.0.2) (jb)
*  2008-03-06: Added DuListInsertElement function (5.0.1) (wh)
*  2007-12-11: Added export of env database, initialization options (5.0.0) (jn)
*  2007-06-19: Fixed bug in md5 bitshift algorithm for 64 bit (4.0.8)
*  2007-06-18: Ported to 64 bit linux (4.0.7)
*  2007-06-05: Added macro enabled time logging (4.0.6)
*  2007-04-26: Ported to 64 bit platform (4.0.5)
*  2007-04-17: Fixed possible uninitialized value in DuMemPoolCreate (4.0.4)
*  2007-02-27: Added command line arguments function CheckArgString (4.0.3)
*  2007-02-27: Update memory pooling interface (dynamic block size) (4.0.2)
*  2007-02-19: Fixed memory clearing bug in memory pooling (4.0.1)
*  2007-02-24  Added memory pooling (jb)      (4.0.0)
*  2006-11-01: correct bug in CheckArgStrings() (jn) (3.1.3)
*  2006-10-06: improved layout of mem-usage print (mtb) (3.1.2)
*  2006-10-06: correct memory leak in CheckArgLongs(), CheckArgInts(), and
*              CheckArgFloats (js) and added out of memory tests (jn) (3.1.1)
*  2006-08-31: added int DuEnvSaveTextToStream(FILE *f) (jn) (3.1.0)
*  2006-06-06: corrected memory allocation test in du_files (3.0.6)
*  2006-06-06: correct indirection buf in Callstack routines (3.0.5)
*  2006-04-25: Added Callstack info to memory allocation routines. (3.0.4).
*  2006-04-21: Added initialization with special value for mem_Smalloc() (3.0.3).
*  2006-03-31: correct bug with reading of comment lines on last line (3.0.2) 
*  2006-03-19: included <string.h> to make sure it is not included after du.h
*              and will results in compiler errors in debug mode (3.0.1)
*  2006-03-10: added DuPath# routines. 
*  2006-02-09: Clean separation of platform dependent/independent code
*              in Ds and Du (3.0.0)
*  2006-02-03: Changed interface to DuEnvGetString() and DuEnvSetString() to
*              const char* instead of char* (2.1.1).
*  2006-01-18: Added Base64/SerializeObject functionality, changed some int 
*              types to size_t, where strings are involved. Changed some 
*              others from int to long (2.1.0).
*  2006-01-04: removed all DacoStd stuff into Du (nijh) 2.0.0
*  2005-09-13: Added DuArrayCopy
*  2005-03-08: Added mem_Sprint definition if in NDEBUG mode (nijh.)
*  2004-12-22: Added DuAsciiIs* calls and DuAsciiTo* calls for ctype
*              emulation.
*  2002-09-16: Creation.
*
* COPYRIGHT NOTICE:
*  Copyright (c) 1998-2011  DACOLIAN B.V.
*  All rights reserved
*----------------------------------------------------------------------------*/

#ifndef  _DU_H_
#define  _DU_H_


/*-----------------------------------------------------------------------------
 * Macros:
 *   DU_SUPPORT_OBSOLETE
 *
 * DESCRIPTION:
 *   This define can be turned on and off to specify whether or not obsolete
 *   routines should be supported by Du. If this variable is turned of, an
 *   application that uses Du should be compliant with the new Du standard
 *   (introduced in version 2.0.0).
 *---------------------------------------------------------------------------*/
 
#define DU_SUPPORT_OBSOLETE

/*-----------------------------------------------------------------------------
 * Platform independent includes. We assume these header files exist on every
 * platform until proved differently. In the latter case we have to move the
 * header file to the platform specific includes section.
 *
 * stdarg.h : required for variable argument lists.
 * stdio.h  : required for the file stuff.
 * math.h   : required for the rounding routines.
 * stdlib.h : required, since standard malloc stuff should be defined before
 *            we redefine these routines.
 *---------------------------------------------------------------------------*/

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#include "ds.h"

/*-----------------------------------------------------------------------------
* DU_LIB_MAJOR, DU_LIB_MINOR, DU_LIB_MAINTENANCE, DU_LIB_DOTTED_VERSION
*
* Description:
*  These defines give the current version of this library. The version numbers 
*  of the library and include file must match for the major and minor part of
*  the version number. Any mismatch will result in an error during the 
*  DuInstall() call.
*----------------------------------------------------------------------------*/
#define DU_LIB_MAJOR       "8"
#define DU_LIB_MINOR       "3"
#define DU_LIB_MAINTENANCE "7"
#define DU_LIB_DOTTED_VERSION \
  DU_LIB_MAJOR "." DU_LIB_MINOR "." DU_LIB_MAINTENANCE


#ifdef __cplusplus
extern "C" {
#endif




/*-----------------------------------------------------------------------------
 * Library return codes
 *----------------------------------------------------------------------------*/
#define DU_RETURN_OK                                0
#define DU_RETURN_OUT_OF_MEMORY                     1
#define DU_RETURN_ILLEGAL_FILENAME                  2
#define DU_RETURN_CANNOT_OPEN_FILE                  3
#define DU_RETURN_ILLEGAL_VARIABLE_NAME             4
#define DU_RETURN_UNDEFINED_VARIABLE                5
#define DU_RETURN_ILLEGAL_TYPE                      6
#define DU_RETURN_ILLEGAL_ENV_FILE                  7
#define DU_RETURN_ILLEGAL_VERSION                   8
#define DU_RETURN_NOT_INSTALLED                     9
#define DU_RETURN_ILLEGAL_NULL_POINTER             10
#define DU_RETURN_ILLEGAL_HASH_TABLE               11
#define DU_RETURN_ILLEGAL_KEY                      12
#define DU_RETURN_EMPTY_LIST                       13
#define DU_RETURN_NO_NEXT                          14
#define DU_RETURN_NO_PREV                          15
#define DU_RETURN_NOT_FOUND                        16
#define DU_RETURN_ILLEGAL_INDEX                    17
#define DU_RETURN_CALLBACK_ERROR                   18
#define DU_RETURN_DIFFERENT_GRAPHS                 29
#define DU_RETURN_DUPLICATE_EDGE                   20
#define DU_RETURN_ILLEGAL_SIZE                     21
#define DU_RETURN_ILLEGAL_SERIALIZE_OBJECT         22
#define DU_RETURN_NO_MORE_DATA                     23
#define DU_RETURN_ILLEGAL_MESSAGE                  24
#define DU_RETURN_ILLEGAL_ARGUMENT                 25
#define DU_RETURN_ILLEGAL_POINTER                  26
#define DU_RETURN_MEMPOOL_OVERFLOW                 27
#define DU_RETURN_MEMPOOL_ALREADY_FREE             28
#define DU_RETURN_INCOMPATIBLE_VERSION             29



#define DU_RETURN_CLAP_OK                         DU_RETURN_OK
#define DU_RETURN_CLAP_HELP                       25
#define DU_RETURN_CLAP_ERROR                      26
#define DU_RETURN_CLAP_VERSION                    27

#define DU_RETURN_INTERNAL_ERROR                  28
#define DU_RETURN_ILLEGAL_FORMAT                  29

 /*------------------------------------------------------------------------------
 * DEFINE:
 *   ENV_VARIABLE_TYPE_BYTE, ENV_VARIABLE_TYPE_INT, ENV_VARIABLE_TYPE_LONG,
 *   ENV_VARIABLE_TYPE_FLOAT, ENV_VARIABLE_TYPE_DOUBLE, 
 *   ENV_VARIABLE_TYPE_STRING
 *
 * DESCRIPTION:
 *   Types of environment variables.
 *---------------------------------------------------------------------------*/

#define ENV_VARIABLE_TYPE_BYTE   1
#define ENV_VARIABLE_TYPE_INT    2
#define ENV_VARIABLE_TYPE_LONG   3
#define ENV_VARIABLE_TYPE_FLOAT  4
#define ENV_VARIABLE_TYPE_DOUBLE 5
#define ENV_VARIABLE_TYPE_STRING 6

/* Functions like the ones in <ctype.h> that are not affected by locale. */
typedef enum {
  DU_ASCII_ALNUM  = 1 << 0,
  DU_ASCII_ALPHA  = 1 << 1,
  DU_ASCII_CNTRL  = 1 << 2,
  DU_ASCII_DIGIT  = 1 << 3,
  DU_ASCII_GRAPH  = 1 << 4,
  DU_ASCII_LOWER  = 1 << 5,
  DU_ASCII_PRINT  = 1 << 6,
  DU_ASCII_PUNCT  = 1 << 7,
  DU_ASCII_SPACE  = 1 << 8,
  DU_ASCII_UPPER  = 1 << 9,
  DU_ASCII_XDIGIT = 1 << 10
} DuAsciiType;




/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuArray routines and defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * DuArray
 *
 * Description:
 *   Data type that is used to store arrays of arbitrary structures. Array
 *   indexing should only be done using the DuArrayIndex() macro !!! 
 *   Array indexing should only be done when the 'size' field is larger
 *   than zero. Note that 'size' == 0 does not imply 'data' == NULL.
 *
 * Fields:
 *    data : The buffer that stores the array values.
 *    size : The number of elements in the array.
 *---------------------------------------------------------------------------*/

typedef struct _DuArrayStruct
{
   void *data;
   long size;
} DuArrayStruct, *DuArray;


/*-----------------------------------------------------------------------------
 * DuArrayIndex
 *
 * Description:
 *   This macro is used for array indexing (reading and writing) the DuArray 
 *  'array'.
 *
 * Parameters:
 *    e_type : The element type.
 *     array : The DuArray.
 *     index : The array index. 
 *
 * Example:
 *
 * typedef struct _MyStruct 
 * {
 *   int i;
 *   int j;
 * } MyStruct;
 *
 * MyStruct val;
 * DuArray array;
 * 
 * DuArrayIndex(MyStruct, array, 3) = val;
 * val = DuArrayIndex(MyStruct, array, 4);
 *---------------------------------------------------------------------------*/
#define DuArrayIndex(e_type,array,index) \
    (((e_type *) ((array)->data)) [(index)])



/*-----------------------------------------------------------------------------
 * DuArrayCreate()
 *
 * Description:
 *   Creates a new DuArray of size 0.
 *
 * Arguments:
 *   element_size : The size of each element in bytes.
 *          array : Returns the created DuArray.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayCreate (unsigned int element_size, DuArray *array);

/*-----------------------------------------------------------------------------
 * DuArrayCreateSized()
 *
 * Description:
 *   Creates a new DuArray of a specified size. The elements in the the array 
 *   are not initialized.
 *
 * Arguments:
 *   element_size : The size of each element in bytes.
 *           size : The desired number of elements in the DuArray.
 *          array : Returns the created DuArray.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_SIZE, DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayCreateSized (unsigned int element_size, long size, 
                               DuArray *array);

/*-----------------------------------------------------------------------------
 * DuArrayCopy()
 *
 * Description:
 *   Makes a copy of a DuArray.
 *
 * Arguments:
 *       src : The DuArray to be copied
 *     array : Returns the copied DuArray.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayCopy (DuArray src, DuArray *dst);

/*-----------------------------------------------------------------------------
 * DuArraySetSize()
 *
 * Description:
 *   Sets the size of the array, expanding it if necessary. If the new size
 *   is larger than the original size the new elements are added to the end
 *   of the array and are uninitialized. If the new size is smaller than the
 *   original size, the last elements are removed from the array.
 *
 * Arguments:
 *   array : The DuArray..
 *    size : The new size of the DuArray.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_SIZE, DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArraySetSize (DuArray array, long size);


/*-----------------------------------------------------------------------------
 * DuArrayDestroy()
 *
 * Description:
 *   Frees the memory allocated for the DuArray.
 *
 * Arguments:
 *     array : The DuArray.
 *---------------------------------------------------------------------------*/
extern void DuArrayDestroy (DuArray array);


/*-----------------------------------------------------------------------------
 * DuArrayInsertElements()
 *
 * Description:
 *   Inserts 'nr_elts' elements into the DuArray at the given index. Note that
 *   this makes the array 'nr_elts' elements larger and all elements in the 
 *   original array starting from 'index' are shifted 'nr_elts' positions to 
 *   the right.
 *
 * Arguments:
 *   array : The DuArray.
 *   index : The index to place the elements at.
 *    data : A pointer to the elements to insert.
 * nr_elts : The number of elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_INDEX, DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayInsertElements (DuArray array, long index, void *data, 
                                  long nr_elts);

/*-----------------------------------------------------------------------------
 * DuArrayInsertElement()
 *
 * Description:
 *   Inserts a single element into the DuArray at the given index. Note that
 *   this makes the array one element larger and all elements in the original
 *   array starting from 'index' are shifted one position to the right.
 *
 * Arguments:
 *   array : The DuArray.
 *   index : The index to place the elements at.
 *    data : A pointer to the elements to insert.
 * nr_elts : The number of elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_INDEX, DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayInsertElement (DuArray array, long index, void *data);

/*-----------------------------------------------------------------------------
 * DuArrayAppendElements()
 *
 * Description:
 *   Like DuArrayInsertElements(), but now the new elements are added at the
 *   end of the array (starting at index = array->nr_elts-1).
 *
 * Arguments:
 *   array : The DuArray.
 *    data : A pointer to the elements to insert.
 * nr_elts : The number of elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayAppendElements (DuArray array, void *data, long nr_elts);


/*-----------------------------------------------------------------------------
 * DuArrayAppendElement()
 *
 * Description:
 *   Like DuArrayInsertElement(), but now the new element is added at the
 *   end of the array (at index = array->nr_elts-1).
 *
 * Arguments:
 *   array : The DuArray.
 *    data : A pointer to the elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayAppendElement (DuArray array, void *data);

/*-----------------------------------------------------------------------------
 * DuArrayPrependElements()
 *
 * Description:
 *   Like DuArrayInsertElements(), but now the new elements are added at the
 *   beginning of the array (starting at index = 0).
 *
 * Arguments:
 *   array : The DuArray.
 *    data : A pointer to the elements to insert.
 * nr_elts : The number of elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayPrependElements (DuArray array, void *data, long nr_elts);

/*-----------------------------------------------------------------------------
 * DuArrayPrependElement()
 *
 * Description:
 *   Like DuArrayInsertElement(), but now the new element is added at the
 *   beginning of the array (starting at index = 0).
 *
 * Arguments:
 *   array : The DuArray.
 *    data : A pointer to the elements to insert.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *---------------------------------------------------------------------------*/
extern int DuArrayPrependElement (DuArray array, void *data);

/*-----------------------------------------------------------------------------
 * DuArrayRemoveIndex()
 *
 * Description:
 *   Removes the element at the given index from the DuArray. The following
 *   elements are shifted to the left one place and the size of the resulting
 *   array will be one smaller.
 *
 * Arguments:
 *   array : The DuArray.
 *   index : The index of the element to remove.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_INDEX. 
 *---------------------------------------------------------------------------*/
extern int DuArrayRemoveIndex (DuArray array, long index);

/*-----------------------------------------------------------------------------
 * DuArrayRemoveIndexFast()
 *
 * Description:
 *   Removes the element at the given index from the DuArray. The last element
 *   in the array is used to fill in the space. The size of the resulting
 *   array will be one smaller than the size of the original array. Note that 
 *   this routine does not preserve the order of the elements in the DuArray 
 *   but it is faster than the DuArrayRemoveIndex() routine.
 *
 * Arguments:
 *   array : The DuArray.
 *   index : The index of the element to remove.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_INDEX. 
 *---------------------------------------------------------------------------*/
extern int DuArrayRemoveIndexFast (DuArray array, long index);




/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuPtrArray routines and defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
 * DuPtrArray
 *
 * Description:
 *   Data type that is used to store arrays of arbitrary structures. Array
 *   indexing should only be done using the DuArrayIndex() macro !!! 
 *   Array indexing should only be done when the 'size' field is larger
 *   than zero. Note that 'size' == 0 does not imply 'data' == NULL.
 *
 * Fields:
 *    data : The buffer that stores the pointers.
 *    size : The number of elements in the array.
 *---------------------------------------------------------------------------*/

typedef struct _DuPtrArrayStruct
{
   void **data;
   long size;
} DuPtrArrayStruct, *DuPtrArray;


/*-----------------------------------------------------------------------------
 * The DuPtrArray is a pointer array. The routines are similar to the DuArray
 * routines and are therefor not described.
 *---------------------------------------------------------------------------*/

#define DuPtrArrayIndex(array,index) ((array)->data[(index)])


extern int DuPtrArrayCreate (DuPtrArray *array);
extern int DuPtrArrayCreateSized (long size, DuPtrArray *array);
extern int DuPtrArraySetSize (DuPtrArray array, long size);
extern void DuPtrArrayDestroy (DuPtrArray array);
extern int DuPtrArrayCopy (DuPtrArray src, DuPtrArray *dst);

extern int DuPtrArrayInsertElements (DuPtrArray array, long index, 
                                     void **ptrs, long nr_ptrs);
extern int DuPtrArrayInsertElement (DuPtrArray array, long index, void *ptr);
extern int DuPtrArrayAppendElements (DuPtrArray array, void **ptrs, 
                                     long nr_ptrs);
extern int DuPtrArrayAppendElement (DuPtrArray array, void *ptr);
extern int DuPtrArrayPrependElements (DuPtrArray array, void **ptrs, 
                                      long nr_ptrs);
extern int DuPtrArrayPrependElement (DuPtrArray array, void *ptr);
extern int DuPtrArrayRemoveIndex (DuPtrArray array, long index);
extern int DuPtrArrayRemoveIndexFast (DuPtrArray array, long index);
extern int DuPtrArrayAppend (DuPtrArray array_dst, DuPtrArray array_src);
extern int DuPtrArrayMerge (DuPtrArray array1, DuPtrArray array2,
                              DuPtrArray *array);
extern int DuPtrArrayMultiply (DuPtrArray array1, DuPtrArray array2, 
                               DuPtrArray *array);

/*-----------------------------------------------------------------------------
 * DestroyPtrPtrArray
 *
 * Description:
 *   Destroy a DuPtrArray of DuPtrArray's. 
 *
 * Arguments:
 *     array: The DuPtrArray to be destroyed.
 *---------------------------------------------------------------------------*/
extern void DuPtrPtrArrayDestroy (DuPtrArray array);


/*-----------------------------------------------------------------------------
 * DuPtrArrayRemoveElement()
 *
 * Description:
 *   Removes the first occurrence of 'ptr' from the DuPtrArray. The following
 *   elements are shifted to the left one place and the size of the resulting
 *   array will be one smaller.
 *
 * Arguments:
 *   array : The DuArray.
 *     ptr : The element to remove.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_NOT_FOUND. 
 *---------------------------------------------------------------------------*/
extern int DuPtrArrayRemoveElement (DuPtrArray array, void *ptr);

extern int DuPtrArrayRemoveElementFast (DuPtrArray array, void *ptr);

/*-----------------------------------------------------------------------------
 * DuPtrArrayCheckPresence()
 *
 * Description:
 *   Tests if 'ptr' occurs in the DuPtrArray. If so, 'index' returns the  
 *   position of the the first occurrence of 'ptr'. If not, index returns -1.
 *
 * Arguments:
 *   array : The DuArray.
 *   index : The find position or -1 if not present.
 *---------------------------------------------------------------------------*/
extern void DuPtrArrayCheckPresence (DuPtrArray array, void *ptr, 
                                     long *index);











/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Graph functions and defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

#define DU_PATH_CALLBACK_RETURN_OK               0
#define DU_PATH_CALLBACK_RETURN_OUT_OF_MEMORY    1
#define DU_PATH_CALLBACK_RETURN_TERMINATE        2
#define DU_PATH_CALLBACK_RETURN_ERROR            3
#define DU_PATH_CALLBACK_RETURN_SKIP             5

typedef struct _DuGraphStruct *DuGraph;
typedef struct _DuGraphVertexStruct *DuGraphVertex;
typedef struct _DuGraphEdgeStruct *DuGraphEdge;

/*-----------------------------------------------------------------------------
 * DuGraphEdgeTestCallback
 *
 * Description:
 *   Edge test callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphEdgeTestCallback) (DuGraphEdge edge, void *data_ptr);

/*-----------------------------------------------------------------------------
 * DuGraphVertexTestCallback
 *
 * Description:
 *   Vertex test callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphVertexTestCallback) (DuGraphVertex vertex, 
                                          void *data_ptr);


/*-----------------------------------------------------------------------------
 * DuGraphPathExtendCallback
 *
 * Description:
 *   Edge test callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphPathExtendCallback) (DuGraphEdge edge, void *data_ptr);

/*-----------------------------------------------------------------------------
 * DuGraphPathReduceCallback
 *
 * Description:
 *   Edge test callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphPathReduceCallback) (DuGraphEdge edge, void *data_ptr);

/*-----------------------------------------------------------------------------
 * DuGraphVertexPathCallback
 *
 * Description:
 *   Vertex path callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphVertexPathCallback) (long nr_vertices, 
                                          DuGraphVertex *vertices,
                                          void *data_ptr);


/*-----------------------------------------------------------------------------
 * DuGraphEdgePathCallback
 *
 * Description:
 *   Vertex path callback routine.
 *----------------------------------------------------------------------------*/
typedef int (*DuGraphEdgePathCallback) (long nr_edges, 
                                        DuGraphEdge *edges,
                                        void *data_ptr);

extern int DuGraphCreate (DuGraph *graph);

extern int DuGraphAddVertex (DuGraph graph,
                             void *data,
                             DuGraphVertex *vertex);

extern int DuGraphAddEdge (DuGraphVertex vertex_from, 
                              DuGraphVertex vertex_to,
                              void *data,
                              DuGraphEdge *edge);
extern int DuGraphCheckEdge (DuGraphVertex vertex_from, 
                              DuGraphVertex vertex_to,
                              DuGraphEdge *edge);

extern void DuGraphRemoveEdge (DuGraphEdge edge);

extern void DuGraphRemoveVertex (DuGraphVertex vertex);

extern void DuGraphGetVertices (DuGraph graph,
                                long *nr_vertices,
                                DuGraphVertex **vertices);

extern void DuGraphGetEdges (DuGraph graph,
                             long *nr_edges,
                             DuGraphEdge **edges);

extern void DuGraphGetEdgeDataOrg (DuGraphEdge edge,
								   void **edge_data);

#define DuGraphGetEdgeData(edge,edge_data) DuGraphGetEdgeDataOrg(edge,(void**)edge_data)

extern void DuGraphGetVertexDataOrg (DuGraphVertex vertex,
								     void **vertex_data);

#define DuGraphGetVertexData(vertex,vertex_data) DuGraphGetVertexDataOrg(vertex,(void**)vertex_data)

extern void DuGraphGetInList (DuGraphVertex vertex, 
                              long *nr_in,
                              DuGraphVertex **in_vertices, 
                              DuGraphEdge **in_edges);

extern void DuGraphGetOutList (DuGraphVertex vertex, 
                               long *nr_out,
                               DuGraphVertex **out_vertices, 
                               DuGraphEdge **out_edges);

extern void DuGraphDestroy (DuGraph graph);

extern int DuGraphIterateEdgePaths (DuGraphVertex vertex_from, 
                                    DuGraphVertex vertex_to,
                                    DuGraphPathExtendCallback extend_fun,
                                    DuGraphPathReduceCallback reduce_fun,
                                    DuGraphEdgePathCallback callback,
                                    void *call_back_data);

extern int DuGraphIterateVertexPathsBreathFirst (DuGraphVertex vertex_from, 
                                                 DuGraphVertex vertex_to,
                                                 DuGraphVertexTestCallback vertex_test,
                                                 DuGraphEdgeTestCallback edge_test,
                                                 DuGraphVertexPathCallback callback,
                                                 void *call_back_data);

extern int DuGraphIterateEdgePathsBreathFirst (DuGraphVertex vertex_from, 
                                               DuGraphVertex vertex_to,
                                               DuGraphVertexTestCallback vertex_test,
                                               DuGraphEdgeTestCallback edge_test,
                                               DuGraphEdgePathCallback callback,
                                               void *call_back_data);



#if 0
/*-----------------------------------------------------------------------------
 * DijkstrasShortesPath()
 *
 * Description:
 *   Determines the shortest path from vertex x to vertex y. If y is reachable
 *   from x, the vertices (including points x and y) are stored in the buffer
 *   buf and the number of vertices on the path is stored in nr_vertices. The
 *   user is responsible for allocating the buffer. The size of the buffer
 *   should be at least equal to the number of vertices in the graph. If y is
 *   not reachable from x, nr_vertices is set to 0.
 *
 * Arguments:
 *       graph : The graph.
 *           x : The ID of the source vertex.
 *           y : The ID of the target vertex.
 *         buf : The buffer in which the path (array of vertex IDs) is
 *               returend.
 * nr_vertices : The number of vertices in the path.
 *
 *---------------------------------------------------------------------------*/
void DijkstrasShortesPath (Graph *g, int x, int y, int buf[],
						   int *nr_vertices);


#endif






/*-----------------------------------------------------------------------------
 * DuGetVersion()
 *
 * Description:
 *   Delivers version information and compile date information of this library.
 *
 * Arguments:
 *         major : returns the major release number if not NULL.
 *         minor : returns the minor release number if not NULL.
 *   maintenance : returns the maintenance release number if not NULL.
 *   description : returns an informal description about the font library if
 *                 not NULL.
 *
 * Return value:
 *   pointer to a '\0' terminated character string that contains both the
 *   version number and compilation date and time.
 *---------------------------------------------------------------------------*/
extern const char *DuGetVersion(const char **major,
                                const char **minor,
                                const char **maintenance,
                                const char **description);













/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuList stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * DuList
 *
 * Description:
 *   Definition of the hidden data type DuList. This is a double linked list
 *   that can be used to store all kind of data elements.
 *----------------------------------------------------------------------------*/
typedef struct _DuListStruct *DuList;

/*-----------------------------------------------------------------------------
 * DuListIterator
 *
 * Description:
 *   Type definition of an iterator routine. Iterator routines are used by the
 *   DuListIterate() routine to perform an operation for all elements in a 
 *   DuList. The context variable in the iterator routine is used to share
 *   arbitrary data between the caller and the iterator routine.
 *
 * Example:
 * 
 *    typedef struct _MyContext
 *    {
 *      int cnt;
 *    } MyContext;
 * 
 *    void iterator (void *data, void *context)
 *    {
 *      MyContext *my_context;
 * 
 *      my_context = (MyContext *) context;
 *      printf ("list[%d] = %p\n", my_context->cnt, data);
 *      my_context->cnt++;
 *    }
 *
 *    void main (void)
 *    {
 *       MyContext context;
 * 
 *       context.cnt = 0;
 *       DuListIterate (lst, iterator, &context);
 *    }
 *
 *----------------------------------------------------------------------------*/
typedef void (*DuListIterator) (void *data, void *context);


/*-----------------------------------------------------------------------------
 * DuListComparator
 *
 * Description:
 *   Type definition of a comparator for DuLists. Comparators are used by 
 *   routines (like DuListRemoveElement()) that need to compare data objects.
 *   A comparator defines an order between two data objects 'data1' and 
 *   'data2'. It should return:
 *     -1 if 'data1' is smaller than 'data2'
 *      0 if 'data1' is equal to 'data2'
 *     +1 if 'data1' is larger than 'data2'
 *
 *   For example, a comparator that can be used for a list of strings is 
 *   defined by:
 *
 *   int EqualStrings (void *data1, void *data2)
 *   {
 *     return (strcmp (data1, data2));
 *   }
 *
 *   Since the strcmp() routine compares strings and returns exactly the 
 *   values described above.
 *----------------------------------------------------------------------------*/
typedef int (*DuListComparator) (void *data1, void *data2);


/*-----------------------------------------------------------------------------
 * DuListCreate()
 *
 * Description:
 *   Create an empty DuList.
 *
 * Arguments:
 *    lst : Returns the created list.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY. 
 *----------------------------------------------------------------------------*/
extern int DuListCreate (DuList *lst);


/*-----------------------------------------------------------------------------
 * DuListDestroy()
 *
 * Description:
 *   Destroys a DuList.
 *
 * Arguments:
 *    lst : The DuList that is to be destroyed.
 *---------------------------------------------------------------------------*/
extern void DuListDestroy (DuList lst);



/*-----------------------------------------------------------------------------
 * DuListSetComparator()
 *
 * Description:
 *   Sets the DuList's comparator. A comparator defines an order between data 
 *   objects 'data1' and 'data2'. It should return:
 *     -1 if 'data1' is smaller than 'data2'
 *      0 if 'data1' is equal to 'data2'
 *     +1 if 'data1' is larger than 'data2'
 * 
 *   The default order (if DuListSetComparator() is not called) is defined by
 *   the simple pointer comparison rules:
 *     -1 if data1 < data2
 *      0 if data1 == data2
 *     +1 if data1 > data2
 *   This order is useful for in for example integer lists, where integers are
 *   casted to pointers. For general data structures the user should define an
 *   appropriate order.
 *
 * Arguments:
 *          lst : The DuList.
 *   comparator : The comparator routine.
 *---------------------------------------------------------------------------*/
extern void DuListSetComparator (DuList lst, DuListComparator comparator);


/*-----------------------------------------------------------------------------
 * DuListGetSize()
 *
 * Description:
 *   Returns the number of elements in the DuList.
 *
 * Arguments:
 *           lst : The DuList.
 *   nr_elements : Returns the number of elements.
 *---------------------------------------------------------------------------*/
extern void DuListGetSize (DuList lst, int *size);



/*-----------------------------------------------------------------------------
 * DuListGetCurrent()
 *
 * Description:
 *   This routine returns the data located at the 'current position' in the
 *   DuList. The 'current position' is a property of a DuList. It is altered
 *   as a side effect by routines like DuListGetHead().
 *
 * Arguments:
 *    lst : The DuList.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST. 
 *----------------------------------------------------------------------------*/
int DuListGetCurrent (DuList lst, void **data);

/*-----------------------------------------------------------------------------
 * DuListGetFirst()
 *
 * Description:
 *   This routine returns the first element in the DuList. 
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is also set to 
 *   the first element in the DuList.
 *
 * Arguments:
 *    lst : The DuList.
 *   data : Returns the data.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST. 
 *----------------------------------------------------------------------------*/
extern int DuListGetFirst (DuList lst, void **data);


/*-----------------------------------------------------------------------------
 * DuListGetLast()
 *
 * Description:
 *   This routine returns the last element in the DuList. . 
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is also set to 
 *   the last element in the DuList.
 *
 * Arguments:
 *    lst : The DuList.
 *   data : Returns the data.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST. 
 *----------------------------------------------------------------------------*/
extern int DuListGetLast (DuList lst, void **data);


/*-----------------------------------------------------------------------------
 * DuListGetNext()
 *
 * Description:
 *   This routine returns the data located at the DuList element after the 
 *   'current position'.
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is also shifted
 *   to the next position.
 *
 * Arguments:
 *    lst : The DuList.
 *   data : Returns the data.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST, DU_RETURN_NO_NEXT.
 *----------------------------------------------------------------------------*/
extern int DuListGetNext (DuList lst, void **data);


/*-----------------------------------------------------------------------------
 * DuListGetPrev()
 *
 * Description:
 *   This routine returns the data located at the DuList element before the 
 *   'current position'.
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is also shifted
 *   to the previous position.
 *
 * Arguments:
 *    lst : The DuList.
 *   data : Returns the data.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST, DU_RETURN_NO_PREV.
 *----------------------------------------------------------------------------*/
extern int DuListGetPrev (DuList lst, void **data);


/*-----------------------------------------------------------------------------
 * DuListPrependElement()
 *
 * Description:
 *   This routine adds an element to the beginning of the DuList.
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is set to the
 *   added element.
 *
 * Arguments:
 *     lst : The DuList.
 *    data : The element to be added.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY.
 *----------------------------------------------------------------------------*/
extern int DuListPrependElement (DuList lst, void *data);


/*-----------------------------------------------------------------------------
 * DuListAppendElement()
 *
 * Description:
 *   This routine adds an element to the end of the DuList.
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is set to the
 *   added element.
 *
 * Arguments:
 *     lst : The DuList.
 *    data : The element to be added.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY.
 *----------------------------------------------------------------------------*/
extern int DuListAppendElement (DuList lst, void *data);


/*-----------------------------------------------------------------------------
 * DuListInsertElement()
 *
 * Description:
 *   This routine inserts an element in the DuList while preserving a certain
 *   order.
 *
 * Side effects:
 *   In order to determine where an element should be inserted, the DuList's
 *   comparator routine is used. For more details, see the description of the
 *   DuListSetComparator() routine. In case of an existing similar item, the
 *   element is added right after it. In case of successful operation, the
 *   'current position' is set to the newly inserted element.
 *
 * Arguments:
 *     lst : The DuList.
 *    data : The element to be inserted.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY.
 *----------------------------------------------------------------------------*/
extern int DuListInsertElement (DuList lst, void *data_p);


/*-----------------------------------------------------------------------------
 * DuListRemoveElement()
 *
 * Description:
 *   This routine removes the first element from the DuList that matches 
 *   'key_data_p'. Note that there can be more matching elements in the 
 *   DuList, but only the first one is removed.
 *
 * Side effects:
 *   In order to determine whether or not an element matches the specified
 *   'key_data_p', the DuList's comparator routine is used. For more details,
 *   see the description of the DuListSetComparator() routine.
 *   In case of successful operation, the 'current position' is set to the
 *   successor of the removed element. If the removed element was the last
 *   element in the list, the 'current position' is set to the first element. 
 *   If the removed element was the only element in the list, the DuList will 
 *   be empty after deletion and 'current position' is undefined.
 *
 * Arguments:
 *           lst : The DuList.
 *    key_data_p : The element to be removed.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST, DU_RETURN_NOT_FOUND.
 *----------------------------------------------------------------------------*/
extern int DuListRemoveElement (DuList lst, void *key_data_p);


/*-----------------------------------------------------------------------------
 * DuListRetrieveElement()
 *
 * Description:
 *   This routine retrieves the first element from the DuList that matches 
 *   'key_data_p'. Note that there can be more matching elements in the 
 *   DuList, but only the first one is returned.
 *
 * Side effects:
 *   In order to determine whether or not an element matches the specified
 *   'key_data_p', the DuList's comparator routine is used. For more details,
 *   see the description of the DuListSetComparator() routine.
 *   In case of successful operation, the 'current position' is set to the
 *   retrieved element.
 *
 * Arguments:
 *           lst : The DuList.
 *    key_data_p : The element to be removed.
 *        data_p : Returns the retrieved element.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST, DU_RETURN_NOT_FOUND.
 *----------------------------------------------------------------------------*/
extern int DuListRetrieveElement (DuList lst, void *key_data_p, void **data_p);


/*-----------------------------------------------------------------------------
 * DuListRetrieveElement()
 *
 * Description:
 *   This routine retrieves the element at position 'index' in the specified 
 *   DuList. The index should be a value in the range 0..N-1, where N is the
 *   size of the DuList as returned by the routine DuListGetSize().
 *
 * Side effects:
 *   In case of successful operation, the 'current position' is set to the
 *   retrieved element.
 *
 * Arguments:
 *           lst : The DuList.
 *         index : The index in the DuList.
 *        data_p : Returns the retrieved element.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_EMPTY_LIST, DU_RETURN_ILLEGAL_INDEX.
 *----------------------------------------------------------------------------*/
extern int DuListRetrieveIndexedElement (DuList lst, int index, void **data_p);


/*-----------------------------------------------------------------------------
 * DuListIterate()
 *
 * Description:
 *   This routine is used to perform an operation on each element in a DuList.
 *   The order in which the elements are traversed is from the first to the
 *   last element. The routine does not alter the 'current position'.
 *   The context variable in the iterator routine is used to share arbitrary 
 *   data between the caller and the iterator routine.
 *
 * Arguments:
 *         lst : The DuList.
 *         fun : The iterator routine.
 *     context : The context.
 *
 * Example:
 * 
 *    typedef struct _MyContext
 *    {
 *      int cnt;
 *    } MyContext;
 * 
 *    void iterator (void *data, void *context)
 *    {
 *      MyContext *my_context;
 * 
 *      my_context = (MyContext *) context;
 *      printf ("list[%d] = %p\n", my_context->cnt, data);
 *      my_context->cnt++;
 *    }
 *
 *    void main (void)
 *    {
 *       MyContext context;
 * 
 *       context.cnt = 0;
 *       DuListIterate (lst, iterator, &context);
 *    }
 *----------------------------------------------------------------------------*/
extern void DuListIterate (DuList lst, DuListIterator fun, void *context);














/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuEnv stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * DuEnvSet###()
 *
 * Description:
 *   These routines set the value of an environment variable. If the variable 
 *   is already defined, the existing definition is replaced.
 *
 * Arguments:
 *    var_name : The name of the environment variable.
 *          val: The value.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_OUT_OF_MEMORY, DU_RETURN_ILLEGAL_VARIABLE_NAME.
 *---------------------------------------------------------------------------*/
extern int DuEnvSetInt (const char *var_name, int val);
extern int DuEnvSetByte (const char *var_name, BYTE val);
extern int DuEnvSetInt (const char *var_name, int val);
extern int DuEnvSetLong (const char *var_name, long val);
extern int DuEnvSetFloat (const char *var_name, float val);
extern int DuEnvSetDouble (const char *var_name, double val);
extern int DuEnvSetString (const char *var_name, const char *val);

/*-----------------------------------------------------------------------------
 * DuEnvGet###()
 *
 * Description:
 *   These routines retrieve the value of an environment variable.
 *
 * Arguments:
 *    var_name : The name of the environment variable.
 *          val: The returned reference to the value.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_UNDEFINED_VARIABLE, DU_RETURN_ILLEGAL_TYPE,
 *   DU_RETURN_ILLEGAL_VARIABLE_NAME.
 *---------------------------------------------------------------------------*/
extern int DuEnvGetByte (const char *var_name, BYTE *val);
extern int DuEnvGetInt (const char *var_name, int *val);
extern int DuEnvGetLong (const char *var_name, long *val);
extern int DuEnvGetFloat (const char *var_name, float *val);
extern int DuEnvGetDouble (const char *var_name, double *val);
extern int DuEnvGetString (const char *var_name, const char **val);

/*-----------------------------------------------------------------------------
 * DuEnvReset()
 *
 * Description:
 *   Reset the environment. This removes all environment variable definitions.
 *   After this call all memory allocated for environment variables is freed.
 *
 * Returns:
 *   DU_RETURN_OK.
 *---------------------------------------------------------------------------*/
extern int DuEnvReset ();

/*-----------------------------------------------------------------------------
 * DuEnvRemove()
 *
 * Description:
 *   Remove the definition of the variable 'var_name'. 
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_UNDEFINED_VARIABLE, DU_RETURN_ILLEGAL_VARIABLE_NAME.
 *---------------------------------------------------------------------------*/
extern int DuEnvRemove (const char *var_name);

/*-----------------------------------------------------------------------------
 * DuEnvLoad()
 *
 * Description:
 *   Load environment variables from a text file. This will add all
 *   definitions in the text file to the environment. Definitions of variables
 *   that already exist in the environment will be overruled by the definitions
 *   in the file.
 *   It is capable of detecting whether a text-version or an encrypted version
 *   is offered and takes action accordingly. With the text_allowed variable
 *   can be indicated whether a plain-text version is allowed to be read.
 *
 * Arguments:
 *    filename     : The name of the text file.
 *    text_allowed : Indicates whether plain text is allowed.
 *    update_value_if_exist : set to 1 of overrule an already specified value.
 *                   This parameter is only used and the 'str' contains a 
 *                   non-encrypted env-specification.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_CANNOT_OPEN_FILE,
 *   DU_RETURN_ILLEGAL_ENV_FILE, DU_RETURN_OUT_OF_MEMORY, 
 *   DU_RETURN_ILLEGAL_VARIABLE_NAME, DU_RETURN_ILLEGAL_TYPE.
 *---------------------------------------------------------------------------*/
int DuEnvLoad (const char *filename, int text_allowed);
int DuEnvLoadFromString(const char *str, int text_allowed,
                        int update_value_if_exist);

/*-----------------------------------------------------------------------------
 * DuEnvSaveText()
 *
 * Description:
 *   Save the environment to a text file.
 *
 * Arguments:
 *    filename : The name of the text file.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_CANNOT_OPEN_FILE, 
 *---------------------------------------------------------------------------*/
extern int DuEnvSaveText (const char *filename);

/*-----------------------------------------------------------------------------
* DuEnvSaveTextToStream()
*
* Description:
*  Save the current contents of the environment to an already open stream.
*
* Arguments:
*  f : Pointer to a stream open for writing.
*
* Returns:
*  DU_RETURN_OK on successful completion, or one of the following error codes:
*  DU_RETURN_ILLEGAL_NULL_POINTER, DU_RETURN_CANNOT_WRITE.
*----------------------------------------------------------------------------*/
extern int DuEnvSaveTextToStream(FILE *f);

/*-----------------------------------------------------------------------------
 * DuEnvSaveEncrypted()
 *
 * Description:
 *   Save the environment to an encrypted text file.
 *
 * Arguments:
 *    filename : The name of the encrypted text file.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_CANNOT_OPEN_FILE, 
 *---------------------------------------------------------------------------*/
extern int DuEnvSaveEncrypted (const char *filename);





/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuMemPool stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/
typedef void du_pool_t;

#define DU_MEMPOOL_FLAG_FENCE		(1<<0)

extern int DuMemPoolCreate(du_pool_t **pool,const unsigned int flags,unsigned int default_size);
extern int DuMemPoolDestroy(du_pool_t *pool);
extern int DuMemPoolClear(du_pool_t *pool);
extern void *DuMemPoolAlloc(du_pool_t *pool, const unsigned long byte_size);
extern void *DuMemPoolCalloc(du_pool_t *pool, const unsigned long ele_n,
                             const unsigned long ele_size);
extern int DuMemPoolFree(du_pool_t *pool, void *addr, const unsigned long size);




/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuHashTable stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


typedef struct _DuHashTableStruct *DuHashTable;


/*-----------------------------------------------------------------------------
 * DuHashTableCreate()
 *
 * Description:
 *   Create an empty DuHashTable.
 *
 * Arguments:
 *    hsh : Returns the created hash table.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_NOT_INSTALLED, DU_RETURN_OUT_OF_MEMORY, 
 *   DU_RETURN_ILLEGAL_NULL_POINTER.
 *---------------------------------------------------------------------------*/
extern int DuHashTableCreate (DuHashTable *hsh);

/*-----------------------------------------------------------------------------
 * DuHashTableDestroy()
 *
 * Description:
 *   Destroyes a DuHashTable.
 *
 * Arguments:
 *        hsh : The DuHashTable that is to be destroyed.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_ILLEGAL_HASH_TABLE.
 *---------------------------------------------------------------------------*/
extern int DuHashTableDestroy (DuHashTable hsh);

/*-----------------------------------------------------------------------------
 * DuHashTableAddElement()
 *
 * Description:
 *   Add a key to a DuHashTable. The caller can associate a reference to its
 *   own data with the key by setting the data parameter. Set 'data' to
 *   NULL if no data reference needs to be associated. If the key is already
 *   in the hash table, then only the data reference associated with 'key' is
 *   updated with the specified data reference.
 *
 * Arguments:
 *       hsh : The DuHashTable.
 *       key : The key to be added.
 *    keylen : The length of the key.
 *      data : A reference to user data.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_OUT_OF_MEMORY, DU_RETURN_ILLEGAL_HASH_TABLE,
 *   DU_RETURN_ILLEGAL_KEY.
 *---------------------------------------------------------------------------*/
extern int DuHashTableAddElement (DuHashTable hsh, 
                                  const unsigned char *key, 
                                  size_t keylen, 
                                  const void *data);

/*-----------------------------------------------------------------------------
 * DuHashTableRetrieveElement()
 *
 * Description:
 *   Checks if the specified key is in the hash table and returns the
 *   associated data reference. The value NULL is returned in 'data' if the
 *   specified key is not in the hash table or no data reference is associated
 *   with 'key'.
 *
 * Arguments:
 *          hsh : The DuHashTable.
 *          key : The key to be checked.
 *       keylen : The length of the key.
 *   is_present : Returns 1 if the key is in the hash table and 0 if not.
 *         data : Returns the associated data reference.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED,
 *   DU_RETURN_ILLEGAL_HASH_TABLE, DU_RETURN_ILLEGAL_NULL_POINTER,
 *   DU_RETURN_ILLEGAL_KEY.
 *---------------------------------------------------------------------------*/
extern int DuHashTableRetrieveElement (DuHashTable hsh,
                                       const unsigned char *key,
                                       size_t keylen,
                                       int *is_present,
                                       const void **data);

/*-----------------------------------------------------------------------------
 * DuHashTableRemoveElement()
 *
 * Description:
 *   Remove a key from the hash table. If the key is not in the hash table,
 *   this operation has no effect.
 *
 * Arguments:
 *      hsh : The DuHashTable.
 *      key : The key to be added.
 *   keylen : The length of the key.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_ILLEGAL_HASH_TABLE, DU_RETURN_ILLEGAL_KEY.
 *---------------------------------------------------------------------------*/
extern int DuHashTableRemoveElement (DuHashTable hsh,
                                     const unsigned char *key,
                                     size_t keylen);

/*-----------------------------------------------------------------------------
 * DuHashTableGetNumberOfElements()
 *
 * Description:
 *   Returns the number of elements in the hash table.
 *
 * Arguments:
 *           hsh : The hash table.
 *   nr_elements : Returns the number of elements.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem:  DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_ILLEGAL_NULL_POINTER, DU_RETURN_ILLEGAL_HASH_TABLE.
 *---------------------------------------------------------------------------*/
extern int DuHashTableGetNumberOfElements (DuHashTable hsh, int *nr_elements);


/*-----------------------------------------------------------------------------
 * DuHashTableGetNext()
 *
 * Description:
 *   Get the next entry from the specified DuHashTable. This routine is be 
 *   used to iterate over all elements in a DuHashTable. The first element is 
 *   retrieved by specifying NULL for key. The next element is retrieved by 
 *   specifying the first key and so on. If 'key' is not in the DuHashTable or
 *   'key' is the last key in the DuHashTable, 'next_keylen' will return 0
 *   and 'next_key' and 'next_data' will return NULL.
 *
 * Arguments:
 *          hsh : The DuHashTable.
 *          key : The key.
 *       keylen : The length of the key.
 *     next_key : Returns the next key.
 *  next_keylen : Returns the length of the next key.
 *     data_ref : Returns the data reference associated with 'next_key'.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_ILLEGAL_NULL_POINTER, DU_RETURN_ILLEGAL_HASH_TABLE,
 *   DU_RETURN_ILLEGAL_KEY.
 *---------------------------------------------------------------------------*/
extern int DuHashTableGetNext (DuHashTable hsh,
                               const unsigned char *key, size_t keylen,
                               const unsigned char **next_key, size_t *next_keylen,
                               const void **next_data);


/*-----------------------------------------------------------------------------
 * DuHashTableExport()
 *
 * Description:
 *   Exports a DuHashTable. All elements of the DuHashTable are stored in the
 *   arrays 'keys' and 'datas'. The caller is responsible for allocating these
 *   buffers. The size of the buffers should be >= N, where N is the number of
 *   elements in the database which is returned by the 
 *   DuHashTableGetNumberOfElements() routine. If no keys or no data references
 *   are required, one can specify  NULL for 'keys' or 'datas' respectively.
 *   Note further that the 'keys' array will be filled with references to the
 *   keys in the DuHashTable. This means that that these references are valid
 *   as long as the DuHashTable exists.
 *
 * Arguments:
 *          hsh : The DuHashTable.
 *         keys : The array, in which the keys are stored.
 *        datas : The array, in  which the data references are stored.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_ILLEGAL_NULL_POINTER, DU_RETURN_ILLEGAL_HASH_TABLE.
 *---------------------------------------------------------------------------*/
extern int DuHashTableExport (DuHashTable hsh, const unsigned char *keys[], 
                              const void *datas[]);

/*-----------------------------------------------------------------------------
 * DuHashTableImport()
 *
 * Description:
 *   Imports a DuHashTable. A new DuHashTable is created and the elements in 
 *   the array 'keys' are added. The routine makes a local copy of all keys in 
 *   the array, which allows the user to destroy the array and keys after this
 *   routine. The array 'datas' is used to associate references to user data to 
 *   the keys. A value NULL at a certain location in the 'datas' array is
 *   used to denote that no data is associated with that key. If no data
 *   references are used at all, one can set 'datas' to NULL.
 *   
 *
 * Arguments:
 *          hsh : Returns the created DuHashTable.
 *         keys : The array with keys.
 *    keys_lens : The array with key lengths.
 *        datas : The array with data references.
 *  nr_elements : Number of elements to be imported.
 *
 * Returns:
 *   DU_RETURN_OK if the operation was succesful and one of the following
 *   errors in case of any problem: DU_RETURN_NOT_INSTALLED, 
 *   DU_RETURN_OUT_OF_MEMORY, DU_RETURN_ILLEGAL_NULL_POINTER.
 *---------------------------------------------------------------------------*/
extern int DuHashTableImport (DuHashTable *hsh, const unsigned char *keys[],
                              const size_t key_lens[], const void *datas[],
                              int nr_elements);











/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DU_ASCII stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

extern  const int *const du_ascii_table;

#define DU_ASCII_ISALNUM(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_ALNUM) != 0)
#define DU_ASCII_ISALPHA(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_ALPHA) != 0)
#define DU_ASCII_ISCNTRL(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_CNTRL) != 0)
#define DU_ASCII_ISDIGIT(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_DIGIT) != 0)
#define DU_ASCII_ISGRAPH(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_GRAPH) != 0)
#define DU_ASCII_ISLOWER(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_LOWER) != 0)
#define DU_ASCII_ISPRINT(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_PRINT) != 0)
#define DU_ASCII_ISPUNCT(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_PUNCT) != 0)
#define DU_ASCII_ISSPACE(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_SPACE) != 0)
#define DU_ASCII_ISUPPER(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_UPPER) != 0)
#define DU_ASCII_ISXDIGIT(c) \
  ((du_ascii_table[(unsigned char) (c)] & DU_ASCII_XDIGIT) != 0)


/*-----------------------------------------------------------------------------
 * DuAsciiIsAlnum(), DuAsciiIsAlpha(), DuAsciiIsCntrl(), DuAsciiIsDigit(),
 * DuAsciiIsGraph(), DuAsciiIsLower(), DuAsciiIsPrint(), DuAsciiIsPunct(),
 * DuAsciiIsSpace(), DuAsciiIsUpper(), DuAsciiIsXdigit()
 *
 * Description:
 *  Unlike the standard C library is-type() functions, these functions only
 *  recognizes standard ASCII letters and ignores the locale, returning false
 *  on all non-ASCII characters, even if they are of the correct type in a
 *  particular character set and should return true. The result is always 0
 *  (false) or 1 (true).
 *
 * Input:
 *   c: The character to be checked.
 *
 * Return value:
 *  1 if 'c' is of the correct type, and 0 if 'c' is not of the correct type
 *  or 'c' is smaller than 0 or larger than 255.
 *---------------------------------------------------------------------------*/
extern int DuAsciiIsAlnum(int c);
extern int DuAsciiIsAlpha(int c);
extern int DuAsciiIsCntrl(int c);
extern int DuAsciiIsDigit(int c);
extern int DuAsciiIsGraph(int c);
extern int DuAsciiIsLower(int c);
extern int DuAsciiIsPrint(int c);
extern int DuAsciiIsPunct(int c);
extern int DuAsciiIsSpace(int c);
extern int DuAsciiIsUpper(int c);
extern int DuAsciiIsXdigit(int c);

/*-----------------------------------------------------------------------------
 * DuAsciiToLower(), DuAsciiToUpper()
 *
 * Description:
 *  Unlike the standard C library toupper() function, this function only
 *  recognizes standard ASCII letters and ignores the locale, returning all
 *  non-ASCII characters unchanged, even if they are upper or lower case
 *  letters in a particular character set and should be changed.
 *
 * Input:
 *   c: The character to be converted to upper or lower case.
 *
 * Return value:
 *  The result of converting 'c' to lower case or upper case. If 'c' is not
 *  an ASCII lower or upper case letter, 'c' is returned unchanged.
 *---------------------------------------------------------------------------*/
extern int DuAsciiToLower(int c);
extern int DuAsciiToUpper(int c);

/*-----------------------------------------------------------------------------
* DsStrAsciiCaseCmp()
*
* Description:
*   Unlike the BSD strcasecmp() function, this routine only recognized standard
*   ASCII letters and ignores the locale, treating all non-ASCII characters as
*   if they are not letters.
*
* Inputs:
*   s1 : Specifies a '\0' terminated string.
*   s2 : Specifies a '\0' terminated string.
*
* Return value:
*  An integer less than, equal to, or grater than zero if 's1' is found,
*  respectively, to be less than, to match, or to be greater than 's2'. Zero is
*  also returned if either 's1' or 's2' is NULL.
*----------------------------------------------------------------------------*/
extern int DuStrAsciiCaseCmp(const char *s1, const char *s2);

/*-----------------------------------------------------------------------------
* DuStrTok()
*
* Description:
*   Reentrant implementation of the strtok() routine. The DuStrTok() routine
*   parses a string into a sequence of tokens. On the first call to DuStrTok() 
*   the string to be parsed should be specified in 'str'. In each subsequent 
*   call that should parse the same string, 'str' should be NULL.
*   The 'delimeters' argument specifies a set of characters that delimit the
*   tokens in the parsed string. Each call to DuStrTok() returns a pointer to 
*   a null-terminated string containing the next token. This string does not 
*   include the delimiting character. If no more tokens are found, DuStrTok() 
*   returns NULL. A sequence of two or more contiguous delimiter characters in 
*   the parsed string is considered to be a single delimiter. Delimiter 
*   characters at the start or end of the string are ignored. Put another way: 
*   the tokens returned by DuStrTok() are always non-empty strings. 
*   The 'save_ptr' argument is a pointer to a char* variable that is used 
*   internally by DuStrTok() in order to maintain context between successive 
*   calls that parse the same string. On the first call to DuStrTok(), the value 
*   of 'save_ptr' is ignored. In subsequent calls, 'save_ptr' should be unchanged 
*   since the previous call. Different strings may be parsed concurrently using 
*   sequences of calls to DuStrTok() that specify different' save_ptr' arguments. 
*
* Inputs:
*   str        : Specifies the string to be parsed in the first call. The value 
*                should be NULL in subsequent calls.
*   delimeters : Specifies the delimiter symbols.
*   
* IO parameters:
*   save_ptr   : Context parameter (see description).
*
* Return value:
*   A pointer to a null-terminated string containing the next token. This 
*   string does not include the delimiting character. If no more tokens are 
*   found, NULL is returned.
*----------------------------------------------------------------------------*/
extern char *DuStrTok (char *str, const char *delimeters, char **save_ptr);







/*-----------------------------------------------------------------------------
 *-----------------------------------------------------------------------------
 *
 * DuStr stuff
 *
 *-----------------------------------------------------------------------------
 *---------------------------------------------------------------------------*/
#define DU_SEEK_SET 0
#define DU_SEEK_CUR 1
#define DU_SEEK_END 2

typedef struct DuStrFile_t *DuStrFile;

extern DuStrFile DuStrFileOpen(const char *str, char **dest,
                               const char *mode);

extern int DuStrFileClose(DuStrFile fs);
extern int DuStrFileSeek(DuStrFile fs, long offset, int origin);
extern int DuStrFileGetc(DuStrFile fs);

extern int DuStrIsIdentifier(const char *src);

/*-----------------------------------------------------------------------------
* DuStrCpy()
*
* Description:
*   Duplicates a '\0'-terminated string including the trailing '\0'. After the
*   last use, the duplicated string should be freed by DuFree().
*
* Inputs:
*    src : The '\0' terminated character string to be duplicated.
*
* Return value:
*   The duplicated string. The value NULL is returned in case of a memory
*   problem or in case src = NULL.
*----------------------------------------------------------------------------*/
extern char *DuStrDup (const char *src);

/*-----------------------------------------------------------------------------
*
* Description:
*  Counts the number of characters in an '\0' terminated character string.
*  The routine will return 0 if 'src' is NULL.
*----------------------------------------------------------------------------*/
extern int DuStrLen( const char *src);

/*-----------------------------------------------------------------------------
* DuFree()
*
* Description:
*   Frees a pointer. Use this routine for all pointers allocated by Du.
*
* Inputs:
*    ptr : Pointer to be freed.
*
*----------------------------------------------------------------------------*/
extern void DuFree (void *ptr);

/*-----------------------------------------------------------------------------
* DsStrConcat()
*
* Description:
*  Concatenates a NULL terminated list of '\0' terminated character strings
*  into a new allocated buffer.
*
* Return value:
*  A pointer to the new concatenated string, or NULL if 'string1' is NULL or
*  not enough memory.
*----------------------------------------------------------------------------*/
extern char *DuStrConcat(const char *string1,.../* NULL terminated */);


/*-----------------------------------------------------------------------------
* DuStrCpyP()
*
* Description:
*  Copies a '\0'-terminated string into the 'dest' buffer, including the 
*  trailing '\0', and returns a pointer to the traling '\0' character. This
*  function is useful for concatenating multiple strings together without
*  having to repeatedly scan for the end.
*
* Inputs:
*   dest : Specifies a buffer into which the 'src' string should be copied.
*    src : Specifies a '\0' terminated character string that should be copied
*          into 'dest'. 
*
* Return value:
*  A pointer to the traling '\0'-character or NULL if either 'dest' or 'src'
*  is NULL.
*----------------------------------------------------------------------------*/
extern char *DuStrCpyP(char *dest, const char *src);



/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuSerialize stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

typedef struct _DuSerializeObjectStruct *DuSerializeObject;



/*-----------------------------------------------------------------------------
 * DuSerializeObjectCreate
 *
 * Description:
 *    Creates an empty DuSerializeObject.
 *
 * Arguments:
 *     s : Returns the DuSerializeObject.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_OUT_OF_MEMORY
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectCreate (DuSerializeObject *s);

/*-----------------------------------------------------------------------------
 * DuSerializeObjectDestroy
 *
 * Description:
 *    Destroy a DuSerializeObject
 *
 * Arguments:
 *     s : The DuSerializeObject.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectDestroy (DuSerializeObject s);


/*-----------------------------------------------------------------------------
 * DuSerializeObjectRewind
 *
 * Arguments:
 *     s : The DuSerializeObject.
 *
 * Description:
 *    See header file.
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectRewind (DuSerializeObject s);

/*-----------------------------------------------------------------------------
 * DuSerializeUnsignedChar, DuSerializeChar, DuSerializeUnsignedLong, 
 * DuSerializeLong, DuSerializeInt, DuSerializePointer.
 *
 * Description:
 *   Write a value of a certain type to a DuSerializeObject. For the routine
 *   DuSerializeString(), value is assumed to be a '\0' terminated string. 
 *
 * Arguments:
 *     s : The DuSerializeObject.
 * value : The value to serialize.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT, DU_RETURN_OUT_OF_MEMORY.
 *   
 *---------------------------------------------------------------------------*/
extern int DuSerializeUnsignedChar (DuSerializeObject s, unsigned char value);
extern int DuSerializeChar (DuSerializeObject s, char value);
extern int DuSerializeUnsignedLong (DuSerializeObject s, unsigned long value);
extern int DuSerializeLong (DuSerializeObject s, long value);
extern int DuSerializeInt (DuSerializeObject s, int value);
extern int DuSerializePointer (DuSerializeObject s, void *value);
extern int DuSerializeString (DuSerializeObject s, char *value);

/*-----------------------------------------------------------------------------
 * DuDeserializeUnsignedChar, DuDeserializeChar, DuDeserializeUnsignedLong, 
 * DuDeserializeLong, DuDeserializeInt, DuDeserializePointer, 
 * DuDeserializeString.
 *
 * Description:
 *   Read a value of a certain type from a DuSerializeObject. The routine
 *   DuDeserializeString() returns a '\0'-terminated string in the buffer
 *   value. This buffer should be large enough to hold the result. The buffer
 *   size should be S+1, where S is the length of the string. To obtain the 
 *   string length S, one should call the routine with value == NULL.
 *
 * Arguments:
 *     s : The DuSerializeObject.
 * value : The unsigned char.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT, DU_RETURN_NO_MORE_DATA.
 *---------------------------------------------------------------------------*/
extern int DuDeserializeUnsignedChar (DuSerializeObject s, unsigned char *value);
extern int DuDeserializeChar (DuSerializeObject s, char *value);
extern int DuDeserializeUnsignedLong (DuSerializeObject s, unsigned long *value);
extern int DuDeserializeLong (DuSerializeObject s, long *value);
extern int DuDeserializeInt (DuSerializeObject s, int *value);
extern int DuDeserializePointer (DuSerializeObject s, void **value);
extern int DuDeserializeString (DuSerializeObject s, char *value, 
                                size_t *str_len);


/*-----------------------------------------------------------------------------
 * DuSerializeObjectGetSize
 *
 * Description:
 *    Return the the number of bytes currently used to store the serialized 
 *    data.
 *
 * Arguments:
 *     s : The DuSerializeObject.
 *  size : Returns the number of bytes.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT,
 *   DU_RETURN_ILLEGAL_NULL_POINTER
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectGetSize (DuSerializeObject s, long *size);

/*-----------------------------------------------------------------------------
 * DuSerializeObjectGetBufferRef
 *
 * Description:
 *   Return a reference to the binary representation of the currently
 *   serialized data. Note that this reference is valid until the next
 *   operation on the DuSerializeObject. The number of bytes in the buffer
 *   is returned by 'size'. This is equivalent to the size returned by the
 *   DuSerializeObjectGetSize() routine.
 *
 * Arguments:
 *     s : The DuSerializeObject.
 *   buf : Returns a reference to the buffer.
 *  size : Returns the number of bytes in 'buf'.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT, 
 *   DU_RETURN_ILLEGAL_NULL_POINTER
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectGetBufferRef (DuSerializeObject s, 
                                          unsigned char **buf, 
                                          long *size);

/*-----------------------------------------------------------------------------
 * DuSerializeObjectToBase64
 *
 * Description:
 *   Transforms a DuSerializeObject into its base 64 representation. This is a 
 *   '\0'-terminated string. The encoded string is stored in str. The caller
 *   is responsible for allocating this buffer. The buffer should be large 
 *   enough to store the string and the terminating '\0' symbol. To obtain the 
 *   length of the string without actually storing the string, one should
 *   specify str=NULL.
 *
 * Arguments:
 *       s : The DuSerializeObject.
 *     str : The buffer in which the base64 encoded string is stored.
 * str_len : Returns the length of the encoded string. 
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_SERIALIZE_OBJECT.
 *---------------------------------------------------------------------------*/
extern int DuSerializeObjectToBase64 (DuSerializeObject s, char *str, 
                                      size_t *str_len);

/*-----------------------------------------------------------------------------
 * DuSerializeBase64ToObject
 *
 * Description:
 *   This is the reverse of DuSerializeObjectToBase64(), and creates a 
 *   DuSerializeObject from its base64 string representation.
 *   
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_OUT_OF_MEMORY, 
 *   DU_RETURN_ILLEGAL_MESSAGE.
 *---------------------------------------------------------------------------*/
extern int DuSerializeBase64ToObject (const char *str, DuSerializeObject *s);

extern int DuSerializeObjectToBytes (DuSerializeObject s, 
									 DS_UINT8 *bytes, 
									 int *nr_bytes);

extern int DuSerializeBytesToObject (const DS_UINT8 *bytes, 
									 int nr_bytes, 
									 DuSerializeObject *s);


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuBase64 stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * DuBase64Encode
 *
 * Description:
 *   Encode an unsigned character buffer into a base64 character string. The
 *   string is '\0' terminated. The encoded string is stored in str. The caller
 *   is responsible for allocating this buffer. The buffer should be large 
 *   enough to store the string and the terminating '\0' symbol. To obtain the 
 *   length of the string without actually storing the string, one should
 *   specify str=NULL.
 *
 * Arguments:
 *     buf : The buffer to encode.
 *    size : The number of elements in buf.
 *     str : The buffer in which the base64 encoded string is stored.
 * str_len : Returns the length of the encoded string. 
 *
 * Returns:
 *   DU_RETURN_OK.
 *---------------------------------------------------------------------------*/
extern int DuBase64Encode (unsigned char *buf, long size, char *str, 
                           size_t *str_len);


/*-----------------------------------------------------------------------------
 * DuBase64Decode
 *
 * Description:
 *   Decode a base64 character string into an unsigned character buffer. The
 *   base64 string is assumed to be '\0' terminated. The decoded data is 
 *   returned in buf. The caller is responsible for allocating this buffer. 
 *   The buffer should be large enough to store the data. To obtain the size 
 *   without actually decoding the string, one should specify buf=NULL.
 *
 * Arguments:
 *     str : The buffer containing the base64 encoded string.
 *     buf : The buffer in which the decoded data is stored.
 *    size : Returns the number of elements in buf.
 *
 * Returns:
 *   DU_RETURN_OK, DU_RETURN_ILLEGAL_MESSAGE.
 *---------------------------------------------------------------------------*/
extern int DuBase64Decode (const char *str, unsigned char *buf, long *size);

/*-----------------------------------------------------------------------------
 * DuMessageToUint32
 *
 * Description:
 *   Computes a 32 bit checksum for the given message. The message may have
 *   any length (including zero length). The determination is based on the
 *   Message-Digest Algorithm (MD5).
 *
 * Arguments:
 *     message : The message for which a checksum is to be evaluated.
 *      length : The length of the message.
 *   check_sum : The computed checksum.
 *
 * Returns:
 *   DU_RETURN_OK.
 *---------------------------------------------------------------------------*/
extern int DuMessageToUint32 (unsigned char *message, 
                              int length, 
                              DS_UINT32 *check_sum);
                       

/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * DuPath stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * DuPathSkipRoot()
 *
 * Description:
 *   Returns a pointer into file_name after the root component, i.e. after 
 *   the '/' in UNIX or 'C:\' or \\server\share\ under WIN32. If file_name 
 *   is not an absolute path, tail will be set to file_name. There is however
 *   one exception to this rule. If under WIN32 we have a relative file 
 *   preceded by a drive letter (for example 'C:book.txt'), tail will be set
 *   to the part after the ':'.
 *
 * WIN32 Examples:
 *   "\"                        ""
 *   "\\\\"                     ""
 *   "C:"                       ""
 *   "C:\"                      ""
 *   "C:\hello.tif"             "hello.tif"
 *   "C:hello.tif"              "hello.tif"
 *   "\\wenen"                  ""
 *   "\\wenen\share"            "share"
 *   "\\wenen\share\"           "share\"
 *   "\\wenen\share\hello.tif"  "share\hello.tif"
 *   "\\\sub\\hello.tif"        "sub\\hello.tif"
 *   "\\\sub\share\hello.tif"   "sub\share\hello.tif"
 *   "//wenen/share/hello.tif"  "share/hello.tif"
 *
 * WIN32 Examples (relative files):
 *   "..\hello.tif"             "..\hello.tif"
 *   "hello.tif"                "hello.tif" 
 *
 * Arguments:
 *     file_name : The filename.
 *          tail : Returns a reference in file_name, after the UNC prefix.
 *                 The value will be identical to file_name if file_name 
 *                 contains no UNC prefix.
 * 
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME. 
 *---------------------------------------------------------------------------*/
extern int DuPathSkipRoot (const char *file_name, 
                           const char **tail);

/*-----------------------------------------------------------------------------
 * DuPathIsAbsolute()
 *
 * Description:
 *   Checks if the given file_name is an absolute file name, i.e. it contains 
 *   a full path from the root directory such as '/usr/local' on UNIX or 
 *   'C:\windows\file.txt' or '\\wenen\share\file.txt'on WIN32 systems. An 
 *   empty filename is not absolute.
 *
 * WIN32 Examples:
 *   \\srv001\share             Absolute
 *   "C:book.doc"               Relative
 *   "C:\book.doc"              Absolute
 *   "book.doc"                 Relative

 * LINUX Examples:
 *   "/home/misc/book.doc"      Absolute
 *   "../mark"                  Relative
 *   "."                        Relative
 *
 * Arguments:
 *      file_name : The filename to be checked.
 *    is_absolute : Returns 0 if not absolute and 1 if absolute.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME. 
 *---------------------------------------------------------------------------*/
extern int DuPathIsAbsolute (const char *file_name, int *is_absolute);


/*-----------------------------------------------------------------------------
 * DuPathGetExtensionRef()
 *
 * Description:
 *   Returns a pointer into file_name at the beginning of the file extension.
 *   If the file has no extension, a reference to the terminating '\0' 
 *   character is returned. 
 *
 * Examples:
 *   "C:\hello.tif"             "tif"
 *   "//wenen/share/hello.tif"  "tif"
 *   "/tmp/file.tar.gz"         "gz"
 *   ".bashrc"         "        "bashrc"
 *   "\"                        ""
 *   "C:."                      ""
 *   "C:.\"                     ""
 *
 * Arguments:
 *     file_name : The filename.
 *     extension : Returns a reference in file_name, after the dot of the
 *                 extension.
 * 
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME. 
 *---------------------------------------------------------------------------*/
int DuPathGetExtensionRef (const char *file_name, 
                           const char **extension);

/*-----------------------------------------------------------------------------
 * DuPathGetBasename()
 *
 * Description:
 *   Returns the last component of the filename. If file_name ends with a 
 *   directory separator (i.e., the specified name is a directory), it gets 
 *   the component before the last separator. The 
 *   The returned string should be freed with DuFree() when no longer needed.
 *
 * WIN32 Examples:
 *   "C:\windows\programs\"      "programs"
 *   "\programs\"                "programs"
 *   "\\srv001\share"            "share"
 *   "\\srv001\share/file.txt"   "file.txt"
 *   "C:sub"                     "sub"
 *   "C:book.doc"                "book.doc"
 *   "C:\book.doc"               "book.doc"
 *   "book.doc"                  "book.doc"
 * 
 * WIN32 Special cases:
 *   "\"                         "\"
 *   "\\srv001"                  "\"
 *   "\\srv001\"                 "\"
 *   "C:"                        "\"
 *   "C:\"                       "\"
 *   "C:\."                      "."
 *   "C:."                       "."
 *   "C:.\"                      "."
 *
 * LINUX:
 *   "/usr/include"              "include"
 *   "/usr/include/"             "include"
 *
 * LINUX Special cases:
 *   "/"                         ""
 *
 * Arguments:
 *        file_name : The filename.
 *         basename : Returns the base name.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_OUT_OF_MEMORY.
 *---------------------------------------------------------------------------*/
extern int DuPathGetBasename (const char *file_name,
                              char **basename);

/*-----------------------------------------------------------------------------
 * DuPathNormalize()
 *
 * Description:
 *   Returns a normalized version of the filename. In the normalized filename
 *   multiple separators are replaced by a single one. Furthermore for WIN32
 *   it is checked if the specified filename must be a directory (for example
 *   "." or "\\srv001". If so, a terminating directory separator is added.
 *   Furthermore, on the WIN32 platform, the normalized filename contains no
 *   '/' separators, only '\'.
 *   The force_terminator parameter is used to force a terminating directory
 *    separator. If this parameter is set to 1, this the normalized filename
 *   will always end in a terminating separator. If this parameter is set to
 *   0, this routine will determine based on the name (as far as possible)
 *   whether or not a terminating separator should be added. All examples 
 *   below are examples with force_terminator=0.
 *   The returned string should be freed with DuFree() when no longer needed.
 *
 * WIN32 Examples:
 *   "C:/windows/programs/"      "C:\windows\programs\"
 *   "C:\windows\\/programs/\"   "C:\windows\programs\"
 *   "C:\windows\file.txt"       "C:\windows\"
 *   "\\srv001\share"            "\\srv001\share\"
 *   "\\srv001\\\share\"         "\\srv001\share\"
 *   "\\srv001\share/file.txt"   "\\srv001\share\file.txt"
 *   "C:file"                    "C:file"
 *   "C:sub\"                    "C:sub\"
 *   "file.txt"                  "file.txt"
 *   "."                         ".\"
 *   "\\srv001"                  "\\srv001\"
 *
 * LINUX:
 *   "//usr/file"                "/usr/file"
 *   "/usr/include/"             "/usr/include/"
 *   "///"                       "/"
 *
 * Arguments:
 *          file_name : The filename.
 *   force_terminator : Specifies whether or not the terminating directory
 *                      separator is forced.
 *            dirname : Returns the directory name.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_OUT_OF_MEMORY.
 *---------------------------------------------------------------------------*/
extern int DuPathNormalize (const char *file_name, 
                            int force_terminator,
                            char **normalized);


/*-----------------------------------------------------------------------------
 * DuPathGetDirname()
 *
 * Description:
 *   Returns the directory components of a file name. If the file name has no
 *   directory components ".\" is returned. The returned directory is always
 *   a clean path with single separators. For WIN32, only '\' separators are
 *   used. The 'strip_terminator' parameter can be used to specify whether or
 *   not the last terminator should be stripped. All answers below are based
 *   on strip_terminator=0.
 *   The returned string should be freed with DuFree() when no longer needed.
 *
 * WIN32 Examples:
 *   "C:\windows\programs\"      "C:\windows\programs\"
 *   "C:\windows\\/programs/\"   "C:\windows\programs\"
 *   "C:\windows\file.txt"       "C:\windows\"
 *   "\\srv001\share"            "\\srv001\share\"
 *   "\\srv001\share\"           "\\srv001\share\"
 *   "\\srv001\share/file.txt"   "\\srv001\share\"
 *   "C:file"                    "C:.\"
 *   "C:sub\"                    "C:sub\"
 *   "file.txt"                  ".\"
 *   "."                         ".\"
 *   "C:"                        "C:\"
 *   "\\srv001"                  "\\srv001\"
 *
 * LINUX:
 *   "/usr/file"                 "/usr/"
 *   "/usr/include/"             "/usr/include/"
 *   "/"                         "/"
 *
 * Arguments:
 *        file_name : The filename.
 * strip_terminator : Specifies whether or not the terminator should be
 *                    stripped (0 = do not strip, 1 = strip).
 *          dirname : Returns the directory name.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, 
 *---------------------------------------------------------------------------*/
 extern int DuPathGetDirname (const char *file_name, 
                              int strip_terminator,
                              char **dirname);

/*-----------------------------------------------------------------------------
 * DuPathChangeExtension()
 *
 * Description:
 *   Changes the extension of a specified file. If the file has no extension,
 *   the specified extension is added. Note that if the specified file is a
 *   directory, DU_RETURN_ILLEGAL_FILENAME is returned.
 *   The returned string should be freed with DuFree() when no longer needed.
 *
 * Arguments:
 *          src : The filename.
 *      dst_ext : The desired extension.
 *          dst : Returns the file.
 *
 * Returns:
 *   DU_RETURN_OK in case of successful operation, otherwise one of the error
 *   codes: DU_RETURN_ILLEGAL_FILENAME, DU_RETURN_OUT_OF_MEMORY.
 *---------------------------------------------------------------------------*/
extern int DuPathChangeExtension (const char *src,
                                  const char *dst_ext,
                                  char **dst);



/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Library stuff
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* DuInitialize()
*
* Description:
*  Initialize this library. This routine must be called before any of the other
*  routines in this library are used.
*
* Return value:
*  DU_RETURN_OK on successful completion or one of the following error 
*  codes: DU_RETURN_ILLEGAL_VERSION
*---------------------------------------------------------------------------*/
#define DuInitialize(initialization_options) \
  DuInitializeVersion(DU_LIB_MAJOR,DU_LIB_MINOR,NULL)
extern int DuInitializeVersion(const char *major,
                               const char *minor,
                               const char *initialization_options);

/*-----------------------------------------------------------------------------
* DuFinalize()
*
* Description:
*  Frees all allocated resources. A second call to DuFinalize() will have no
*  effect. After calling DuFinalize() no DU-routines can be used expect for
*  DuGetVersion() and DuInitialize().
*
* Return value:
*  The routine returns always DU_RETURN_OK. 
*----------------------------------------------------------------------------*/
extern int DuFinalize(void);




/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Rounding defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

#define bround(f) ((BYTE)(floor((f)+0.5)))
#define lround(f) ((long)(floor((f)+0.5)))
#define lfloor(f) ((long)(floor(f)))
#define ifloor(f) ((int)(floor(f)))
#define iround(f) ((int)(floor((f)+0.5)))
#define fast_floor(f) (((long) (f)) - (((f)<0) && ((f)!=((long)(f)))))
#define fast_ceil(f) (-(fast_floor(-(f))))
#define positive_lround(x)		((lround((x)-0.0001) != lround((x)+0.0001)) ? lround((x)+0.0001) : lround(x))
#define consistent_lround(x)	(((x)>=0)?positive_lround(x):-positive_lround(-(x)))


#define positive_lfloor(x)		((lfloor((x)-0.0001) != lfloor((x)+0.0001)) ? lfloor((x)+0.0001) : lfloor(x))
#define consistent_lfloor(x)	(((x)>=0)?positive_lfloor(x):-positive_lfloor(-(x)))


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Misc defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

#define DegToRad(x) ((x) * DS_PI / 180.0)
#define RadToDeg(x) (180.0 * (x) / DS_PI)



#define FLOAT_DIV(x,y)  ((-DS_EPSILON < (y)  &&  (y) < DS_EPSILON)                              \
                         ? AssertionReport(-DS_EPSILON >= (y)  ||  (y) >= DS_EPSILON), (x)     \
                         : (x)/(y))

#define LONG_DIV(x,y)   ((y) == 0                                                           \
                         ? AssertionReport ((y) != 0), (x)                                  \
                         : (x)/(y)) 


#define ROUNDED_LONG_DIV(x,y) ((y) == 0                         \
                         ? AssertionReport ((y) != 0), (x)      \
                         : ((x) > 0)                            \
                             ? ((y) > 0)                        \
                                 ? ((2*(x) + (y))/(2*(y)))      \
                                 : (-((-2*(x) + (y))/(2*(y))))  \
                             : ((y) > 0)                        \
                                 ? (-((2*(x) - (y))/(-2*(y))))  \
                                 : ((-2*(x) - (y))/(-2*(y)))    \
                      )



/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Showroom convenience routines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Stdlog headers
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

extern FILE* LogOpen(const char* filename, int argc, char** argv);
extern void LogClose();
extern void LogError(const char* format, ...);

extern void LogPrint(const char* format, ...); 
extern void LogPrintTime();


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Extstring headers
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

extern char* strfind (const char* str, const char* set);
extern char* strrfind (const char* str, const char* set);


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Alternative memory manager functions
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

//#define DU_ALT_MEM_NO_MEMORY_TRACE

#ifndef DU_MEMORY_MANAGER
#define mem_Sprint(dummy) ((void)0)

#ifdef _WIN32_WCE
#define strdup _strdup
#endif

/* strdup() is not defined for PLATFORM_C6400p !!! */
#if defined (PLATFORM_C6400p)
#define strdup(s)    DuStrDup((s))
#endif


#else   /* DU_MEMORY_MANAGER enabled */

#undef strdup

#define calloc(n,s)  mem_Scalloc((n),(s))
#define malloc(s)    mem_Smalloc((s))
#define strdup(s)    mem_Sstrdup((s))
#define free(s)      mem_Sfree((s))
#define realloc(p,s) mem_Srealloc((p),(s))

#ifdef DU_ALT_MEM_NO_MEMORY_TRACE
extern void *mem_Scalloc(size_t num,size_t size);
extern void mem_Sfree(void *ptr);
extern void *mem_Smalloc(size_t size);
extern char *mem_Sstrdup (const char *s);
#define mem_Sprint(dummy) ((void)0)
extern void *mem_Srealloc(void *ptr,size_t size);

#else /* DU_ALT_MEM_NO_MEMORY_TRACE */

#undef mem_Scalloc
#undef mem_Sfree
#undef mem_Smalloc
#undef mem_Sstrdup
#undef mem_Sprint
#undef mem_Srealloc
#define mem_Smalloc(size)      _mem_Smalloc(size,__FILE__,__LINE__)
#define mem_Sstrdup(ptr)       _mem_Sstrdup(ptr,__FILE__,__LINE__)
#define mem_Sfree(ptr)         _mem_Sfree(ptr,__FILE__,__LINE__)
#define mem_Scalloc(num,size)  _mem_Scalloc(num,size,__FILE__,__LINE__)
#define mem_Sprint(filename)   _mem_Sprint(filename)
#define mem_Srealloc(ptr,size) _mem_Srealloc(ptr,size,__FILE__,__LINE__)
extern void *_mem_Scalloc(size_t num, size_t size, char *file,int line);
extern void _mem_Sfree(void *ptr,char *file,int line);
extern void *_mem_Smalloc(size_t size,char *file,int line);
extern void *_mem_Sstrdup (const char *s, char *file, int line);
extern void _mem_Sprint(const char *filename);
extern void *_mem_Srealloc(void *ptr,size_t size,char *file,int line);

#endif /* DU_ALT_MEM_NO_MEMORY_TRACE */

#endif /* DU_MEMORY_MANAGER */

extern void DuTimeLog(char *msg,...);
extern void DuTimeLogDump();

#ifdef DU_DEBUG_TIMELOG
#define DU_TIMELOG_START DuTimeLog("start");
#define DU_TIMELOG DuTimeLog
#define DU_TIMELOG_END DuTimeLogDump();
#else
#define DU_TIMELOG_START
#define DU_TIMELOG
#define DU_TIMELOG_END
#endif



/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Node functions and defines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


#define IsRootNode(node) (((Node *)(node))->parent == NULL &&                 \
   ((Node *)(node))->next == NULL && ((Node *)(node))->prev == NULL)
#define IsLeafNode(node) ((node)->children == NULL)

/*-----------------------------------------------------------------------------
 * Node
 *
 * Description:
 *   The Node struct represents one node in a N-ary tree. The 'data' field
 *   contains the actual data of the node. The 'next' and 'prev' fields point
 *   to the node's siblings (a sibling is another Node with the same parent).
 *   The 'parent' field points to the parent of the Node, or is NULL if the
 *   Node is the root of the tree. The 'children' field points to the first
 *   child of the Node. The other children are accessed by using the 'next'
 *   pointer of each child.
 *---------------------------------------------------------------------------*/
typedef struct _Node {
   void *data;
   struct _Node *parent;
   struct _Node *prev;
   struct _Node *next;
   struct _Node *children;
} Node;

typedef enum {
  TRAVERSE_LEAFS     = 1 << 0,
  TRAVERSE_NON_LEAFS = 1 << 1,
  TRAVERSE_ALL       = TRAVERSE_LEAFS | TRAVERSE_NON_LEAFS,
  TRAVERSE_MASK      = 0x03
} TraverseFlags;

/*-----------------------------------------------------------------------------
 * TraverseFunc()
 *
 * Description:
 *   Specifies the type of function passed to TraverseNode(). The function is
 *   called with each of the nodes visited, together with the user data passed
 *   to TraverseNode(). If the function returns 1, then the traversal is stop-
 *   ped.
 *
 * Arguments:
 *   node : a Node.
 *   data : user data passed to TraverseNode().
 *
 * Returns:
 *   1 to stop the traversal or 0 to continue the traversal.
 *---------------------------------------------------------------------------*/
typedef int (*TraverseFunc)(Node *node,void *data);

typedef enum {
  TRAVERSE_IN_ORDER,
  TRAVERSE_PRE_ORDER,
  TRAVERSE_PRE_ORDER_DYNAMIC,
  TRAVERSE_POST_ORDER,
  TRAVERSE_LEVEL_ORDER
} TraverseType;


extern Node *AppendNode(Node *parent, Node *node);
/*-----------------------------------------------------------------------------
 * GetNodeDepth()
 *
 * Description:
 *   Get the depth of a Node. If 'node' is NULL the depth is 0. The root node
 *   has a depth of 1. For the children of the root node the depth is 2, and so
 *   on.
 *
 * Return:
 *   the depth of the Node;
 *---------------------------------------------------------------------------*/
extern unsigned int GetNodeDepth(Node *node);

/*-----------------------------------------------------------------------------
 * GetNthChildNode()
 *
 * Description:
 *   Gets a child of a Node, using the given index. The first child is at index
 *   0. If the index is too big, NULL is returned;
 *
 * Arguments:
 *   node : a Node
 *      n : the index of the desired child.
 *
 * Returns:
 *   The child of 'node' at index 'n'.
 *---------------------------------------------------------------------------*/
extern Node *GetNthChildNode(Node *node, unsigned int n);



extern Node *InsertNode(Node *parent, int position, Node *node);

/*-----------------------------------------------------------------------------
 * InsertNodeBefore()
 *
 * Description:
 *   Inserts a Node beneath the parent before the given sibling.
 *
 * Arguments:
 *    parent : the Node to place 'node' under.
 *   sibling : the sibling Node to place 'node' before. If sibling is NULL,
 *             the node is inserted as the last chld of 'parent'.
 *      node : the Node to insert.
 *
 * Returns:
 *   The inserted Node.
 *---------------------------------------------------------------------------*/
extern Node *InsertNodeBefore(Node *parent, Node *sibling, Node *node);

/*-----------------------------------------------------------------------------
 * NewNode()
 *
 * Description:
 *   Creates a new Node containing the given data. Used to create the first
 *   node in a tree.
 *
 * Arguments:
 *   data : the data of the new Node
 *   alloc_size : if not 0, allocate 'alloc_size' bytes and copy 'data' into
 *                it.
 *
 * Returns:
 *   a new Node.
 *---------------------------------------------------------------------------*/
extern Node *NewNode(void *data, unsigned int alloc_size);

/*-----------------------------------------------------------------------------
 * PrependNode()
 *
 * Description:
 *   
 *
 * Arguments:
 *
 * Returns:
 *---------------------------------------------------------------------------*/
extern Node *PrependNode(Node *parent, Node *node);

/*-----------------------------------------------------------------------------
 * TraverseNode()
 *
 * Description:
 *   Traverses a tree starting at the given root Node. It calls the given func-
 *   tion for each node visited. The traversal can be halted at any point by
 *   returning 1 from 'func'.
 *
 * Arguments:
 *        root : the root Node of the tree to traverse.
 *       order : the order in which nodes are visited.
 *       flags : which types of children are to be visited.
 *   max_depth : the maximum depth of the traversal. Nodes below his depth will
 *               not be visited. If 'max_depth' is -1 all nodes in the tree are
 *               visited. if depth is 1, only the root is visited. If depth is
 *               2, the root and its children are visited. And so on.
 *        func : the function to call for each visited Node.
 *        data : user data to pass to the function.
 *---------------------------------------------------------------------------*/
extern void TraverseNode(Node *root, TraverseType order, TraverseFlags flags,
                         int max_depth, TraverseFunc func, void *data);










/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Debug reporting routines
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/

/*
 *
 * SYNOPSIS:
 *
 *    ErrorReport((const char *format, [arg,]...));
 *    WarningReport((const char *format, [arg,]....));
 *    DebugReport((const char *format, [arg,]...), int level);
 *    LineReport(int level);
 *    AssertionReport(expresion);
 *    SystemErrorReport((const char *format, [arg,]...));
 *    Log(((const char *format, [arg,]...));
 *
 *    extern FILE *error_report_file (only needed if ERROR_REPORT_FILE defined)
 *    extern FILE *debug_report_file (only needed if DEBUG_REPORT_FILE defined)
 *    extern FILE *logfile           (only needed if LOG_REPORT_FILE define)
 *    extern int error_report_flag   (only needed if ERROR_REPORT_VAR defined)
 *    extern int debug_report_level  (only needed if DEBUG_REPORT_VAR defined)
 *    extern int debug_report_flag   (only needed if DEBUG_REPORT_VAR defined)
 *    extern int create_logfile      (only needed if LOG_REPORT_VAR defined)
 *
 * DESCRIPTION:
 *
 * This file defines various message reporting macro's that can be included
 * in the code as one statements.
 * All the macro's will be replaced by a null statement when the code is 
 * compiled with `NDEBUG' (no debugging) defined.
 * Default behaviour of all macro's is to print the reporting messages to the
 * `stderr' stream. This default behaviour can be altered by defining
 * ErrorReport will print to the file specified by `error_report_file'
 * when ERROR_FILE is defined.
 * DebugReport will print to the file specified by `debug_report_file' when
 * DEBUG_FILE is defined.
 * The programmer is responsible for defining and opening of these files for
 * writing. Both macro's do not open or close these files!!!
 * With ERROR_REPORT_VAR defined the printing of error messages can be switched on
 * and off with the `error_report_flag'. The printing of debug information
 * can be controlled by the `debug_report_flag' and `debug_report_level'
 * variables when DEBUG_REPORT_VAR is defined. The user is reponsible for
 * declaring and initializing these variables.
 * The macro `SystemErrorReport' behaves the same as the ErrorReport macro
 * except that a laguage-dependent message is printed at the end, describing the
 * last error encountered during a call to a system or library function.
 *
 * EXAMPLES:
 *
 * Using the ErrorReport macro in file `main.c' at line 21 as follows:
 *      ErrorReport(("Illegal index %d (max=%d)",i,max_size));
 * will produce (when i equals 14 and max_size equals 10):
 *      "Error in main.c at line 21: Illegal index 14 (max=10)\n"
 * Using the DebugReport macro in the same situation yields:
 *      DebugReport(("Illegal index %d (max=%d)",i,max_size),1);
 *      "Debug in main.c at line 21: Illegal index 14 (max=10)\n"
 *      LineReport(1) produces:
 *      "Debug in main,c at line 21: Passed this line\n"
 * The AssertionReport macro will produce a messaga when the expresion
 * evaluates false. AssertionReport(i < max_size) would print the following
 * message:
 *      "Assertion (i < max_size) failed in main.c at line 21\n"
 *
 *
 * IMPORTANT:
 * The additional parentheses around the `format' string and `args' are
 * required. You will get compile errors when you leave them out.
 *
 */

#ifdef ERROR_REPORT_FILE
extern FILE *error_report_file;
#   define __error_report_file error_report_file
#else
#   define __error_report_file stderr
#endif

#ifdef WARNING_REPORT_FILE
extern FILE *warning_report_file;
#   define __warning_report_file warning_report_file
#else
#   define __warning_report_file stderr
#endif

#ifdef DEBUG_REPORT_FILE
extern FILE *debug_report_file;
#   define __debug_report_file debug_report_file
#else
#   define __debug_report_file stderr
#endif

#ifdef LOG_REPORT_FILE
extern FILE *logfile;
#   define __log_report_file logfile
#else
#   define __log_report_file stderr
#endif

#ifdef ERROR_REPORT_VAR
extern int error_report_flag;
#   define __error_report_flag error_report_flag
#else
#   define __error_report_flag 1                    /* produce error messages */
#endif

#ifdef WARNING_REPORT_VAR
extern int warning_report_flag;
#   define __warning_report_flag warning_report_flag
#else
#   define __warning_report_flag 1                /* produce warning messages */
#endif

#ifdef LOG_REPORT_VAR
extern int create_logfile;
#   define __log_report_flag create_logfile
#else
#   define __log_report_flag 1
#endif

#ifdef DEBUG_REPORT_VAR
extern int debug_report_flag;
extern int debug_report_level;
#   define __debug_report_flag  debug_report_flag
#   define __debug_report_level debug_report_level
#else
#   define __debug_report_flag  1                   /* produce debug messages */
#   define __debug_report_level 1000      /* show all debug levels below 1000 */
#endif

#ifdef NDEBUG
#define AssertionReport(expresion) ((void)0)
#define ErrorReport(message)       ((void)0)
#define WarningReport(message)     ((void)0)
#define DebugReport(message,level) ((void)0)
#define LineReport(level)          ((void)0)
#define SystemErrorReport(message) ((void)0)
#define Log(message)               ((void)0)
#else

extern int errno;

#define __VoidStatement                                                        \
   if(0) {                                                                     \
      __VarArgErrorPrint("This is to avoid the unused function warning");      \
      __VarArgDebugPrint("This is to avoid the unused function warning");      \
      __VarArgLogPrint(  "This is to avoid the unused function warning");      \
      __VarArgWarningPrint("This is to avoid the unused function warning");    \
   } else ((void)0)

#define ErrorReport(message)                                                   \
   do { \
   if(__error_report_flag) {                                                   \
     fprintf(__error_report_file,"Error in %s at line %d: ",__FILE__,__LINE__);\
     __VarArgErrorPrint message ;                                              \
     fprintf(__error_report_file,"\n");                                        \
   } else __VoidStatement; \
   } while (0)

#define WarningReport(message)                                                 \
   do { \
   if(__warning_report_flag) {                                                 \
     fprintf(__warning_report_file,"Warning in %s at line %d: ",__FILE__,__LINE__);\
     __VarArgWarningPrint message ;                                            \
     fprintf(__warning_report_file,"\n");                                      \
   } else __VoidStatement; \
   } while (0)

#define SystemErrorReport(message)                                             \
   do { \
   if(__error_report_flag) {                                                   \
     fprintf(__error_report_file,"Error in %s at line %d: ",__FILE__,__LINE__);\
     __VarArgErrorPrint message ;                                              \
     fprintf(__error_report_file," (%s)\n",strerror(errno));                   \
   } else __VoidStatement; \
   } while(0)

#define DebugReport(message,level)                                             \
   do { \
   if (__debug_report_flag && (level) <= __debug_report_level) {                \
     fprintf(__debug_report_file,"Debug in %s at line %d: ",__FILE__,__LINE__);\
     __VarArgDebugPrint message ;                                              \
     fprintf(__debug_report_file,"\n");                                        \
   } else __VoidStatement; \
   } while(0)

#define LineReport(level) DebugReport(("Passed this line"),(level))

#define AssertionReport(expression)                                            \
   ((expression) ? (void)0 :                                                   \
      (void) fprintf(__debug_report_file,"Assertion (%s) in %s at line %d failed\n",  \
              #expression,__FILE__,__LINE__))


#define Log(message)							       \
   do { \
   if (__log_report_flag) {						       \
      __VarArgLogPrint message;						       \
      fprintf (__log_report_file, "\n");				       \
      fflush (__log_report_file);					       \
   } else __VoidStatement; \
   } while (0)


extern void __VarArgDebugPrint (const char *fmt, ... /*args*/);
extern void __VarArgErrorPrint(const char *fmt, ... /*args*/);
extern void __VarArgWarningPrint(const char *fmt, ... /*args*/);
extern void __VarArgLogPrint (const char *fmt, ... /*args*/);


#endif /* NDEBUG */

#define DEBUG_FUNCTION_LEVEL 6
#define DEBUG_BASIC_FUNCTION_LEVEL 99

#define DebugFuncEnter(f)				                \
   DebugReport (("ENTER_FUNCTION: %s", f), DEBUG_FUNCTION_LEVEL)
#define DebugBasicFuncEnter(f)				                \
   DebugReport (("ENTER_FUNCTION: %s", f), DEBUG_BASIC_FUNCTION_LEVEL)




#define OPTION_NO_ARGUMENT       DU_OPTION_NO_ARGUMENT
#define OPTION_REQUIRED_ARGUMENT DU_OPTION_REQUIRED_ARGUMENT
#define OPTION_OPTIONAL_ARGUMENT DU_OPTION_OPTIONAL_ARGUMENT
#define DuOptionSpecStruct OptionSpec_t
#define ProcessOptions(argc,argv,p,use,o,d,h,i,nr_args) \
  DuProcessOptions((argc),(argv),(p),"?.?.? built on " __TIMESTAMP__,\
    (use),(o),(d),(h),(i),(nr_args),(nr_args))
#define ProcessOptionsExt(argc,argv,p,use,o,d,h,i,min_nr_args, max_nr_args) \
  DuProcessOptions((argc),(argv),(p),"?.?.? built on " __TIMESTAMP__,\
   (use),(o),(d),(h),(i),(nr_args),(min_nr_args),(max_nr_args))


/*=============================================================================
* Command Line Argument Parsing (CLAP) support.
*
* The CLAP functions provide an easy and standard way to:
*  (a) Describe the functionality, command line arguments of an application,
*      and the libraries it depends on.
*  (b) Scan and handle the command line arguments.
*
*
* Main ingredients:
*  DuOptionSpectstruct : Contains an explicit specification of on all the 
*   options that are accepted.
*  DuProcessOptions: Routine to process the command line options
*
*----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
* DU_OPTION_NO_ARGUMENT, DU_OPTION_REQUIRED_ARGUMENT,
* DU_OPTION_OPTIONAL_ARGUMENT
*
* Desciption:
*  These defines should be used to specify if an option requires an argument,
*  has an optional argument, or allows no argument.
*----------------------------------------------------------------------------*/
#define DU_OPTION_NO_ARGUMENT       0
#define DU_OPTION_REQUIRED_ARGUMENT 1
#define DU_OPTION_OPTIONAL_ARGUMENT 2


/*-----------------------------------------------------------------------------
* DuOptionSpecStruct
*
* Description: 
*  The DuOptionSpecStruct is used to describe all the options used by the
*  application. The CLAP framework used this description to generate help
*  messages and to process the command line at the program start.
*
*  The DuOptionSpecStruct allows the specification of short, single character,
*  names (mandatory) and long (optional) names for options. All used names
*  should be unique.
*
* Fields:
*  short_name : A single character short name of a option. This field must
*               always be set. The first 'short_name' field that equals '\0' is
*               assumed to indicate the end of and DuOptionSpecStruct array.
*               All used characters must be unique.
*    long_name: A '0\' terminated character string specifying the long name of
*               an option. Use NULL to specify that the option has no long 
*               name. All used long names must be unique.
*      has_arg: Species if an options takes an argument. Used one of the
*               predefined values DU_OPTION_NO_ARGUMENT,
*               DU_OPTION_REQUIRED_ARGUMENT, or DU_OPTION_OPTIONAL_ARGUMENT.
*     arg_type: A '\0' terminated character string specifying the type of the
*               argument that this option takes. This string only used to
*               print additional argument information during a 'help' request.
*       descr : A '\0' terminated character string with a short description of
*               the option. This string will be printed in any 'help' request.
*----------------------------------------------------------------------------*/
typedef struct DuOptionSpecStructType {
  int short_name;
  const char *long_name;
  int has_arg;
  const char *arg_type;
  const char *descr;
} DuOptionSpecStruct;



/*-----------------------------------------------------------------------------
*
* Return value:
*  DU_RETURN_CLAP_OK in case of successful completion, or one of the following
*  error codes: DU_RETURN_CLAP_HELP, or DU_RETURN_CLAP_ERROR.
*----------------------------------------------------------------------------*/
extern int DuProcessOptions(int argc, char** argv,
                            const char* progname,
                            const char *version,
                            const char* usage,
                            const DuOptionSpecStruct* options,
                            const char* description,
                            int (option_handler)(int c, char *arg),
                            int* option_index, int min_nr_args,
                            int max_nr_args);


/* 
** The function 'ProcessOptions' parses the command line parameters specified by
** 'argc' and 'argv'. 
** If an error occurs during parsing an appropriate error message is generated.
** To this purpose the programmer needs to pass three constant string parameters
** 'progname', 'usage', and 'description' containing the name of the application,
** usage information and a complete description of the application respectively.
** The options that are allowed are desrcibed by 'options'. This is a vector of 
** OptionSpec_t's terminated by an element containing a 'short_name' field 
** that is '\0'.
** The parameter 'OptionHandler' is a user defined function that handles all
** possible options (usually a function with a switch statement). The input of 
** this function is the short option identified by 'c' and a pointer 'arg' to an 
** optional argument. This pointer is NULL if no argument is specified. The 
** return value specifies wheter or not an error has occured during the 
** interpretation of the optional argument (See example below).
** The 'option_index' parameter specifies the first argv-element that is to be 
** processed. Normally when you want to scan all parameters, this value is set
** to 1 (the zeroth argv-element should be ignored since that is the program
** name). At return 'option_index' points to the next option that is to be 
** processed.
** The parameter 'nr_args' specifies how many arguments the application expects
** after the last option. If this can be any number a negative value should be
** specified.
** The return value of the function indicates wheter an error has occured during
** scanning (0=error, 1=ok).
*/



#define LONG_NO_CHECK   DS_MAX_LONG
#define INT_NO_CHECK    DS_MAX_INT
#define FLOAT_NO_CHECK  DS_MAX_FLOAT


extern int CheckArgChar(char *option_arg, const char *possible_chars, 
                        char *val);
extern int CheckArgLong(char *option_arg, long min, long max, long *val);
extern int CheckArgInt(char *option_arg, int min, int max, int *val);
extern int CheckArgFloat(char *option_arg, float min, float max, float *val);
extern int CheckArgString(char *option_arg,
                          int max_nr_chars,
                          char *string);

extern void ConditionalStrDup (char 		*option_arg, 
			       const char 	*default_str, 
			       char 		**str);

extern void ConditionalStrCpy (char 		*option_arg, 
			       const char 	*default_str, 
			       char 		*str);


/*
** Recognize one or more strings concatenated by the symbol separator.
** The maximum number of strings that may be concatenated is defined by 
** max_nr_strings. If more than max_nr_strings are found, the return value
** is 0, otherwise the return value is 1.
*/
extern int CheckArgStrings (char 	*option_arg, 
			    const char	separator,
			    long 	min_nr_strings, 
			    long 	max_nr_strings, 
			    char 	*strings[], 
			    long 	*nr_strings);

/*
** Similar to CheckArgStrings, CheckArgLongs tries to scan one or more longs
** concatenated by a separator symbol. Now an additional check is performed,
** if all values are longs in the specified range.
*/
extern int CheckArgLongs (char		*option_arg, 
			  const char	separator,
			  long 		min_nr_longs,
			  long 		max_nr_longs,
			  long		min, 
			  long		max, 
			  long 		longs[], 
			  long		*nr_longs);

/*
** Similar to CheckArgLongs, but now for ints.
*/
extern int CheckArgInts (char		*option_arg, 
			 const char	separator,
		         long 	        min_nr_ints,
		         long 	        max_nr_ints,
		         int       	min, 
		         int  	        max, 
		         int 	        ints[], 
		         long		*nr_ints);

/*
** Similar to CheckArgLongs, but now for floats.
*/
extern int CheckArgFloats (char		*option_arg, 
			   const char	separator,
			   long 	min_nr_floats,
			   long 	max_nr_floats,
			   float	min, 
			   float	max, 
			   float 	floats[], 
			   long		*nr_floats);


/*------------------------------------------------------------------------------
 *------------------------------------------------------------------------------
 *
 * Some often used command-line settings for intrada applications
 * Should be deleted from thia file sooner or later !!!!!
 *
 *------------------------------------------------------------------------------
 *----------------------------------------------------------------------------*/


#define DISPLAY_OPTION_SPECIFICATION			\
   {							\
   'x', "no_display", OPTION_NO_ARGUMENT, "",		\
   "Display nothing."					\
   },							\
   {							\
      'f', "full_display", OPTION_NO_ARGUMENT, "",	\
   "Display full process."				\
   }
   
#define TIMING_OPTION_SPECIFICATION			\
   {							\
   't', "timing", OPTION_NO_ARGUMENT, "",		\
   "Show timing results."				\
   }
   
#define VERBOSE_OPTION_SPECIFICATION			\
   {							\
   'v', "verbose", OPTION_REQUIRED_ARGUMENT, "int",	\
   "Use verbose level <int>."				\
   }
   
#define STORE_SHOWROOM_OPTION_SPECIFICATION		\
   {							\
   's', "store_showroom", OPTION_OPTIONAL_ARGUMENT,	\
   "dir", "Store showroom in directory <dir>."		\
   }
   
#define STORE_TIF_OPTION_SPECIFICATION			\
   {							\
   'g', "store_tif", OPTION_OPTIONAL_ARGUMENT, "dir",	\
   "Generate tif-images in directory <dir>."		\
   }
   
#define DISPLAY_OPTION_HANDLER				\
   case 'f':						\
   SHOW_MODE = SHOW_PROCESS;				\
   break;						\
   case 'x':						\
   SHOW_MODE = SHOW_NOTHING;				\
   break
   
#define TIMING_OPTION_HANDLER				\
   case 't':						\
   SHOW_TIMING = 1;					\
   break
   
#define VERBOSE_OPTION_HANDLER				\
   case 'v':						\
   ok = CheckArgInt (option_arg, 0, INT_NO_CHECK, 	\
   &debug_report_level);				\
   break
   
#define  STORE_SHOWROOM_OPTION_HANDLER(dir_name,b_var)	\
   case 's':						\
   b_var = TRUE;					\
   ConditionalStrCpy (option_arg, "./", dir_name);	\
   CleanPath (dir_name);				\
   break
   
#define  STORE_TIF_OPTION_HANDLER(dir_name,b_var)	\
   case 'g':						\
   b_var = TRUE;					\
   ConditionalStrCpy (option_arg, "./", dir_name);	\
   CleanPath (dir_name);				\
   break


#define DU_MAX_DATE_TIME_STRING_SIZE 100

/*-----------------------------------------------------------------------------
* DuGetCurrentDateAndTimeString()
*
* Description:
*   Creates a formated string for the current date/time.
* 
* Possible values for format: 
*   0: "Fri Jul 29 16:30:28 2011"
*   1: "2011/07/29 16:30:28"
*   2: "2011_07_29_16_30_28"
*
* Arguments:
*     format : The format of the string (see text above).
*     buffer : The buffer to store the formated string in.
*
* Returns:
*   DU_RETURN_ILLEGAL_OK on successful completion.
*   DU_RETURN_INTERNAL_ERROR if the current time could not be determined
*   DU_RETURN_ILLEGAL_FORMAT if the format parameter has an illegal value.
*---------------------------------------------------------------------------*/
extern int DuGetCurrentDateAndTimeString (int format,
										  char buffer[DU_MAX_DATE_TIME_STRING_SIZE]);


//#define DU_TIME_LOGGING_ENABLE

#ifdef DU_TIME_LOGGING_ENABLE
#define DuTimeLogStart(timer,parent_timer) DuTimeLogStart_imp(timer,parent_timer)
#define DuTimeLogStop(timer,parent_timer) DuTimeLogStop_imp(timer,parent_timer)
#define DuTimeLogDumpToFile()  DuTimeLogDumpToFile_imp()

extern int DuTimeLogStart_imp (const char *timer, const char *parent_timer);
extern int DuTimeLogStop_imp (const char *timer, const char *parent_timer);
extern void DuTimeLogDumpToFile_imp ();

#else

#define DuTimeLogStart(timer,parent_timer) (void)0
#define DuTimeLogStop(timer,parent_timer) (void)0
#define DuTimeLogDumpToFile() (void)0

#endif



#ifdef __cplusplus
}  /* close scope of 'extern "C"' declaration which encloses file. */
#endif



#endif /* _DU_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */



