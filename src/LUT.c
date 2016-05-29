#include <stdio.h>
#include "LUT.h"
#include "Pixel.h"
#include <common.h>
#include "LutOption.h"


LUT* makeLUT(){
	LUT* list = (LUT*) malloc(sizeof(LUT));
	if(!list)
		return NULL;
	list->prev = NULL;
	list->next = NULL;
	list->type = aucun;
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

bool existLUTByType(LUT* l, LutOption type){
	if (!l || LUTIsEmpty(l))
		return false;
	LUT *tmp = l;
	while (tmp != NULL) {
		if (tmp->type == type)
			return true;
		tmp=tmp->next;
		if(tmp == l)
			break;
	}
	return false;
}

void removeLUTByType(LUT* l, LutOption type){
	if (!l || LUTIsEmpty(l))
		return;
	LUT *tmp = l;
	while (tmp != NULL) {
		if (tmp->type == type) {
			printf("delete\n");
			deleteLUT(tmp);
			return;
		}
		tmp=tmp->next;
		if(tmp == l)
			break;
	}
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
	}
	if (list->next == list)	{
		LUT* newNode = makeLUT();
		newNode->prev = list;
		newNode->next = list;
		list->next = newNode;
		list->prev = newNode;
		for (i = 0; i < 256; i++)
			newNode->lut[i] = lut[i];
	}
	LUT* newNode = makeLUT();
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
 	L->type = invert;
 }

void ADDLUM(LUT* L, int l){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = i + l;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	L->type = addlum;
 }

void DIMLUM(LUT* L, int l){
 	ADDLUM(L, -l);
 	L->type = dimlum;
}

void ADDCON(LUT* L, int c){
 	int i;
 	for (i = 0; i < 256; i++){
 		int value = (-(127 - i) * c) + 127;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	L->type = addcon;
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
	L->type = dimcon;
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
	ret->type = l->type;
	return ret;
}


void freeLUT (LUT** liste){
	if(liste != NULL && *liste != NULL ){
		viderLUT(*liste);
    	free(*liste);
    	*liste = NULL;
    }
//	printf("FreeLUT OK\n");
}


void viderLUT (LUT* liste){
	if(!liste)
		return;
    LUT *it, *next;

    for ( it = liste->next; it != NULL &&  it != liste; it = next ){
    	int type = it->type;
        next = it->next;
        free(it);
        printf("suppression LUT de type %d\n", type);
        fflush(stdin);
    }

}






