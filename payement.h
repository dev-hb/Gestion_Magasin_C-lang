///// GESTION DE PAIEMENT


//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////


typedef struct payement{
	char * type;
	Date * date;
} Payement;

typedef struct payementElement{
	Payement * payement;
	struct payementElement * next;
} PayementElement;



//// LES FONCTIONS DE MANIPULATION


PayementElement *createPayementElement(Payement *payement){
	PayementElement *ye=(PayementElement *)malloc(sizeof(PayementElement));
	ye->payement=payement;
	ye->next=NULL;
	return ye;
}

Payement *createPayement(char *type, int d, int m, int y){
	Payement *p=(Payement*)malloc(sizeof(Payement));
	p->type = (char *) malloc(sizeof(char)*255);
	strcpy(p->type, type);
	p->date = (Date *) malloc(sizeof(Date));
	p->date->jour = d;
	p->date->mois = m;
	p->date->annee = y;
	
	return p;
}

void addPayementToList(PayementElement **ye1, Payement *p){
	PayementElement *ptr;
	PayementElement *ye2=(PayementElement*)malloc(sizeof(PayementElement));
	ye2->payement=p;
	ye2->next=NULL;
	if(*ye1 == NULL){
		*ye1=ye2;
		return ;
	}else{
		for(ptr=(*ye1);ptr->next != NULL;ptr=ptr->next);
		ptr->next=ye2;
	}
}

void afficherPayement(PayementElement *ye1){
	PayementElement *ptr;
	ptr=ye1;
	if(!ptr) printf("aucun payement enregistre!\n");
	while(ptr != NULL){
		printf("%s\t", ptr->payement->type);
		printf("%s\n", dateToString(ptr->payement->date));
		ptr=ptr->next;
	}
}
