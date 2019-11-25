#include "adt_vector.h"
#include "common_def.h"

static s16 VECTOR_Init(Vector *vector);
static u16 VECTOR_Capacity(Vector *vector);
static s16 VECTOR_Destroy(Vector *vector);
static s16 VECTOR_isEmpty(Vector *vector);
static s16 VECTOR_isFull(Vector *vector);
static u16 VECTOR_Length(Vector *vector);
static u16 VECTOR_Resize(Vector *vector, u16 capacity);
static s16 VECTOR_InsertFirst(Vector *vector, MemoryNode *node);
static s16 VECTOR_InsertLast(Vector *vector, MemoryNode *node);
static s16 VECTOR_Insert(Vector *vector, MemoryNode *node, int index);
static MemoryNode* VECTOR_Head(Vector *vector);
static MemoryNode* VECTOR_ExtractFirst(Vector *vector);
static MemoryNode* VECTOR_ExtractLast(Vector *vector);
static MemoryNode* VECTOR_Extract(Vector *vector, u16 index);
static s16 VECTOR_Concat(Vector *source, Vector *dest);
static u16 VECTOR_Traverse(Vector *vector, void(*callback) (MemoryNode *));
static s16 VECTOR_Print(Vector *vector);

struct vector_ops_s vector_ops =
{
	.Init = VECTOR_Init,
	.Capacity = VECTOR_Capacity,
	.Destroy = VECTOR_Destroy,
	.isEmpty = VECTOR_isEmpty,
	.isFull = VECTOR_isFull,
	.Length = VECTOR_Length,
	.Resize = VECTOR_Resize,
	.InsertFirst = VECTOR_InsertFirst,
	.Insert = VECTOR_Insert,
	.InsertLast = VECTOR_InsertLast,
	.ExtractFirst = VECTOR_ExtractFirst,
	.Extract = VECTOR_Extract,
	.ExtractLast = VECTOR_ExtractLast,
	.Head = VECTOR_Head,
	.Concat = VECTOR_Concat,
	.Traverse = VECTOR_Traverse,
	.Print = VECTOR_Print,
};

Vector* VECTOR_Create(u16 capacity){
	Vector* pVec = (Vector*) malloc(sizeof(Vector));

	if(pVec == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	pVec->capacity_ = capacity;
	VECTOR_Init(pVec);
	return pVec;
}

s16 VECTOR_Init(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	vector->head_ = 0;
	vector->tail_ = 0;
	vector->ops_ = &vector_ops;
	vector->node_ = (MemoryNode*) malloc(sizeof(MemoryNode) * vector->capacity_);

	MemoryNode* ptrNodes = vector->node_;
	for(u16 i = 0; i < vector->capacity_; i++){
		MEMNODE_Reset(ptrNodes);
		++ptrNodes;
	}

	return kErrorCode_Ok;
}

u16 VECTOR_Capacity(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return vector->capacity_;
}

s16 VECTOR_Destroy(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	for(int i = vector->head_;i < vector->tail_; i++){
		free(vector->node_[i].data_);
	}
	free(vector->node_);
	free(vector);
	return kErrorCode_Ok;
}

u16 VECTOR_Length(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return vector->tail_ - vector->head_;
}

s16 VECTOR_isEmpty(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(vector->tail_ < vector->capacity_){
		return kErrorCode_Empty;
	}else{
		return kErrorCode_Full;
	}
}

s16 VECTOR_Insert(Vector *vector, MemoryNode *node, int index){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(node != NULL){
		if(vector->tail_ < vector->capacity_){
			if(index <= vector->tail_){
				if(vector->node_[index].data_ == NULL){
					vector->node_[index].ops_->MemCopy(
						&vector->node_[index],
						node->data_,
						node->size_);
					vector->tail_ += 1;
					return kErrorCode_Ok;
				}
				memcpy(&vector->node_[index + 1],&vector->node_[index],(vector->tail_ - index) * sizeof(MemoryNode));
				vector->node_[index].data_ = NULL;
				vector->node_[index].ops_->MemCopy(
						&vector->node_[index],
						node->data_,
						node->size_
					);
				vector->tail_ += 1;
				return kErrorCode_Ok;
			}else{
				#ifdef VERBOSE_
	      			printf("Error: [%s] OUT OF INDEX\n",__FUNCTION__);
    			#endif
				return kErrorCode_OutOfIndex;
			}
		}else{
			#ifdef VERBOSE_
      			printf("Error: [%s] FULL\n",__FUNCTION__);
    		#endif
			return kErrorCode_Full;
		}
	}else{
		#ifdef VERBOSE_
      		printf("Error: [%s] EMPTY\n",__FUNCTION__);
    	#endif
		return kErrorCode_Empty;
	}
}

s16 VECTOR_InsertFirst(Vector *vector, MemoryNode *node){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(node != NULL){
		if(vector->tail_ < vector->capacity_){
			if(vector->node_->data_ != NULL){

				memcpy(&vector->node_[vector->head_ + 1],&vector->node_[vector->head_],vector->tail_ * sizeof(MemoryNode));
			}

			vector->tail_ += 1;
			vector->node_[vector->head_].data_ = NULL;
			vector->node_[vector->head_].ops_->MemCopy(
				&vector->node_[vector->head_],
				node->data_,
				node->size_);

				return kErrorCode_Ok;
		}else{
			#ifdef VERBOSE_
    				printf("Error: [%s] FULL\n",__FUNCTION__);
    		#endif
			return kErrorCode_Full;
		}
	}else{
		#ifdef VERBOSE_
      		printf("Error: [%s] NODE PARAMETER NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Empty;
	}
}

s16 VECTOR_InsertLast(Vector *vector, MemoryNode *node){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(node != NULL){
		if(vector->tail_ <= vector->capacity_){
			if(vector->node_[vector->tail_].data_ == NULL){
				vector->node_[vector->tail_].ops_->MemCopy(
 					&vector->node_[vector->tail_],
 					node->data_,
 					node->size_);
 				vector->tail_ += 1;
 				return kErrorCode_Ok;
			}
			#ifdef VERBOSE_
      			printf("Error: [%s] FULL\n",__FUNCTION__);
    		#endif
			return kErrorCode_Full;
		}else{
			#ifdef VERBOSE_
      			printf("Error: [%s] FULL\n",__FUNCTION__);
    		#endif
			return kErrorCode_Full;
		}
	}else{
		#ifdef VERBOSE_
      		printf("Error: [%s] EMPTY\n",__FUNCTION__);
    	#endif
		return kErrorCode_Empty;
	}
}

MemoryNode* VECTOR_ExtractFirst(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}

	if(VECTOR_Length(vector) <= 0){
		#ifdef VERBOSE_
					printf("Error: [%s] EMPTY VECTOR\n",__FUNCTION__);
			#endif
		return NULL;
	}
	MemoryNode* ptrExtracted = MEMNODE_Create();
	ptrExtracted->ops_->MemCopy(
		ptrExtracted,
		vector->node_[vector->head_].data_,
		vector->node_[vector->head_].size_
	);

	vector->node_[vector->head_].data_ = NULL;
	if(vector->head_ +1 != vector->tail_){
		memcpy(&vector->node_[vector->head_],&vector->node_[vector->head_ + 1],vector->tail_ * sizeof(MemoryNode));
	}
	vector->node_[vector->tail_ - 1].data_ = NULL;
	vector->tail_ -= 1;
	return ptrExtracted;
}

MemoryNode* VECTOR_ExtractLast(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}

	if(VECTOR_Length(vector) <= 0){
		#ifdef VERBOSE_
					printf("Error: [%s] EMPTY VECTOR\n",__FUNCTION__);
			#endif
		return NULL;
	}

	MemoryNode* ptrExtracted = MEMNODE_Create();
	ptrExtracted->ops_->MemCopy(
		ptrExtracted,
		vector->node_[vector->tail_-1].data_,
		vector->node_[vector->tail_-1].size_
	);

	if(vector != NULL && ptrExtracted != NULL){
		free(vector->node_[vector->tail_-1].data_);
		vector->node_[vector->tail_-1].data_ = NULL;
		vector->tail_ -= 1;
		return ptrExtracted;
	}
	#ifdef VERBOSE_
    	printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
	return NULL;
}

MemoryNode* VECTOR_Extract(Vector *vector, u16 index){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}

	if(VECTOR_Length(vector) <= 0){
		#ifdef VERBOSE_
					printf("Error: [%s] EMPTY VECTOR\n",__FUNCTION__);
			#endif
		return NULL;
	}

	if(index >= VECTOR_Length(vector)){
		#ifdef VERBOSE_
					printf("Error: [%s] INDEX OUT OF RANGE\n",__FUNCTION__);
			#endif
		return NULL;
	}

	MemoryNode* ptrExtracted = MEMNODE_Create();
	ptrExtracted->ops_->MemCopy(
		ptrExtracted,
		vector->node_[index].data_,
		vector->node_[index].size_
	);

		free(vector->node_[index].data_);
		vector->node_[index].data_ = NULL;
		if(index +1 != vector->tail_){
			memcpy(&vector->node_[index],&vector->node_[index + 1],(vector->tail_ - index) * sizeof(MemoryNode));
			vector->node_[vector->tail_-1].data_ = NULL;
		}
		vector->tail_ --;
		return ptrExtracted;
}

u16 VECTOR_Resize(Vector *vector, u16 capacity){
	if(vector == NULL){
		#ifdef VERBOSE_
    		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
    	return kErrorCode_Null;
	}
	if(vector->node_ == NULL){
		#ifdef VERBOSE_
    		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
    	return kErrorCode_Null;
	}

	if(vector->capacity_ > capacity){
		#ifdef VERBOSE_
    		printf("Error: [%s] ERROR CAPACITY\n",__FUNCTION__);
    	#endif
    	return kErrorCode_Null;
	}

	MemoryNode *newNode =  (MemoryNode*)malloc(capacity * sizeof(MemoryNode));
	MemoryNode *newNodeAux = newNode;
  for(u16 i = 0; i < capacity; i++){
		MEMNODE_Reset(newNodeAux);
		newNodeAux++;
	}

  memcpy(newNode,vector->node_,vector->capacity_ * sizeof(MemoryNode));
  free(vector->node_);
  vector->node_ = newNode;
  vector->capacity_ = capacity;

  return kErrorCode_Ok;
}

MemoryNode* VECTOR_Head(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
    		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
    return NULL;
	}
	if(vector->node_ == NULL){
		#ifdef VERBOSE_
    		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
    return NULL;
	}

	if(VECTOR_Length(vector) <= 0){
		#ifdef VERBOSE_
					printf("Error: [%s] EMPTY VECTOR\n",__FUNCTION__);
			#endif
		return NULL;
	}

	return &vector->node_[vector->head_];
}

s16 VECTOR_Concat(Vector *source, Vector *dest){
	if(source == NULL){
		#ifdef VERBOSE_
				printf("Error: [%s] SOURCE NULL\n",__FUNCTION__);
			#endif
			return kErrorCode_Null;
	}

	if(source->node_ == NULL){
		#ifdef VERBOSE_
				printf("Error: [%s] SOURCE NODE NULL\n",__FUNCTION__);
			#endif
			return kErrorCode_Null;
	}

	if(dest == NULL){
		#ifdef VERBOSE_
				printf("Error: [%s] DEST NULL\n",__FUNCTION__);
			#endif
			return kErrorCode_Null;
	}

	if(dest->node_ == NULL){
		#ifdef VERBOSE_
				printf("Error: [%s] DEST NODE NULL\n",__FUNCTION__);
			#endif
			return kErrorCode_Null;
	}

	VECTOR_Resize(dest, dest->capacity_ + source->capacity_);
 	memcpy(&dest->node_[dest->tail_],&source->node_[source->head_],source->tail_ * sizeof(MemoryNode));
	dest->tail_ += source->tail_;
	return kErrorCode_Ok;
 }

u16 VECTOR_Traverse(Vector *vector, void(*callback) (MemoryNode *)){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] VECTOR NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	MemoryNode *newNode = vector->node_;
	for(u16 i = 0; i < vector->tail_; i++){
		callback(&newNode[i]);
	}
	return kErrorCode_Ok;
}

s16 VECTOR_Print(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	printf("\nHEAD: %d", vector->head_);
	printf("\nTAIL: %d\n", vector->tail_);

	if(vector->node_[vector->head_].data_ == NULL){
		printf("\nEMPTY VECTOR\n");
		return kErrorCode_Ok;
	}

	for(u16 i = vector->head_; i < vector->tail_; i++){
		if(vector->node_[i].data_ != NULL){
			vector->node_[i].ops_->Print(&vector->node_[i]);
		}else{
			printf("Node %d = [NULL]\n", i);
		}
	}
	return kErrorCode_Ok;
}

s16 VECTOR_isFull(Vector *vector){
	if(vector == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}

	if(VECTOR_Length(vector) <= 0){
		#ifdef VERBOSE_
      		printf("Error: [%s] EMPTY VECTOR\n",__FUNCTION__);
    	#endif
		return kErrorCode_Empty;
	}

	if(vector->tail_ == vector->capacity_){
		return kErrorCode_Full;
	}
	return kErrorCode_Null;
}
