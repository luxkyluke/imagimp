
#include "LUT.h"

LUT* initLUT(){
	LUT* list = malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	return list;
}

bool LUTIsEmpty(LUT* list){
	return (list->next == NULL);
}

void addNode(LUT* list, int lut[256]){
	int i;
	if (list == NULL) return;
	if (LUTIsEmpty(list)){
		list->next = list;
		list->prev = list;
		for (i = 0; i < 256; i++)
			list->lut[i] = lut[i];
		return;
	}
	if (list->next == list)	{
		LUT* newNode = malloc(sizeof(LUT));
		newNode->prev = list;
		newNode->next = list;
		list->next = newNode;
		list->prev = newNode;
		for (i = 0; i < 256; i++)
			newNode->lut[i] = lut[i];
		return;
	}
	LUT* newNode = malloc(sizeof(LUT));
	newNode->next = list;
	newNode->prev = list->prev;
	list->prev->next = newNode;
	list->prev = newNode;
	for (i = 0; i < 256; i++)
		newNode->lut[i] = lut[i];
}
