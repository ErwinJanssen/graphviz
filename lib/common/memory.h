/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/*************************************************************************
 * Copyright (c) 2011 AT&T Intellectual Property 
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * Contributors: See CVS logs. Details at http://www.graphviz.org/
 *************************************************************************/

#ifndef GV_MEMORY_H
#define GV_MEMORY_H

#include <stdlib.h>
#ifdef HAVE_MALLOC_H
#include <malloc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef DMALLOC
#define NEW(t)           (t*)calloc(1,sizeof(t))
#define N_NEW(n,t)       (t*)calloc((n),sizeof(t))
#define GNEW(t)          (t*)malloc(sizeof(t))
#define N_GNEW(n,t)      (t*)malloc((n)*sizeof(t))
#define ALLOC(size,ptr,type) (ptr? (type*)realloc(ptr,(size)*sizeof(type)):(type*)malloc((size)*sizeof(type)))
#define RALLOC(size,ptr,type) ((type*)realloc(ptr,(size)*sizeof(type)))
#define ZALLOC(size,ptr,type,osize) (ptr? (type*)recalloc(ptr,(size)*sizeof(type)):(type*)calloc((size),sizeof(type)))
#else
#define NEW(t)           (t*)zmalloc(sizeof(t))
#define N_NEW(n,t)       (t*)zmalloc((n)*sizeof(t))
#define GNEW(t)          (t*)gmalloc(sizeof(t))

#define N_GNEW(n,t)      (t*)gmalloc((n)*sizeof(t))
#define N_GGNEW(n,t)      (t*)malloc((n)*sizeof(t))
#define ALLOC(size,ptr,type) (ptr? (type*)grealloc(ptr,(size)*sizeof(type)):(type*)gmalloc((size)*sizeof(type)))
#define RALLOC(size,ptr,type) ((type*)grealloc(ptr,(size)*sizeof(type)))
#define ZALLOC(size,ptr,type,osize) (ptr? (type*)zrealloc(ptr,size,sizeof(type),osize):(type*)zmalloc((size)*sizeof(type)))
#endif
#ifdef GVDLL
#define extern __declspec(dllexport)
#else
#ifdef WIN32
#ifndef GVC_EXPORTS
#define extern __declspec(dllimport)
#endif
#endif

#endif

    extern void *zmalloc(size_t);
    extern void *zrealloc(void *, size_t, size_t, size_t);
    extern void *gmalloc(size_t);
	extern void *grealloc(void *, size_t);
#undef extern

/**
 * Malloc with additional error checking.
 * Will always return a valid pointer to some memory, never null.
 * If no memory can be allocated, it throws exit and prints the name of the
 * function that called it.
 * When calling this function, use the __FUNCTION__ macro to pass it's name
 * to this function.
 */
void* safe_malloc_function(size_t size, const char* calling_function);

/**
 * This macro inserts the calling function as parameter, so it doesn't have to
 * be specified in the code.
 */
#define safe_malloc(size) safe_malloc_function(size, __FUNCTION__);

/**
 * Free that also sets the target to NULL. This prevents accessing freed
 * memory.
 */
void safe_free_function(void** pointer);

/**
 * This macro makes it possible to call `safe_free(pointer) instead of
 * casting the address of every pointer to (void **).
 */
#define safe_free(pointer) safe_free_function((void **) &(pointer))

#ifdef __cplusplus
}
#endif

#endif
