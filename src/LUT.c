#include <stdio.h>
#include "LUT.h"
#include "Pixel.h"

LUT* makeLUT(){
	LUT* list = (LUT*) malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	return list;
}

bool IsLUTEmpty(LUT* list){
	if(list->next == NULL)
		return true;
	return false;
}

void addLUT(LUT* list, int lut[256]){
	int i;
	if (list == NULL) 
		return;
	if (IsLUTEmpty(list) == true){
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
		return;
	}
	LUT* old_last = list->prev;
	list->prev->prev = list;
	list->prev = old_last->prev;
	free(old_last);
}



int* INVERT(LUT* L){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = 255 - i;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	return L->lut;
 }

int* ADDLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = i + l;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	return L->lut;
 }

int* DIMLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = i - l;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	return L->lut;
}

int* ADDCON(LUT* L, int c){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = (-(127 - i) * c) + 127;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	return L->lut;
}

int* DIMCON(LUT* L, int c){
 	int i;
 	if(c != 0){
	 	for (i = 0; i < 256; i++){
	 		int value = (-(127 - i) * (1 / c)) + 127;
	 		checkValue(&value);
	 		L->lut[i] = value;
	 	}
	}
 	return L->lut;
}
 
void fusionnerLut(LUT* l){
 	int i;
	LUT *next, *l_tmp= l->next;
	while(l_tmp != NULL && l_tmp != l){
		for(i=0; i < 256; i++){
			checkValue(&(l->lut[i]));
			checkValue(&(l_tmp->lut[l->lut[i]]));
			l->lut[i] = l_tmp->lut[l->lut[i]];
		}
		next = l_tmp->next;
		deleteLUT(l_tmp);
		l_tmp = next;
	}
}


void freeLUT(LUT* L){
	LUT* tmp = L->next;
	LUT* next;
	while(tmp != NULL && tmp != L){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	printf("FreeLUT OK\n");
}



