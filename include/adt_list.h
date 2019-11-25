#ifndef _ADT_LIST_H_
#define _ADT_LIST_H_

#include "memory_node.h"

typedef struct adt_list_s
{
	u16 length_;
	MemoryNode *head_;
	MemoryNode *tail_;
	struct adt_list_ops_s *ops_;
} List;

struct adt_list_ops_s
{
	///
	/// @brief      Initialize de values of the list
	///
	/// @param      list    List to initialize
	///
	/// @return     Signed int code
	///
	s16(*Init)(List *list);
	///
	/// @brief      Destroy the list
	///
	/// @param      list    List to destroy
	///
	/// @return     Unsigned int code
	///
	s16(*Destroy)(List *list);
	///
	/// @brief      Check if the list is empty
	///
	/// @param      list    List to check
	///
	/// @return     Bool
	///
	bool(*isEmpty) (List *list);
	///
	/// @brief      Check the length of the list
	///
	/// @param      list    List to check
	///
	/// @return     Unsigned int code
	///
	u16(*Length) (List *list);
	///
	/// @brief      Insert a node in the first position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*InsertFirst)(List *list, MemoryNode *value);
	///
	/// @brief      Insert a node in the last position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*InsertLast)(List *list, MemoryNode *value);
	///
	/// @brief      Insert a node in a position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @param			index 	Position to insert the node
	///
	/// @return     Signed int code
	///
	s16(*Insert)(List *list, MemoryNode *value, u16 index);
	///
	/// @brief      Return the pointer to the first element of the list
	///
	/// @param      list    List to check
	///
	/// @return     Pointer to the first node
	///
	MemoryNode*(*Head)(List *list);
	///
	/// @brief      Extract a node in the first position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*ExtractFirst)(List *list);
	///
	/// @brief      Extract a node in the last position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*ExtractLast)(List *list);
	///
	/// @brief      Extract a node in a position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*Extract)(List *list,u16 index);
	///
	/// @brief      Concatenate two list
	///
	/// @param      source    List to insert in other list
	///
	/// @param			dest 			List to be inserted
	///
	/// @return     Signed int code
	///
	s16(*Concat)(List *source, List *dest);
	///
	/// @brief      Print the values of the list
	///
	/// @param      list    List to print
	///
	/// @return     Void
	///
  void(*Print)(List *list);
	///
	/// @brief      Call a function passed as parameter in all the nodes
	///
	/// @param      list    List to call the callback
	/// @param      Void*   Pointer to function (MEMORYNODE)
	///
	/// @return     Unsigned int code
	///
	u16 (*Traverse)(List *list, void(*callback) (MemoryNode *));
};
	///
	/// @brief      Create the list and assing them in a position in memory
	///
	/// @return     Pointer to the list created
	///
List* LIST_Create();
//

#endif //_ADT_LIST_H_
