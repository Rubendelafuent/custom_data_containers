#include "adt_d_list.h"
#include "memory_node.h"
#include "common_def.h"

static s16 D_LIST_Init(DList *node);
static s16 D_LIST_Destroy(DList *list);
static bool D_LIST_isEmpty(DList *list);
static u16 D_LIST_Length(DList *list);
static s16 D_LIST_InsertFirst(DList *list, MemoryNode *value);
static s16 D_LIST_InsertLast(DList *list, MemoryNode *value);
static s16 D_LIST_Insert(DList *list, MemoryNode *value, u16 index);
static MemoryNode *D_LIST_Head(DList *list);
static MemoryNode *D_LIST_ExtractFirst(DList *list);
static MemoryNode *D_LIST_ExtractLast(DList *list);
static MemoryNode *D_LIST_Extract(DList *list, u16 index);
static s16 D_LIST_Concat(DList *source, DList *dest);
static u16 D_LIST_Traverse(DList *list, void(*callback) (MemoryNode *));
static void D_LIST_Print(DList *list);
//
struct adt_d_list_ops_s adt_d_list_ops = {

  .Init = D_LIST_Init,
  .Destroy = D_LIST_Destroy,
  .isEmpty = D_LIST_isEmpty,
  .Length = D_LIST_Length,
  .InsertFirst = D_LIST_InsertFirst,
  .InsertLast = D_LIST_InsertLast,
  .Insert = D_LIST_Insert,
  .Head = D_LIST_Head,
  .ExtractFirst = D_LIST_ExtractFirst,
  .ExtractLast = D_LIST_ExtractLast,
  .Extract = D_LIST_Extract,
  .Concat = D_LIST_Concat,
  .Traverse = D_LIST_Traverse,
  .Print = D_LIST_Print,

};

DList* D_LIST_Create(){
  DList* pList = NULL;
  pList = (DList*) malloc(sizeof(DList));
  if(pList != NULL){
    D_LIST_Init(pList);
  }
  return pList;
}

s16 D_LIST_Init(DList *list){
  list->head_ = NULL;
  list->tail_ = NULL;
	list->length_ = 0;
	list->ops_ = &adt_d_list_ops;
	if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
		return kErrorCode_Null;
	}

	return kErrorCode_Ok;
}

s16 D_LIST_Destroy(DList *list){
	if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
  if(list->head_ == NULL){
    free(list);
		return kErrorCode_Ok;
	}
  MemoryNode* newNode = NULL;
  for(newNode = list->head_->next_; newNode != NULL; newNode = newNode->next_){
    list->head_->ops_->Destroy(list->head_);;
    list->head_ = newNode;
  }
  list->head_->ops_->Destroy(list->head_);
  free(list);
	return kErrorCode_Ok;
}

bool D_LIST_isEmpty(DList* list) {
  if (list->head_ == NULL) {
		printf("The list is empty\n");
		return true;
	}

	printf("The list is not empty");
	return false;
}


u16 D_LIST_Length(DList *list){
  return list->length_;
}

s16 D_LIST_InsertFirst(DList *list, MemoryNode *value){
  if(list == NULL){
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
if(list->head_ == NULL){
  MemoryNode* newNode = MEMNODE_Create();
  newNode->ops_->MemCopy(
    newNode,
    value->data_,
    value->size_);
  list->head_ = newNode;
  list->tail_ = newNode;
  list->length_ ++;
  return kErrorCode_Ok;
}
MemoryNode* newNode = MEMNODE_Create();
newNode->ops_->MemCopy(
  newNode,
  value->data_,
  value->size_);
newNode->next_ = list->head_;

list->head_ = newNode;
list->head_->next_->previous_ = newNode;
list->length_ ++;
return kErrorCode_Ok;
}

s16 D_LIST_InsertLast(DList *list, MemoryNode *value){
  if(list == NULL){
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
	if(list->head_ == NULL){
		MemoryNode* newNode = MEMNODE_Create();
		list->head_ = newNode;
		list->head_->ops_->MemCopy(
			list->head_,
			value->data_,
			value->size_);
    list->tail_ = newNode;
		list->head_->next_ = NULL;
    list->length_ ++;
		return kErrorCode_Ok;
	}
	if(list->head_->next_ == NULL){
		MemoryNode* newNode = MEMNODE_Create();
		newNode->ops_->MemCopy(
			newNode,
			value->data_,
			value->size_);
      list->tail_ = newNode;
      list->head_->next_ = newNode;
      newNode->previous_ = list->head_;
      list->length_ ++;
		return kErrorCode_Ok;
	}else{
    MemoryNode* ptrNode = MEMNODE_Create();
    ptrNode = list->head_;
		do{
			ptrNode = ptrNode->next_;
		}while(ptrNode->next_ != NULL);
		MemoryNode* newNode = MEMNODE_Create();
		newNode->ops_->MemCopy(
			newNode,
			value->data_,
			value->size_);
    list->tail_ = newNode;
    list->tail_->previous_ = ptrNode;
		ptrNode->next_ = newNode;
    list->length_ ++;
		return kErrorCode_Ok;
	}
}

s16 D_LIST_Insert(DList *list, MemoryNode *value, u16 index){
  if(list == NULL){
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
	if(index < 0){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
  if(index == list->ops_->Length(list) - 1){
    list->ops_->InsertLast(list, value);
    return kErrorCode_Null;
  }
	if(list->head_ == NULL){
    MemoryNode* newNode = MEMNODE_Create();
		newNode->ops_->MemCopy(
			newNode,
			value->data_,
			value->size_);
    list->tail_ = newNode;
    list->head_ = newNode;
    list->length_ ++;
		return kErrorCode_Ok;
	}
	if(index == 0){
		list->ops_->InsertFirst(list, value);
		return kErrorCode_Ok;
	}else{
		MemoryNode* newNode = MEMNODE_Create();
		newNode->ops_->MemCopy(
			newNode,
			value->data_,
			value->size_);
    MemoryNode* ptrNode = MEMNODE_Create();
    ptrNode = list->head_;
		for(u16 i = 0; i < index-1; i++){
			if(ptrNode->next_ != NULL){
				ptrNode = ptrNode->next_;
			}else{
				ptrNode->next_ = newNode;
        list->tail_ = newNode;
        list->tail_->previous_ = ptrNode;
        list->length_ ++;
				return kErrorCode_Ok;
			}
		}
		MemoryNode* newAuxNode = ptrNode->next_;
		newNode->next_ = newAuxNode;
    ptrNode->next_ = newNode;
    newNode->previous_ = ptrNode;
    list->length_ ++;
		return kErrorCode_Ok;
	}
}

MemoryNode* D_LIST_Head(DList* list) {
  if (list == NULL) {
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}

  return list->head_;
}

MemoryNode* D_LIST_ExtractFirst(DList *list){
  if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}else{
		if(list->head_ == NULL){
			#ifdef VERBOSE_
      			printf("Error: [%s] NULL\n",__FUNCTION__);
    		#endif
			return NULL;
		}else{
			MemoryNode* auxMemNode = MEMNODE_Create();
      MemoryNode* memNodeDel = MEMNODE_Create();
      memNodeDel = list->head_;
			auxMemNode->ops_->MemCopy(
        auxMemNode,
        list->head_->data_,
        list->head_->size_);
			if(list->head_->next_ != NULL){
        list->head_ = list->head_->next_;
        list->head_->previous_ = NULL;
        free(memNodeDel);
			}else{
        free(list->head_);
        list->head_->previous_ = NULL;
        list->tail_ = NULL;
        list->head_ = NULL;
			}
      list->length_ --;
			return auxMemNode;
		}
	}
}

MemoryNode* D_LIST_ExtractLast(DList *list){
  if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	if(list->head_ == NULL){
		#ifdef VERBOSE_
    			printf("Error: [%s] NULL\n",__FUNCTION__);
  		#endif
		return NULL;
	}

  if(list->head_->next_ == NULL){
    free(list->head_);
    list->tail_ = NULL;
    list->head_ = NULL;
    list->length_ --;
    return NULL;
  }

  MemoryNode* newNode = MEMNODE_Create();
  newNode = list->head_;
  for(MemoryNode *it=list->head_;it->next_->next_!=NULL;it=it->next_){
		if(newNode->next_ != NULL){
      newNode = newNode->next_;
		}
  }
	MemoryNode* auxMemNode = MEMNODE_Create();
  auxMemNode = newNode->next_;
  free(newNode->next_);
  list->tail_ = newNode;
  newNode->next_ = NULL;
  list->length_ --;
	return auxMemNode;
}

MemoryNode* D_LIST_Extract(DList *list, u16 index){
  if(index < 0){
		#ifdef VERBOSE_
      		printf("Error: [%s] INDEX ERROR\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] LIST NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	if(list->head_ == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] HEAD NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	if(list->head_->next_ == NULL){
		MemoryNode* auxMemNode = MEMNODE_Create();
		auxMemNode = D_LIST_ExtractFirst(list);
		return auxMemNode;
	}
	if(index == 0){
		MemoryNode* auxMemNode = MEMNODE_Create();
		auxMemNode = D_LIST_ExtractFirst(list);
		return auxMemNode;
	}

	if (index > list->ops_->Length(list)) {
		#ifdef VERBOSE_
      		printf("Error: [%s] INDEX ERROR\n",__FUNCTION__);
    	#endif
		return NULL;
	}
  if(index == list->ops_->Length(list) -1){
    MemoryNode* auxMemNode = MEMNODE_Create();
    auxMemNode = D_LIST_ExtractLast(list);
    return auxMemNode;
  }
  MemoryNode* newNode = MEMNODE_Create();
  newNode = list->head_;
	for (u16 i = 0; i < index; ++i) {
	  if (newNode->next_ != NULL) {
		  if (i + 1 == index) {
		    MemoryNode* auxMemNode = MEMNODE_Create();
		    MemoryNode* auxMemNodeDel = MEMNODE_Create();
        auxMemNodeDel = newNode->next_;
        auxMemNode->ops_->MemCopy(
          auxMemNode,
          newNode->next_->data_,
          newNode->next_->size_
        );
        newNode->next_ = newNode->next_->next_;
        newNode->next_->previous_ = newNode;
        free(auxMemNodeDel);
        list->length_ --;
				return auxMemNode;
			}
		}
    newNode = newNode->next_;
	}
	#ifdef VERBOSE_
    	printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
	return NULL;
}

s16 D_LIST_Concat(DList *source, DList *dest){
  if(source == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	if(dest == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
  dest->tail_->next_ = source->head_;
  source->head_->previous_ = dest->tail_;
  dest->tail_ = source->tail_;
  dest->length_ = dest->length_ + source->length_;
  free(source);
	return kErrorCode_Ok;
}

u16 D_LIST_Traverse(DList *list, void(*callback) (MemoryNode *)){
  if(list == NULL){
    #ifdef VERBOSE_
      printf("Error: [%s] LIST NULL\n",__FUNCTION__);
    #endif
    return kErrorCode_Null;
  }
  if(list->head_ == NULL){
    #ifdef VERBOSE_
      printf("Error: [%s] HEAD NULL\n",__FUNCTION__);
    #endif
    return kErrorCode_Null;
  }
	MemoryNode *newNode = NULL;
	for(newNode = list->head_; newNode != NULL; newNode = newNode->next_){
		callback(newNode);
	}
	return kErrorCode_Ok;
}

void D_LIST_Print(DList *list){
  if(list == NULL){
    #ifdef VERBOSE_
      printf("Error: [%s] NULL\n",__FUNCTION__);
    #endif
    return;
  }

  if(list->head_ == NULL){
    printf("---------------------------\n" );
    printf("EMPTY LIST\n");
    printf("---------------------------\n" );
    return;
  }

  u16 i = 0;
  for(MemoryNode *it=list->head_;it!=NULL;it=it->next_){
    printf("---------------------------\n" );
    printf("Position: %d\n",i);
    it->ops_->Print(it);
    if(it->previous_ != NULL){
      printf("PREV: I'm linked with PREVIOUS\n");
    }
    else{
      printf("PREV: I'm not linked(NULL)\n");
    }
    if(it->next_ != NULL){
      printf("NEXT: I'm linked with NEXT\n");
    }else{
      printf("NEXT: I'm linked with the void(NULL)\n");
    }
    printf("---------------------------\n");
    ++i;
  }
}
