#include <stdio.h>
#include "LUT.h"

LUT* initLUT(){
	LUT* list = (LUT*) malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	return list;
}

bool IsLUTEmpty(LUT* list){
	return (list->next == NULL);
}

void addLUT(LUT* list, int lut[256]){
	int i;
	if (list == NULL) 
		return;
	if (IsLUTEmpty(list)){
		list->next = list;
		list->prev = list;
		for (i = 0; i < 256; i++)
			list->lut[i] = lut[i];
		return;
	}
	if (list->next == list)	{
		LUT* newNode = (LUT*) malloc(sizeof(LUT));
		newNode->prev = list;
		newNode->next = list;
		list->next = newNode;
		list->prev = newNode;
		for (i = 0; i < 256; i++)
			newNode->lut[i] = lut[i];
		return;
	}
	LUT* newNode = (LUT*) malloc(sizeof(LUT));
	newNode->next = list;
	newNode->prev = list->prev;
	list->prev->next = newNode;
	list->prev = newNode;
	for (i = 0; i < 256; i++)
		newNode->lut[i] = lut[i];
}

void deleteLUT(LUT* list){
	if (list == NULL) 
		return;
	if (IsLUTEmpty(list) == true) 
		return;
	if (list->next == list){
		list->next = NULL;
		list->prev = NULL;
	}
	LUT* old_last = list->prev;
	list->prev->prev = list;
	list->prev = old_last->prev;
	free(old_last);
}



int* INVERT(LUT* L){
 	int i;
 	for (i = 0; i < 256; i++){
 		L->lut[i] = 255 - i;
 	}
 	return L->lut;
 }

int* ADDLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		L->lut[i] = i + l;
 	}
 	return L->lut;
 }

int* DIMLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		L->lut[i] = i - l;
 	}
 	return L->lut;
}

int* ADDCON(LUT* L, int c){
 	int i;
 	for (i = 0; i < 256; i++){
 		L->lut[i] = (-(127 - i) * c) + 127;
 	}
 	return L->lut;
}

int* DIMCON(LUT* L, int c){
 	int i;
 	if(c != 0){
	 	for (i = 0; i < 256; i++){
	 		L->lut[i] = (-(127 - i) * (1 / c)) + 127;
	 	}
	}
 	return L->lut;
}
 

 void fusionnerLut(LUT* L1, LUT* L2, int* lutC){
	int i;
	for(i=0; i < 256; i++){
		lutC[i] = L2->lut[L1->lut[i]];
	}
}


void FreeLUT(LUT* L){
	free(L->prev);
	L->prev = NULL;
	free(L->next);
	L->next = NULL;
	printf("FreeLUT OK\n");
}
