
#include "LUT.h"

void MakeLUT(LUT* list){
	if(!list)
		return;
	list->prev = NULL;
	list->next = NULL;
}

bool LUTIsEmpty(LUT* list){
	return (list->next == NULL);
}
