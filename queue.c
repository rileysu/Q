#include "queue.h"

queuerep_t* QinitQueueRep(){
	queuerep_t* qr = malloc(sizeof(queuerep_t));

	qr->head = NULL;
	qr->tail = NULL;
	qr->size = 0;

	return qr;	
}

queuenode_t* QinitQueueNode(){
	queuenode_t* qn = malloc(sizeof(queuenode_t));

	qn->data = 0;
	qn->next = NULL;

	return qn;
}

void Qadd(queuerep_t* qr, int data){
	assert(qr != NULL);

	if (QisEmpty(qr)){
		qr->tail = QinitQueueNode();
		qr->head = qr->tail;
	}
	else{
		qr->tail->next = QinitQueueNode();
		qr->tail = qr->tail->next;
	}

	qr->tail->data = data;
	qr->size++;
}

void QaddAll(queuerep_t* qrnew, queuerep_t* qrold){
	assert( (qrnew != NULL) && (qrold != NULL) );
	while(!QisEmpty(qrold)){
		Qadd(qrnew,Qpoll(qrold));
	}
}

void QcopyAll(queuerep_t* qrnew, queuerep_t* qrold){
        assert( (qrnew != NULL) && (qrold != NULL) );

        queuenode_t* curr = qrold->head;

        while(curr != NULL){
		Qadd(qrnew,curr->data);
		curr = curr->next;
        }
}


int Qpeek(queuerep_t* qr){
	assert ( (qr != NULL) && (qr->head != NULL) );

	return qr->head->data;	
}

int Qpoll(queuerep_t* qr){
	assert ( (qr != NULL) && (qr->head != NULL) );

	queuenode_t* curr = qr->head;
	int data = curr->data;

	qr->head = qr->head->next;
	free(curr);
	qr->size--;

	if (qr->head == NULL || qr->head->next == NULL){ // Do not like this conditional
		qr->tail = qr->head;
	}

	return data;
}

void Qclear(queuerep_t* qr){
	assert(qr != NULL);
	queuenode_t* curr = qr->head;
	
	for (int i = 0; i < qr->size; i++){
		queuenode_t* temp = qr->head;
		curr = curr->next;
		qr->head = curr;
		free(temp);
	}
	
	qr->head = NULL;
	qr->tail = NULL;
	qr->size = 0;
}

void QfreeAll(queuerep_t* qr){
	assert(qr != NULL);
	Qclear(qr);
	free(qr);
}

int Qcontains(queuerep_t* qr, int data){
	assert(qr != NULL);
	queuenode_t* curr = qr->head;
	int found = 0;

	while (curr != NULL && found != 1){
		if (curr->data == data){
			found = 1;
		}
		else{
			curr = curr->next;
		}
	}

	return found;
}

int QcontainsCount(queuerep_t* qr, int data){
	assert(qr != NULL);
	queuenode_t* curr = qr->head;
	int found = 0;

	for (int i = 0; i < qr->size; i++){
		if (curr->data == data){
			found++;
		}
		curr = curr->next;
	}

	return found;
}

int QisEmpty(queuerep_t* qr){
	assert(qr != NULL);
	if (qr->head == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void Qremove(queuerep_t* qr, queuenode_t* qnpre, queuenode_t* qnrem){
	assert( (qr != NULL) && (qnrem != NULL) );

	if (qnpre == NULL){
		qnpre = qnrem;
		qnrem = qnrem->next;
		free(qnpre);
		qr->head = qnrem;
		if (qr->head == NULL){
			qr->tail = NULL;
		}
		qr->size--;
	}
	else{
		qnpre->next = qnrem->next;
		if (qr->tail == qnrem){
			qr->tail = qnpre;
		}
		free(qnrem);
		qr->size--;
	}
}

void QremoveIfPresent(queuerep_t* qr, int data){
	assert(qr != NULL);
	while (qr->head->data == data){
		Qremove(qr,NULL,qr->head);
	}

	queuenode_t* pre = qr->head;

	for (int i = 0; i < qr->size - 1; i++){
		if (pre->next->data == data){
			Qremove(qr,pre,pre->next);
		}
	
		pre = pre->next;		
	}
}

void QremoveAllIfPresent(queuerep_t* qrto, queuerep_t* qrfrom){
	assert( (qrto != NULL) && (qrfrom != NULL));
	queuenode_t* curr = qrfrom->head;

	for (int i = 0; i < qrfrom->size; i++){
		QremoveIfPresent(qrto,curr->data);
		curr = curr->next;
	}
}

int Qsize(queuerep_t* qr){
	assert(qr != NULL);
	return qr->size;
}

//DIAG

void QprintDiag(queuerep_t* qr){
	assert(qr != NULL);
	printf("------------------------------\n");
	
	printf("Queue Data:");
	
	queuenode_t* curr = qr->head;

	while (curr != NULL){
		printf(" %d",curr->data);
		curr = curr->next;
	}
	printf("\n");
	if (!QisEmpty(qr)){
		printf("Queue Head: %d\n",qr->head->data);
		printf("Queue Tail: %d\n",qr->tail->data);
		printf("Queue Size: %d\n",qr->size);
	}
	else{
		printf("Queue Empty!\n");
		printf("Queue Size: %d\n",qr->size);
	}

	printf("------------------------------\n");
}
