#ifndef _ADT_STACK_H_
#define _ADT_STACK_H_

#include "memory_node.h"
#include "adt_vector.h"

typedef struct adt_stack_s
{
	Vector* vector_;
	struct adt_stack_ops_s *ops_;
} Stack;

struct adt_stack_ops_s
{
	///
	/// @brief      Initialize de values of the stack
	///
	/// @param      stack    Stack to initialize
	///
	/// @return     Signed int code
	///
	s16(*Init)(Stack *stack);
	///
	/// @brief      Destroy the list
	///
	/// @param      stack    Stack to destroy
	///
	/// @return     Unsigned int code
	///
	s16(*Destroy)(Stack *stack);
	///
	/// @brief      Insert a node in a position of the stack
	///
	/// @param      stack    Stack to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*Push)(Stack *stack, MemoryNode *value);
	///
	/// @brief      Extract a node in a position of the stack
	///
	/// @param      stack    Stack to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*Pop)(Stack *stack);
	///
	/// @brief      Print the values of the stack
	///
	/// @param      stack    Stack to print
	///
	/// @return     Void
	///
  void(*Print)(Stack *stack);
};
	///
	/// @brief      Create the stack and assing them in a position in memory
	///
	/// @return     Pointer to the stack created
	///
Stack* STACK_Create();
//

#endif //_ADT_STACK_H_
