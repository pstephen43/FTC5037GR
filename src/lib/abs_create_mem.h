/**
 *
 *  @file abs_create_mem.h
 *
 *  @brief a collection of math operations
 *
 *  Copyright 2013, Got Robot! FTC Team 5037
 *
 */
#ifndef ABS_CREATE_MEM_H
#define ABS_CREATE_MEM_H

int abs_create_mem()
{
	memset(buffer, 0x0, DYNAMIC_MEMORY_SIZE);

  /** now store the address of the buffer in the pointer */
  next_available_memory_ptr = buffer;
}

#endif /* !ABS_CREATE_MEM_H */
