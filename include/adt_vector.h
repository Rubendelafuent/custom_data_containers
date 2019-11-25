#ifndef __ADT_VECTOR_H__
#define __ADT_VECTOR_H__

#include "platform_types.h"
#include "memory_node.h"

typedef struct adt_vector_s
{
	u16 head_;
	u16 tail_;
	u16 capacity_;
	MemoryNode *node_;
	struct vector_ops_s *ops_;
} Vector;

struct vector_ops_s
{
///
	/// @brief      Init the values of the vector
	///
	/// @param      Vector    Vector to initializate
	///
	/// @return     Signed int code
	///
s16(*Init)(Vector *vector);
	///
	/// @brief      Return the capacity of the vector
	///
	/// @param      Vector    Vector to check
	///
	/// @return     Unsigned int code
	///
u16(*Capacity)(Vector *vector);
	///
	/// @brief      Destroy the vector
	///
	/// @param      Vector    Vector to destroy
	///
	/// @return     Signed int code
	///
s16(*Destroy)(Vector *vector);
	///
	/// @brief      Check if the vector is empty
	///
	/// @param      Vector    Vector to check
	///
	/// @return     Signed int code
	///
s16(*isEmpty)(Vector *vector);
	///
	/// @brief      Check if the vector is full
	///
	/// @param      Vector    Vector to check
	///
	/// @return     Signed int code
	///
s16 (*isFull)(Vector *vector);
	///
	/// @brief      Return the length of the vector
	///
	/// @param      Vector    Vector to check
	///
	/// @return     Unsigned int code
	///
u16 (*Length)(Vector *vector);
	///
	/// @brief      Resize the capacity of the vector
	///
	/// @param      Vector    Vector to resize
	///
	/// @param			Capacity  Size to resize
	///
	/// @return     Unsigned int code
	///
u16 (*Resize)(Vector *vector, u16 capacity);
	///
	/// @brief      Insert a node in the first position of the vector
	///
	/// @param      Vector    Vector to insert the node
	///
	///	@param			node      Node to insert
	///
	/// @return     Signed int code
	///
s16 (*InsertFirst)(Vector *vector, MemoryNode *node);
	///
	/// @brief      Insert a node in the last position of the vector
	///
	/// @param      Vector    Vector to insert the node
	///
	/// @param			node 			Node to insert
	///
	/// @return     Signed int code
	///
s16(*InsertLast)(Vector *vector, MemoryNode *node);
	///
	/// @brief      Insert a node in a position
	///
	/// @param      Vector    Vector to insert the node
	///
	/// @param	 		node 			Node to insert
	///
	/// @param			index			Index of the node to insert
	///
	/// @return     Signed int code
	///
s16 (*Insert)(Vector *vector, MemoryNode *node, int index);
	///
	/// @brief      Return the value of the head
	///
	/// @param      Vector    Vector to check
	///
	/// @return     Memory node pointer
	///
MemoryNode* (*Head)(Vector *vector);
	///
	/// @brief      Extract the first element of the vector
	///
	/// @param      Vector    Vector to extract the node
	///
	/// @return     Memory node pointer
	///
MemoryNode*(*ExtractFirst)(Vector *vector);
	///
	/// @brief      Extract the last element of the vector
	///
	/// @param      Vector    Vector to extract the node
	///
	/// @return     Memory node pointer
	///
MemoryNode*(*ExtractLast)(Vector *vector);
	///
	/// @brief      Extract the element in a position
	///
	/// @param      Vector    Vector to extract the node
	///
	/// @return     Memory node pointer
	///
MemoryNode*(*Extract)(Vector *vector, u16 index);
///
/// @brief      Concatenates the source vector in the dest vector
///
/// @param      Vector    Source to concatenate
/// @param      Vector    Vector destination to concatenate
///
/// @return     Signed int code
///
s16 (*Concat)(Vector *source, Vector *dest);
///
/// @brief      Call a function passed as parameter in all the nodes
///
/// @param      Vector    Vector to call the callback
/// @param      Void*     Pointer to function (MEMORYNODE)
///
/// @return     Unsigned int code
///
u16 (*Traverse)(Vector *vector, void(*callback) (MemoryNode *));
// traverses a vector and applies a callback to each node
	///
	/// @brief      Print the values of the vector elements
	///
	/// @param      Vector    Vector to print
	///
	/// @return     Signed int code
	///
s16 (*Print)(Vector *vector);
// Print
};
	///
	/// @brief      Create the vector and assing them a position in memory
	///
	/// @param      Capacity    Capacity of the vector to create
	///
	/// @return     Pointer to the vector created
	///
Vector* VECTOR_Create(u16 capacity);

#endif //__ADT_VECTOR_H__
