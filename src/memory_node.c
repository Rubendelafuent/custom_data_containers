// memory_node.c :
// Toni Barella
// Algoritmos & Inteligencia Artificial
// ESAT 2016/2017
//

#include <stdio.h>
#include <stdlib.h>

#include "memory_node.h"
#include "common_def.h"

static s16 MEMNODE_Init(MemoryNode *node);
static void* MEMNODE_Data(MemoryNode *node); // returns a reference to data_
static u16 MEMNODE_Size(MemoryNode *node); // returns data size
//static s16 MEMNODE_setData(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_MemSet(MemoryNode *node, u8 value);
static s16 MEMNODE_MemCopy(MemoryNode *node, void *src, u16 bytes);
static s16 MEMNODE_MemConcat(MemoryNode *node, void *src, u16 bytes);
static void MEMNODE_Print(MemoryNode *node);
static s16 MEMNODE_Destroy(MemoryNode *node);

struct memory_node_ops_s memory_node_ops =
{
	.Init = MEMNODE_Init,
	.Data = MEMNODE_Data,
	.Size = MEMNODE_Size,
	.MemSet = MEMNODE_MemSet,
	.MemCopy = MEMNODE_MemCopy,
	.MemConcat = MEMNODE_MemConcat,
	.Print = MEMNODE_Print,
	.Destroy = MEMNODE_Destroy,
};

MemoryNode* MEMNODE_Create()
{
	MemoryNode* pntNode =  (MemoryNode*) malloc(sizeof(MemoryNode));
	if(pntNode == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	MEMNODE_Init(pntNode);
	return pntNode;
}

s16 MEMNODE_CreateFromRef(MemoryNode **node)
{
	*node =  (MemoryNode*) malloc(sizeof(MemoryNode));
	MEMNODE_Init((*node));
	if(node == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
      	return kErrorCode_Null;
	}
	return kErrorCode_Ok;
}

s16 MEMNODE_Init(MemoryNode *node)
{
	if(node == NULL){
		#ifdef VERBOSE_
					printf("Error: [%s] NULL\n",__FUNCTION__);
			#endif
		return kErrorCode_Null;
	}
	node->data_ = NULL;
	node->size_ = 0;
	node->next_ = NULL;
	node->previous_ = NULL;
	node->ops_ = &memory_node_ops;
	return kErrorCode_Ok;
}

s16 MEMNODE_Reset(MemoryNode *node)
{
	if(node == NULL){
		#ifdef VERBOSE_
					printf("Error: [%s] NULL\n",__FUNCTION__);
			#endif
		return kErrorCode_Null;
	}
	MEMNODE_Init(node);
	return kErrorCode_Ok;
}

void* MEMNODE_Data(MemoryNode *node)
{
	return node->data_;
}

u16	MEMNODE_Size(MemoryNode *node)
{
	return node->size_;
}

s16 MEMNODE_MemSet(MemoryNode *node, u8 value){
	if(node == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
      	return kErrorCode_Null;
	}
	memset((u8*)node->data_, value, node->size_);
	return kErrorCode_Ok;
}

s16 MEMNODE_MemCopy(MemoryNode *node, void *src, u16 bytes){
	if(node == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
      	return kErrorCode_Null;
	}
	if(src == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
      	return kErrorCode_Null;
	}
	if(bytes < 0){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(bytes < 0 ){
		#ifdef VERBOSE_
      		printf("Error: [%s] OUT OF INDEX\n",__FUNCTION__);
    	#endif
		return kErrorCode_OutOfIndex;
	}
	if(node->data_ == NULL){
		node->size_ = bytes;
		node->data_ = malloc(bytes);
		memcpy(node->data_, src, node->size_);
	 	return kErrorCode_Ok;
	}
	if(node->data_ != NULL){
		free(node->data_);
		node->size_ = bytes;
		node->data_ = malloc(bytes);
		memcpy(node->data_, src, node->size_);
		return kErrorCode_Ok;
	}
	#ifdef VERBOSE_
    	printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
	return kErrorCode_Null;
}

s16 MEMNODE_MemConcat(MemoryNode *node, void *src, u16 bytes){
	if(node == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(node != NULL){
		if(node->data_ == NULL && src != NULL){
			node->ops_->MemCopy(node->data_, src, bytes);
		}
		if(node->data_ != NULL && src != NULL){
			MemoryNode *newNode = MEMNODE_Create();
			newNode->data_ = malloc(node->size_ + bytes);
			u8 *ptrNode = newNode->data_;
			ptrNode += newNode->size_ - bytes;
			node->size_ += bytes;
			newNode->ops_->MemCopy(newNode->data_, node->data_, node->size_);
			memcpy(ptrNode, src, bytes);
			free(node->data_);
			node->data_ = newNode->data_;
		}
		if(node->data_ != NULL){
			return kErrorCode_Ok;
		}
		if(node->data_ == NULL){
			#ifdef VERBOSE_
      			printf("Error: [%s] NULL\n",__FUNCTION__);
    		#endif
			return kErrorCode_Null;
		}
	}
	#ifdef VERBOSE_
    	printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
    return kErrorCode_Null;
}

void MEMNODE_Print(MemoryNode *node){
	if(node != NULL){
		printf("\nNode values: ");
		u8 *to_print = (u8*)node->data_;
		for(int i = 0; i < (node->size_ / sizeof(*to_print)); i++){
			printf("Node %d = [%X]", i, to_print[i]);
		}
		printf("Size = %d\n", node->ops_->Size(node));
	}else{
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
	}
	printf("\n");
}
s16 MEMNODE_Destroy(MemoryNode * node){
	if(node == NULL){
		#ifdef VERBOSE_
				printf("Error: [%s] NODE NULL\n",__FUNCTION__);
		#endif
		return kErrorCode_Null;
	}
	free(node->data_);
	free(node);
	return kErrorCode_Ok;

}
