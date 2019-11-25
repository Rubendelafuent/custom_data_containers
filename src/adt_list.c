#include "adt_list.h"
#include "memory_node.h"
#include "common_def.h"

static s16 LIST_Init(List *list);
static s16 LIST_Destroy(List *list);
static bool LIST_isEmpty(List *list);
static u16 LIST_Length(List *list);
static s16 LIST_InsertFirst(List *list, MemoryNode *value);
static s16 LIST_InsertLast(List *list, MemoryNode *value);
static s16 LIST_Insert(List *list, MemoryNode *value, u16 index);
static MemoryNode *LIST_Head(List *list);
static MemoryNode *LIST_ExtractFirst(List *list);
static MemoryNode *LIST_ExtractLast(List *list);
static MemoryNode *LIST_Extract(List *list, u16 index);
static s16 LIST_Concat(List *source, List *dest);
static u16 LIST_Traverse(List *list, void(*callback) (MemoryNode *));
static void LIST_Print(List *list);

struct adt_list_ops_s adt_list_ops = {

  .Init = LIST_Init,
  .Destroy = LIST_Destroy,
  .isEmpty = LIST_isEmpty,
  .Length = LIST_Length,
  .InsertFirst = LIST_InsertFirst,
  .InsertLast = LIST_InsertLast,
  .Insert = LIST_Insert,
  .Head = LIST_Head,
  .ExtractFirst = LIST_ExtractFirst,
  .ExtractLast = LIST_ExtractLast,
  .Extract = LIST_Extract,
  .Concat = LIST_Concat,
  .Traverse = LIST_Traverse,
  .Print = LIST_Print,

};

List* LIST_Create(){
	List* pList = NULL;
  pList = (List*) malloc(sizeof(List));
  if(pList != NULL){
    LIST_Init(pList);
  }
  return pList;
}

s16 LIST_Init(List *list){
  list->head_ = NULL;
  list->tail_ = NULL;
	list->length_ = 0;
	list->ops_ = &adt_list_ops;
	if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return kErrorCode_Null;
	}
	return kErrorCode_Ok;
}

s16 LIST_Destroy(List *list){
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

bool LIST_isEmpty(List* list) {
	if (list->head_ == NULL) {
		printf("The list is empty\n");
		return true;
	}

	printf("The list is not empty");
	return false;
}

u16 LIST_Length(List *list){
  if (list == NULL) {
    #ifdef VERBOSE_
        printf("Error: [%s] NULL\n", __FUNCTION__);
    #endif
    return kErrorCode_Null;
  }
  return list->length_;
}

s16 LIST_InsertFirst(List *list, MemoryNode *value){
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
      list->length_ ++;
	return kErrorCode_Ok;
}

s16 LIST_InsertLast(List *list, MemoryNode *value){
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
		ptrNode->next_ = newNode;
    list->length_ ++;
		return kErrorCode_Ok;
	}
}

s16 LIST_Insert(List *list, MemoryNode *value, u16 index){
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
        list->length_ ++;
				return kErrorCode_Ok;
			}
		}
		MemoryNode* newAuxNode = ptrNode->next_;
		newNode->next_ = newAuxNode;
    ptrNode->next_ = newNode;
    list->length_ ++;
		return kErrorCode_Ok;
	}
}

MemoryNode* LIST_Head(List* list) {
	if (list == NULL) {
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
    	#endif
		return NULL;
	}
	return list->head_;
}

MemoryNode* LIST_ExtractFirst(List *list){
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
        free(memNodeDel);
			}else{
        free(list->head_);
        list->tail_ = NULL;
        list->head_ = NULL;
			}
      list->length_ --;
			return auxMemNode;
		}
	}
}

MemoryNode* LIST_ExtractLast(List *list){
	if(list == NULL){
		#ifdef VERBOSE_
      		printf("Error: [%s] NULL\n",__FUNCTION__);
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

MemoryNode* LIST_Extract(List *list, u16 index){
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
		auxMemNode = LIST_ExtractFirst(list);
		return auxMemNode;
	}
	if(index == 0){
		MemoryNode* auxMemNode = MEMNODE_Create();
		auxMemNode = LIST_ExtractFirst(list);
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
    auxMemNode = LIST_ExtractLast(list);
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

s16 LIST_Concat(List *source, List *dest){
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
  dest->tail_ = source->tail_;
  dest->length_ = dest->length_ + source->length_;
  free(source);
	return kErrorCode_Ok;
}

u16 LIST_Traverse(List *list, void(*callback) (MemoryNode *)){
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

void LIST_Print(List *list){
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
  }else{
    u16 i = 0;
    for(MemoryNode *it=list->head_;it!=NULL;it=it->next_){
      printf("---------------------------\n" );
      printf("Position: %d\n",i);
      it->ops_->Print(it);
      if(it->next_ != NULL){
        printf("NEXT: I'm linked with someone\n");
      }else{
        printf("NEXT: I'm linked with the void(NULL)\n");
      }
      printf("---------------------------\n");
      ++i;
    }
  }
}
