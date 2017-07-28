#include "queue.h"

int main(void){
	queuerep_t* qr = QinitQueueRep();
	queuerep_t* qr2 = QinitQueueRep();

	for (int i = 1 ; i <= 100000000; i++){
		Qadd(qr,i);
	}
	
	QprintDiag(qr);
	
	return 0;
}
