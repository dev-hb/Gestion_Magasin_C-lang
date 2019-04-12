/// GESTION DES PRODUITS

//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////


#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Product{
	int code;
	double price;
	char *designation;
} Product;

typedef struct ProductElement {
	Product *produit;
	struct ProductElement  *next;
} ProductElement;


//// LES FONCTIONS DE MANIPULATION


ProductElement *createProductElement(Product *produit){
	ProductElement *pe=(ProductElement *)malloc(sizeof(ProductElement));
	pe->produit=produit;
	pe->next=NULL;
	return pe;
	
}

Product *createProduct(int code, char *designation, double price){
	Product *p=(Product*)malloc(sizeof(Product));
	p->designation = (char *) malloc(sizeof(char)*255);
	strcpy(p->designation, designation);
	p->code=code;
	p->price=price;
	return p;
}

void addProductToList(ProductElement **pe1, Product *p){
	ProductElement *ptr;
	ProductElement *pe2=(ProductElement*)malloc(sizeof(ProductElement));
	pe2->produit=p;
	pe2->next=NULL;
	if(*pe1 == NULL){
		*pe1=pe2;
		return ;
	}else{
		for(ptr=(*pe1);ptr->next != NULL;ptr=ptr->next);
		ptr->next=pe2;
	}
}

void afficherProduct(ProductElement *pe1){
	ProductElement *ptr;
	ptr=pe1;
	if(!ptr) printf("aucun produit enregistre!\n");
	while(ptr != NULL){
		printf("%d\t", ptr->produit->code);
		printf("%s\t", ptr->produit->designation);
		printf("%lf\n", ptr->produit->price);
		ptr=ptr->next;
	}
}

char *CreateText(){
	char text[40];
	char *exactString=(char *)malloc(sizeof(char));
	printf("donner designation: ");
	scanf("%s", text);
	strcpy(exactString, text);
	return exactString;
}

Product *GetProduct(ProductElement *pe, int code){
	ProductElement *ptr;
	if(pe != NULL){
		for(ptr=pe; ptr != NULL; ptr=ptr->next){
			if(ptr->produit->code==code){
				return ptr->produit;
			}
		}
		return NULL;
	}else{
		return NULL;
	}
	
}

void deleteProduct(ProductElement **pe,int code){
    ProductElement *pt=*pe;
    ProductElement *tmp;
    if(*pe==NULL){
    	return ;
    }	
    if((*pe)->produit->code==code){
        *pe=(*pe)->next;
        free(pt);
    }else{
	    while(pt->next !=NULL){
            tmp=pt;
            pt=pt->next;
            if(pt->produit->code==code){
                tmp->next=pt->next;
                free(pt);
                break;
            }
	    }
    }
}

void editProduct(ProductElement *pe, int code, char *ndes, double nprix){
	ProductElement *ptr;
	if(ptr != NULL){
		for(ptr=pe; ptr != NULL; ptr=ptr->next){
			if(ptr->produit->code==code){
				ptr->produit->designation=ndes;
				ptr->produit->price=nprix;
				printf("produit a ete modifie\n ");
				return ;
			}
		}
	}else{
		printf("liste vide");
	}
}
