#include <stdio.h>
#include "LUT.h"
#include "Pixel.h"
#include <common.h>

static unsigned int indice_courant = 1;


LUT* makeLUT(){
	LUT* list = (LUT*) malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	list->id = indice_courant++;
	initLUT(list->lut);
	return list;
}

void initLUT(int* lut){
	int i;
	for(i=0; i<256; ++i){
		lut[i]=i;
	}
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

int addLUT(LUT* list, int lut[256]){
	int i;
	if (list == NULL)
		return 0;
	if (LUTIsEmpty(list) == true){
		list->next = list;
		list->prev = list;
		for (i = 0; i < 256; i++)
			list->lut[i] = lut[i];
		return list->id;
	}
	if (list->next == list)	{
		LUT* newNode = makeLUT();
		newNode->prev = list;
		newNode->next = list;
		list->next = newNode;
		list->prev = newNode;
		for (i = 0; i < 256; i++)
			newNode->lut[i] = lut[i];
		return newNode->id;
	}
	LUT* newNode = makeLUT();
	newNode->next = list;
	newNode->prev = list->prev;
	list->prev->next = newNode;
	list->prev = newNode;
	for (i = 0; i < 256; i++)
		newNode->lut[i] = lut[i];
	return newNode->id;
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

/*void DIMCON(LUT* L, int c){
	int i; 
 	for (i = 0; i < 256; i++){
 		int value = -c -i +127;
 		checkValue(&value); 
   		L->lut[i] = value; 
 	}  
 	
}*/
void DIMCON(LUT* L, int c){ //c varie entre 0 et 1
	int i; 
	float coef = c/100.;
	for(i = 0; i < 256; i++)  {
		//int value = 128 - (128 - L->lut[i]) * coef;
   		L->lut[i] = 128 - (128 - i) * coef;;
	}
}

LUT* fusionnerLut(LUT* l){
 	if(!l || LUTIsEmpty(l))
 		return l;
	int i;
	LUT *ret= copyLUT(l);
	LUT *l_tmp= l->next;
	while(l_tmp != NULL && l_tmp != l){
		for(i=0; i < 256; i++){
			checkValue(&(ret->lut[i]));
			checkValue(&(l_tmp->lut[ret->lut[i]]));
			ret->lut[i] = l_tmp->lut[ret->lut[i]];
		}
		l_tmp = l_tmp->next;
	}
	return ret;
}

LUT* copyLUT(LUT* l){
	if(!l)
		return NULL;
	LUT* ret = makeLUT();
	int i;
	for(i=0; i<256; ++i){
		ret->lut[i]=l->lut[i];
	}
	return ret;
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




