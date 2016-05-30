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
			deleteLUT(&tmp);
			return;
		}
		tmp=tmp->next;
		if(tmp == l)
			break;
	}
}

void addLUT(LUT* list, LUT* l, LutOption type){
//	int i;
	if (!list || !l)
		return;
	if(LUTIsEmpty(list)){
		list->next = list;
		list->prev = list;
	}
	l->prev = list;
	l->next = list->next;
	list->next->prev = l;
	list->next = l;
//	if (LUTIsEmpty(list)){
//		list->next = list;
//		list->prev = list;
//		for (i = 0; i < 256; i++)
//			list->lut[i] = lut[i];
//		list->type = type;
//		return;
//	}
//	if (list->next == list)	{
//		LUT* newNode = makeLUT();
//		newNode->type = type;
//		newNode->prev = list;
//		newNode->next = list;
//		list->next = newNode;
//		list->prev = newNode;
//		for (i = 0; i < 256; i++)
//			newNode->lut[i] = lut[i];
//		return;
//	}
//	LUT* newNode = makeLUT();
//	list->next = l;
//	l->type = type;
//	l->prev = list->prev;
//	list->prev->next = l;
//	list->prev = l;
//	for (i = 0; i < 256; i++)
//		l->lut[i] = l->lut[i];
}

void deleteLUT(LUT** list){
	if (*list == NULL)
		return;
	if (LUTIsEmpty(*list) == true)
		return;
	if ((*list)->next == *list){
		*list = makeLUT();
		return;
	}
	else{
		(*list)->prev->next = (*list)->next;
		(*list)->next->prev = (*list)->prev;
	}
	free(*list);
	*list = NULL;
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
 		int value = L->lut[i];
 		if(i < 127)
 			value -= c/2;
 		if(i >= 127)
 			value += c/2;
 		checkValue(&value);
 		L->lut[i] = value;
 	}
 	L->type = addcon;
}

void DIMCON(LUT* L, int c){ 
	int i;
	float coef = c/100.;
	for(i = 0; i < 256; i++)  {
   		L->lut[i] = 128 - (128 - i) * coef;
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

LUT* copyLUT_r(LUT* l){
	if(!l)
		return NULL;
	LUT* tmp = l->next;
	LUT* ret = copyLUT(l);
	if(!LUTIsEmpty(l)){
		while(tmp != NULL && tmp != l){
			ret->next = copyLUT(tmp);
			tmp = tmp->next;
		}
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
	LutOption type = (*liste)->type;
	if(liste != NULL && *liste != NULL ){
		if(!LUTIsEmpty(*liste))
			viderLUT(*liste);
    	free(*liste);
    	*liste = NULL;
    }
	printf("FreeLUT type %d OK\n", type);
}

void viderLUT (LUT* liste){
	if(!liste)
		return;
    LUT *it, *next;
    for ( it = liste->next; it != liste; it = next ){
    	if(it == NULL)
    		break;
    	int type = it->type;
        next = it->next;
        free(it);
        it = NULL;
        printf("suppression LUT de type %d\n", type);
    }

}






