#include "adt_vector.h"
#include "memory_node.h"
#include "adt_stack.h"
#include "common_def.h"

static s16 STACK_Init(Stack *stack);
static s16 STACK_Destroy(Stack *stack);
static s16 STACK_Push(Stack *stack, MemoryNode *value);
static MemoryNode *STACK_Pop(Stack *stack);
static void STACK_Print(Stack *stack);

struct adt_stack_ops_s adt_stack_ops = {

  .Init = STACK_Init,
  .Destroy = STACK_Destroy,
  .Push = STACK_Push,
  .Pop = STACK_Pop,
  .Print = STACK_Print,

};

Stack* STACK_Create(u8 capacity){
	Stack* pStack = (Stack*) malloc(sizeof(Stack));
	if(STACK_Init(pStack) == 0){
		pStack->vector_ = VECTOR_Create(capacity);
		return pStack;
	}
  #ifdef VERBOSE_
        printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
  return NULL;
}

s16 STACK_Init(Stack *stack){
	stack->ops_ = &adt_stack_ops;
	if(stack == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return kErrorCode_Ok;
}

s16 STACK_Destroy(Stack *stack){
  if(stack == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
	  return kErrorCode_Null;
  }

	stack->vector_->ops_->Destroy(stack->vector_);
  free(stack);
	return kErrorCode_Ok;
}

s16 STACK_Push(Stack *stack, MemoryNode *value){
	if(stack == NULL){
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
	return stack->vector_->ops_->InsertLast(stack->vector_, value);
}

MemoryNode* STACK_Pop(Stack *stack){
	if(stack == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	return stack->vector_->ops_->ExtractLast(stack->vector_);
}

void STACK_Print(Stack *stack){
  if(stack == NULL){
    #ifdef VERBOSE_
      printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
		return;
  }
  stack->vector_->ops_->Print(stack->vector_);
}
