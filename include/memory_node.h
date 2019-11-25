#ifndef __MEMORY_NODE_H__
#define __MEMORY_NODE_H__ 1

#include "platform_types.h"

typedef struct memory_node_s
{
	void *data_;
	u16 size_;
	struct memory_node_s* next_;
	struct memory_node_s* previous_;
	struct memory_node_ops_s *ops_;
} MemoryNode;

struct memory_node_ops_s
{
	///
	/// @brief      Init the values of the node
	///
	/// @param      Node    Node to initializate
	///
	/// @return     Signed int code
	///
	s16(*Init) (MemoryNode *node);
	///
	/// @brief      Return the data of the node
	///
	/// @param      Node    Node to check
	///
	/// @return     Pointer to void
	///
	void*(*Data)(MemoryNode *node);
	///
	/// @brief      Return the size of the node
	///
	/// @param      Node    Node to check
	///
	/// @return     Unsigned int code
	///
	u16(*Size)(MemoryNode *node);
	///
	/// @brief      Set the value to data
	///
	/// @param      Node    Node to set
	///
	/// @param			value   Value to set
	///
	/// @return     Signed int code
	///
	s16(*MemSet) (MemoryNode *node, u8 value);
	///
	/// @brief      Copy the void value to the node
	///
	/// @param      Node    Node to set
	///
	/// @param			*src    Void pointer to the value to set in the node
	///
	/// @param      bytes   Size of the value to set
	///
	/// @return     Signed int code
	///
	s16(*MemCopy) (MemoryNode *node, void *src, u16 bytes);
	///
	/// @brief      Concatenate a value into a node
	///
	/// @param      Node    Node to concatenate
	///
	/// @param			*src    Void pointer to the value to set in the node
	///
	/// @param			bytes   Size of the value to set
	///
	/// @return     Signed int code
	///
	s16(*MemConcat) (MemoryNode *node, void *src, u16 bytes);
	///
	/// @brief      Print the values of the nodes
	///
	/// @param      Node    Node to print
	///
	/// @return     Void
	///
	void(*Print)(MemoryNode *node);
	///
	/// @brief      Destroy the node
	///
	/// @param      Node    Node to destroy
	///
	/// @return     Signed int code
	///
	s16(*Destroy)(MemoryNode *node);
};

	///
	/// @brief      Create the node and assign them a position in memory
	///
	/// @return     Pointer to the memory node created
	///
MemoryNode* MEMNODE_Create();
	///
	/// @brief      Create by reference a memory node
	///
	/// @param      Node    Node to create
	///
	/// @return     Signed int code
	///
s16 MEMNODE_CreateFromRef(MemoryNode **node);
///
/// @brief      Reset the values of the node
///
/// @param      Node    Node to reset
///
/// @return     Signed int code
///
s16 MEMNODE_Reset(MemoryNode *node);
#endif // __MEMORY_NODE_H__
