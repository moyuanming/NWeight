#ifndef __List_H__
#define __List_H__

//#ifndef NULL
//#define NULL 0
//#endif
#include <semaphore.h>
typedef void (*TItem_Destroy_Func)(void *);
typedef struct list_item {
	struct list_item * next;
	struct list_item * prv;
	void * item;
	TItem_Destroy_Func destroy_func;
} TListItem, TQueueItem, TStackItem;
typedef TListItem * PTListItem;
typedef PTListItem PTQueueItem;
typedef PTListItem PTStackItem;
typedef struct List {
	PTListItem first;
	PTListItem last;
	int length;
	sem_t list_sem;
} TList, TQueue, TStack;
typedef TList * PTList;
typedef PTList PTQueue;
typedef PTList PTStack;

PTList List_Create(void);
PTListItem List_Item_Create(void);
void List_Destroy(PTList pl);
void List_Item_Destroy(PTListItem pqi);
int List_GetIndex(PTList pPueue, int index);
PTListItem List_GetItem(PTList pPueue, int index);
PTListItem List_Insert(PTList pPueue, void * item, int index);
void* List_Delete(PTList pPueue, int index);

PTQueue Queue_Create(void);
void Queue_Destroy(PTQueue pl);
PTQueueItem Queue_Push(PTQueue pPueue, void * item);
void* Queue_Pop(PTQueue pPueue);

PTStack Stack_Create(void);
void Stack_Destroy(PTStack pl);
PTStackItem Stack_Push(PTStack pStack, void * item);
void * Stack_Pop(PTStack pStack);
#endif
