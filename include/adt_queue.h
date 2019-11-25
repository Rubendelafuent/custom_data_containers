#ifndef _ADT_QUEUE_H_
#define _ADT_QUEUE_H_

#include "memory_node.h"
#include "adt_list.h"

typedef struct adt_queue_s
{
	List* list_;
	struct adt_queue_ops_s *ops_;
} Queue;

struct adt_queue_ops_s
{
	///
	/// @brief      Initialize de values of the queue
	///
	/// @param      queue    Queue to initialize
	///
	/// @return     Signed int code
	///
	s16(*Init)(Queue *queue);
	///
	/// @brief      Destroy the list
	///
	/// @param      queue    Queue to destroy
	///
	/// @return     Unsigned int code
	///
	s16(*Destroy)(Queue *queue);
	///
	/// @brief      Insert a node in a position of the queue
	///
	/// @param      queue    Queue to insert the node
	///
	/// @param			value 	Node to insert
	///
	/// @return     Signed int code
	///
	s16(*Enqueue)(Queue *queue, MemoryNode *value);
	///
	/// @brief      Extract a node in a position of the queue
	///
	/// @param      queue    Queue to insert the node
	///
	/// @return     Pointer to the memory node extracted
	///
	MemoryNode*(*Dequeue)(Queue *queue);
	///
	/// @brief      Print the values of the queue
	///
	/// @param      queue    Queue to print
	///
	/// @return     Void
	///
  void(*Print)(Queue *queue);
};
	///
	/// @brief      Create the queue and assing them in a position in memory
	///
	/// @return     Pointer to the queue created
	///
Queue* QUEUE_Create();
//

#endif //_ADT_QUEUE_H_
