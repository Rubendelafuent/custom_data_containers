#ifndef _ADT_D_LIST_H_
#define _ADT_D_LIST_H_

#include "memory_node.h"

typedef struct adt_d_list_s
{
	u16 length_;
	MemoryNode *head_;
	MemoryNode *tail_;
	struct adt_d_list_ops_s *ops_;
} DList;

struct adt_d_list_ops_s
{
	///
	/// @brief      Initialize de values of the list
	///
	/// @param      list    List to initialize
	///
	/// @return     Signed int code
	///
	s16(*Init)(DList *list);
	///
	/// @brief      Destroy the list
	///
	/// @param      list    List to destroy
	///
	/// @return     Unsigned int code
	///
	s16(*Destroy)(DList *list);
	///
	/// @brief      Check if the list is empty
	///
	/// @param      list    List to check
	///
	/// @return     Bool
	///
	bool(*isEmpty) (DList *list);
	///
	/// @brief      Check the length of the list
	///
	/// @param      list    List to check
	///
	/// @return     Unsigned int code
	///
	u16(*Length) (DList *list);
	///
	/// @brief      Insert a node in the first position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*InsertFirst)(DList *list, MemoryNode *value);
	///
	/// @brief      Insert a node in the last position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*InsertLast)(DList *list, MemoryNode *value);
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
	s16(*Insert)(DList *list, MemoryNode *value, u16 index);
///
	/// @brief      Return the pointer to the first element of the list
	///
	/// @param      list    List to check
	///
	/// @return     Pointer to the first node
	///
	MemoryNode*(*Head)(DList *list);
	///
	/// @brief      Extract a node in the first position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*ExtractFirst)(DList *list);
	///
	/// @brief      Extract a node in the last position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*ExtractLast)(DList *list);
	///
	/// @brief      Extract a node in a position of the list
	///
	/// @param      list    List to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*Extract)(DList *list,u16 index);
	///
	/// @brief      Concatenate two list
	///
	/// @param      source    List to insert in other list
	///
	/// @param			dest 			List to be inserted
	///
	/// @return     Signed int code
	///
	s16(*Concat)(DList *source, DList *dest);
	///
	/// @brief      Print the values of the list
	///
	/// @param      list    List to print
	///
	/// @return     Void
	///
  void(*Print)(DList *list);
	///
	/// @brief      Call a function passed as parameter in all the nodes
	///
	/// @param      DList   List to call the callback
	/// @param      Void*   Pointer to function (MEMORYNODE)
	///
	/// @return     Unsigned int code
	///
	u16 (*Traverse)(DList *list, void(*callback) (MemoryNode *));
};
	///
	/// @brief      Create the list adn assing them in a position in memory
	///
	/// @return     Pointer to the list created
	///
DList* D_LIST_Create();
//

#endif //_ADT_LIST_H_
