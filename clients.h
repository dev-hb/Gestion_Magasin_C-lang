//// GESTION DES CLIENTS

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

typedef struct Client{
	int code;
	char *nom;
	char *prenom;
	char *tel;
} Client;

typedef struct ClientElement {
	Client *client;
	struct ClientElement  *next;
} ClientElement;


//// LES FONCTIONS DE MANIPULATION


ClientElement *createClientElement(Client *client){
	ClientElement *ce=(ClientElement *)malloc(sizeof(ClientElement));
	ce->client=client;
	ce->next=NULL;
	return ce;
}

Client *createClient(int code, char *nom, char *prenom, char *tel){
	Client *c=(Client*)malloc(sizeof(Client));
	c->code=code;
	c->nom = (char *) malloc(sizeof(char)*sizeof(nom));
	c->prenom = (char *) malloc(sizeof(char)*sizeof(prenom));
	c->tel = (char *) malloc(sizeof(char)*sizeof(tel));
	strcpy(c->nom, nom);
	strcpy(c->prenom, prenom);
	strcpy(c->tel, tel);
	return c;
}

void addClientToList(ClientElement **ce1, Client *c){
	ClientElement *ptr;
	ClientElement *ce2=(ClientElement*)malloc(sizeof(ClientElement));
	ce2->client=c;
	ce2->next=NULL;
	if(*ce1 == NULL){
		*ce1=ce2;
		return ;
	}else{
		
		for(ptr=(*ce1);ptr->next != NULL;ptr=ptr->next);
		ptr->next=ce2;
	}
}

void afficherClient(ClientElement *ce1){
	ClientElement *ptr;
	ptr=ce1;
	if(!ptr) printf("aucun client enregistre!\n");
	while(ptr != NULL){
		printf("%d\t", ptr->client->code);
		printf("%s\t", ptr->client->nom);
		printf("%s\t", ptr->client->prenom);
		printf("%s\n", ptr->client->tel);
		ptr=ptr->next;
	}
}

char *CreateText(char * msg){
	char text[40];
	char *exactString=(char *)malloc(sizeof(char));
	if(!strcmp("nom", msg)){
		printf("donner nom : ");	
	}else if(!strcmp("prenom", msg)){
		printf("donner prenom : ");
	}else if(!strcmp("tel", msg)){
		printf("donner telephone : ");
	}else printf("donner le texte : ");
	scanf("%s", text);
	strcpy(exactString, text);
	return exactString;
}

Client *GetClient(ClientElement *ce, int code){
	ClientElement *ptr;
	if(ce != NULL){
		for(ptr=ce; ptr != NULL; ptr=ptr->next){
			if(ptr->client->code==code){
				return ptr->client;
			}
		}
		return NULL;
	} return NULL;
}

void deleteClient(ClientElement **ce,int code){
    ClientElement *pt=*ce;
    ClientElement *tmp;
    if(*ce!=NULL){
    	if((*ce)->client->code==code){
	        *ce=(*ce)->next;
	        free(pt);
	    }else{
		    while(pt->next !=NULL){
	            tmp=pt;
	            pt=pt->next;
	            if(pt->client->code==code){
	                tmp->next=pt->next;
	                free(pt);
	                break;
	            }
		    }
	    }	
    }
}

void editClient(ClientElement *ce, int code, char *nom, char *prenom, char *tel){
	ClientElement *ptr;
	if(ptr != NULL){
		for(ptr=ce; ptr != NULL; ptr=ptr->next){
			if(ptr->client->code==code){
				ptr->client->nom=nom;
				ptr->client->prenom=prenom;
				ptr->client->tel=tel;
				printf("client a ete modifie\n ");
				return ;
			}
		}
	}else{
		printf("liste vide");
	}
}
