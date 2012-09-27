#include <stdlib.h>
#include "list.h"
//#include "LocalIncludeFile.h"

PTList List_Init(PTList pPueue) {

	pPueue->first = NULL;
	pPueue->last = NULL;
	pPueue->length = 0;
	sem_init (&(pPueue->list_sem), 0, 1);
	return pPueue;
}

PTList List_Create() {
	//echoic("List_Create");
	return List_Init((PTList) malloc(sizeof(TList)));
}

void List_Destroy(PTList pl) {
	//echoic("List_Destroy");
	if (pl != NULL) {
		sem_wait(&(pl->list_sem));
		PTListItem temp = pl->first;
		PTListItem t;
		while (temp) {
			t = temp;
			temp = temp->next;
			List_Item_Destroy(t);
		}
		sem_post(&(pl->list_sem));
		sem_destroy(&(pl->list_sem));
		free(pl);
		pl = NULL;
	}
}

PTListItem List_Item_Init(PTListItem pti) {

	pti->item = NULL;
	pti->next = NULL;
	pti->prv = NULL;
	pti->destroy_func = NULL;
	return pti;
}
PTListItem List_Item_Create() {
	return List_Item_Init((PTListItem) malloc(sizeof(TListItem)));
}

void List_Item_Destroy(PTListItem pqi) {

	if (pqi != NULL) {

		if (pqi->destroy_func != NULL) {

			pqi->destroy_func(pqi->item);

		}
		free(pqi);
		pqi = NULL;

	}

}
int List_Index(PTList pPueue, int index) {
	if (pPueue == NULL) {
		return -1;
	}
	return index < 0 ? -1 : (index >= pPueue->length ? -1 : index);
}
PTListItem List_Get(PTList pPueue, int index) {
	PTListItem temp = NULL;
	int i = List_Index(pPueue, index);
	if (i < 0) {
		return temp;
	}
	int t = 0;
	if (i <= (pPueue->length / 2)) {
		temp = pPueue->first;
		for (t = 0; t < i; t++) {
			temp = temp->next;
		}
	} else {
		temp = pPueue->last;
		for (t = 0; t < (pPueue->length - 1 - i); t++) {
			temp = temp->prv;
		}
	}
	return temp;
}
int List_GetIndex(PTList pPueue, int index)
{
	//echoic("List_GetIndex");
	if (pPueue == NULL) {
		return -1;
	}
	sem_wait(&(pPueue->list_sem));
	int r = List_Index(pPueue,index);
	sem_post(&(pPueue->list_sem));
	return r;
}
PTListItem List_GetItem(PTList pPueue, int index)
{
	//echoic("List_GetItem");
	
	if (pPueue == NULL) {
	
		return NULL;
	}
	
	sem_wait(&(pPueue->list_sem));
	
	PTListItem temp = List_Get(pPueue,index);
	
	sem_post(&(pPueue->list_sem));
	
	return temp;
}

PTListItem List_Insert(PTList pPueue, void * item, int index) {
	//echoic("List_Insert");
	sem_wait(&(pPueue->list_sem));
	int i = (index >= 0 && index <= pPueue->length) ? index : -1;

	PTListItem temp, Result;
	if (pPueue != NULL) {
		if (i < 0) {
			sem_post(&(pPueue->list_sem));
			return NULL;
		} else if (i == 0) {
			temp = pPueue->first;
			Result = List_Item_Create();
			Result->item = item;
			Result->next = pPueue->first;
			pPueue->first = Result;
			if (pPueue->length == 0) {
				pPueue->last = pPueue->first;
			} else {
				Result->next->prv = Result;
			}
		} else if (i == pPueue->length) {
			Result = List_Item_Create();
			Result->item = item;
			Result->prv = pPueue->last;
			pPueue->last->next = Result;
			pPueue->last = Result;
		} else {
			temp = List_Get(pPueue, index);
			Result = List_Item_Create();
			Result->item = item;
			Result->next = temp;
			Result->prv = temp->prv;
			Result->prv->next = Result;
			Result->next->prv = Result;
		}
		pPueue->length++;
		sem_post(&(pPueue->list_sem));
		return Result;
	}
	sem_post(&(pPueue->list_sem));
	return NULL;
}

void * List_Delete(PTList pPueue, int index) {
	//echoic("List_Delete");
	sem_wait(&(pPueue->list_sem));
	int i = List_Index(pPueue, index);
	PTListItem temp;
	void * Result = NULL;
	if (pPueue != NULL) {
		if (i < 0) {
			sem_post(&(pPueue->list_sem));
			return NULL;
		} else {
			temp = List_Get(pPueue, index);
			if (temp != NULL) {
				pPueue->length--;
				Result = temp->item;
				if (pPueue->first == temp && pPueue->last == temp) {
					pPueue->first = NULL;
					pPueue->last = NULL;
				} else if (pPueue->first == temp) {
					pPueue->first = temp->next;
					pPueue->first->prv = NULL;
				} else if (pPueue->last == temp) {
					pPueue->last = temp->prv;
					pPueue->last->next = NULL;
				} else {
					temp->prv->next = temp->next;
					temp->next->prv = temp->prv;
				}
				List_Item_Destroy(temp);
				sem_post(&(pPueue->list_sem));
				return Result;
			}
		}
	}
	sem_post(&(pPueue->list_sem));
	return NULL;
}
PTQueue Queue_Create() {
	return List_Create();
}
void Queue_Destroy(PTQueue pl) {
	List_Destroy(pl);
}
PTQueueItem Queue_Push(PTQueue pPueue, void * item) {
	return List_Insert(pPueue, item, pPueue->length);
}
void * Queue_Pop(PTQueue pPueue) {

	return List_Delete(pPueue, 0);
}

PTStack Stack_Create() {
	return List_Create();
}
void Stack_Destroy(PTStack pl) {
	List_Destroy(pl);
}
PTStackItem Stack_Push(PTStack pStack, void * item) {
	return List_Insert(pStack, item, 0);
}
void * Stack_Pop(PTStack pStack) {
	return List_Delete(pStack, pStack->length - 1);
}

