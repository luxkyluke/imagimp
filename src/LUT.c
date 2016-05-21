#include <stdio.h>
#include "LUT.h"
#include "Pixel.h"

static unsigned int indice_courant = 0;


LUT* makeLUT(){
	LUT* list = (LUT*) malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	list->id = indice_courant++;
	return list;
}

bool LUTIsEmpty(LUT* list){
	if(list->next == NULL)
		return true;
	return false;
}

LUT* getLUTById(LUT* l, int id){
	if (!l)
		return NULL;
	LUT *tmp = l;
	while (tmp != NULL) {
		if (tmp->id == id)
			return tmp;
		tmp = tmp->next;
	}
	fprintf(stderr, "Indice du LUT introuvable\n");
	fflush(stdin);
	return NULL;
}

void addLUT(LUT* list, int lut[256]){
	int i;
	if (list == NULL) 
		return;
	if (LUTIsEmpty(list) == true){
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
	if (LUTIsEmpty(list) == true)
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



void INVERT(LUT* L){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = 255 - i;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 }

void ADDLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = i + l;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 }

void DIMLUM(LUT* L, int l){
 	ADDLUM(L, -l);
}

void ADDCON(LUT* L, int c){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = (-(127 - i) * c) + 127;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
}

void DIMCON(LUT* L, int c){
	ADDCON(L, -c);
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
	if(!L)
		return;
	LUT* tmp = L->next;
	LUT* next;
	while(tmp != NULL && tmp != L){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	printf("FreeLUT OK\n");
}



