#include <stdio.h>
#include "memory_node.h"
#include "adt_vector.h"
#include "adt_list.h"
#include "adt_d_list.h"
#include "adt_stack.h"
#include "adt_queue.h"

int main()
{
	MemoryNode* node = MEMNODE_Create();
	node->ops_->Destroy(node);
	Vector* vector = VECTOR_Create(10000);
	vector->ops_->Destroy(vector);
	List* list = LIST_Create();
	list->ops_->Destroy(list);
	DList* d_list = D_LIST_Create();
	d_list->ops_->Destroy(d_list);
	Stack* stack = STACK_Create();
	stack->ops_->Destroy(stack);
	Queue* queue = QUEUE_Create();
	queue->ops_->Destroy(queue);
	return 0;
}
