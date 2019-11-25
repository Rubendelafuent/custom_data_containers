// adt_list.c : Defines the entry point for the console application.
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2016/2017
//
#include "adt_list.h"
#include "memory_node.h"
#include "adt_queue.h"
#include "common_def.h"

static s16 QUEUE_Init(Queue *queue);
static s16 QUEUE_Destroy(Queue *queue);
static s16 QUEUE_Enqueue(Queue *queue, MemoryNode *value);
static MemoryNode *QUEUE_Dequeue(Queue *queue);
static void QUEUE_Print(Queue *queue);

struct adt_queue_ops_s adt_queue_ops = {

  .Init = QUEUE_Init,
  .Destroy = QUEUE_Destroy,
  .Enqueue = QUEUE_Enqueue,
  .Dequeue = QUEUE_Dequeue,
  .Print = QUEUE_Print,

};

Queue* QUEUE_Create(){
	Queue* pQueue = (Queue*) malloc(sizeof(Queue));
	if(QUEUE_Init(pQueue) == 0){
		pQueue->list_ = LIST_Create();
		return pQueue;
	}
	#ifdef VERBOSE_
  		printf("Error: [%s] NULL\n",__FUNCTION__);
	#endif
  return NULL;
}

s16 QUEUE_Init(Queue *queue){
	queue->ops_ = &adt_queue_ops;
	if(queue == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return kErrorCode_Ok;
}

s16 QUEUE_Destroy(Queue *queue){
  if(queue == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
  }
	queue->list_->ops_->Destroy(queue->list_);
  free(queue);
	return kErrorCode_Ok;
}



s16 QUEUE_Enqueue(Queue *queue, MemoryNode *value){
	if(queue == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(value == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return queue->list_->ops_->InsertLast(queue->list_, value);
}

MemoryNode* QUEUE_Dequeue(Queue *queue){
	if(queue == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	return queue->list_->ops_->ExtractFirst(queue->list_);
}

void QUEUE_Print(Queue *queue){
  if(queue == NULL){
    #ifdef VERBOSE_
      printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
		return;
  }
  queue->list_->ops_->Print(queue->list_);
}
