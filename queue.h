// Author: Riley Sutton
// Date: 2017-07-29
// Description: First attempt at a Queue library

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	int data;
	struct QueueNode* next;
} queuenode_t;

typedef struct QueueRep{
	struct QueueNode* head;
	struct QueueNode* tail;
	int size;
} queuerep_t;

queuerep_t* QinitQueueRep();
queuenode_t* QinitQueueNode();

void Qadd(queuerep_t* qr, int data);
void QaddAll(queuerep_t* qrnew, queuerep_t* qrold);
void QcopyAll(queuerep_t* qrnew, queuerep_t* qrold);
int Qpeek(queuerep_t* qr);
int Qpoll(queuerep_t* qr);
void Qclear(queuerep_t* qr);
void QfreeAll(queuerep_t* qr);
int Qcontains(queuerep_t* qr, int data);
int QcontainsCount(queuerep_t* qr, int data);
//int QcontainsAll(queuerep_t* qrto, queuerep_t* qrfrom);
int QisEmpty(queuerep_t* qr);
void Qremove(queuerep_t* qr, queuenode_t* qnpre, queuenode_t* qnrem);
void QremoveIfPresent(queuerep_t* qr, int data);
void QremoveAllIfPresent(queuerep_t* qrto, queuerep_t* qrfrom);
int Qsize(queuerep_t* qr);

//DIAG
void QprintDiag(queuerep_t* qr);
