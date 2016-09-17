/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2007-2013 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */

#ifndef _MALI_SHARED_MEM_REF_H_
#define _MALI_SHARED_MEM_REF_H_


#include <stddef.h>
#include <mali_system.h>
#include <base/mali_memory.h>


#ifdef __cplusplus
extern "C" {
#endif


/**
 * mali memory struct used to share
 */
typedef struct mali_shared_mem_ref
{
	mali_mem_handle   mali_memory;
	mali_atomic_int   owners;        /**< owner count */
	mali_atomic_int   usage;         /**< in-flight usage count */
} mali_shared_mem_ref;


/**
 * create a mem ref
 * @return NULL on error
 */
MALI_IMPORT struct mali_shared_mem_ref* _mali_shared_mem_ref_alloc( void );


/**
 * create a mem ref for existing memory
 */
MALI_IMPORT struct mali_shared_mem_ref* _mali_shared_mem_ref_alloc_existing_mem( mali_mem_handle mem );

/**
 * create a mem ref with mali memory
 * @param base_ctx
 * @param size
 * @param pow2_alignment
 * @param mali_access
 * @return NULL on error
 */
MALI_IMPORT struct mali_shared_mem_ref* _mali_shared_mem_ref_alloc_mem( mali_base_ctx_handle base_ctx, size_t size, u32 pow2_lignment, u32 mali_access );


/**
 * release a mali memory usage reference
 * @note if both usage and owner count is zero the mem ref will be destroyed
 */
MALI_IMPORT void _mali_shared_mem_ref_usage_deref( struct mali_shared_mem_ref *mem_ref );

/**
 * add a mali memory usage reference
 * @note owner is also increased to guarantee that owner count is always >= usage
 */
MALI_STATIC_INLINE void _mali_shared_mem_ref_usage_addref( struct mali_shared_mem_ref *mem_ref )
{
	MALI_DEBUG_ASSERT_POINTER( mem_ref );
	MALI_DEBUG_ASSERT( _mali_sys_atomic_get( &mem_ref->owners ) > 0, ("trying to addref an unreferenced _mali_shared_mem_ref") );
	_mali_sys_atomic_inc( &mem_ref->owners );
	_mali_sys_atomic_inc( &mem_ref->usage );
}


/** get mali memory usage reference count */
MALI_STATIC_INLINE int _mali_shared_mem_ref_get_usage_ref_count( struct mali_shared_mem_ref *mem_ref )
{
	MALI_DEBUG_ASSERT_POINTER( mem_ref );
	return _mali_sys_atomic_get( &mem_ref->usage );
}


/**
 * release a mali memory owner reference
 * @note if both usage and owner count is zero the mem ref will be destroyed
 */
MALI_IMPORT void _mali_shared_mem_ref_owner_deref( struct mali_shared_mem_ref *mem_ref );


/** add a mali memory owner reference */
MALI_STATIC_INLINE void _mali_shared_mem_ref_owner_addref( struct mali_shared_mem_ref *mem_ref )
{
	MALI_DEBUG_ASSERT_POINTER( mem_ref );
	MALI_DEBUG_ASSERT( _mali_sys_atomic_get( &mem_ref->owners ) > 0, ("trying to addref an unreferenced _mali_shared_mem_ref") );
	_mali_sys_atomic_inc( &mem_ref->owners );
}


/** get mali memory owner reference count */
MALI_STATIC_INLINE int _mali_shared_mem_ref_get_owner_ref_count( struct mali_shared_mem_ref *mem_ref )
{
	MALI_DEBUG_ASSERT_POINTER( mem_ref );
	return _mali_sys_atomic_get( &mem_ref->owners );
}


#ifdef __cplusplus
}
#endif


#endif /* _MALI_SHARED_MEM_REF_H_ */

