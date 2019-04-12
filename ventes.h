/// GESTION DES VENTES


//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////


typedef struct date{
	int jour;
	int mois;
	int annee;
} Date;

typedef struct item{
	int quantity;
	double prix;
	Product * product;
} Item;

typedef struct itemElement{
	Item * item;
	struct itemElement * next;
} ItemElement;

typedef struct vente{
	int saleCode;
	double total;
	Date * date;
	ItemElement *itemList;
	Client * client;
} Vente;

typedef struct venteElement{
	Vente * vente;
	struct venteElement * next;
} VenteElement;

//// LES FONCTIONS DE MANIPULATION

Item * createItem(ProductElement ** pe, int idPro, int price, int qtt){
	Item * i = (Item *) malloc(sizeof(Item));
	i->quantity = qtt;
	i->prix = price;
	i->product = GetProduct(*pe, idPro);
	
	return i;
}

void addItemToList(ItemElement ** ie, Item * i){
	ItemElement *ptr;
	ItemElement *ie2=(ItemElement*)malloc(sizeof(ItemElement));
	ie2->item=i;
	ie2->next=NULL;
	if(*ie == NULL){
		*ie=ie2;
		return ;
	}else{
		for(ptr=(*ie);ptr->next != NULL;ptr=ptr->next);
		ptr->next=ie2;
	}
}

void afficherItem(ItemElement * ie){
	ItemElement * ptr = ie;
	int i=0;
	while(ptr != NULL){
		printf("%d - %s\t",i, ptr->item->product->designation);
		printf("%g\t", ptr->item->prix);
		printf("%d\n", ptr->item->quantity);
		ptr=ptr->next;i++;
	}
}

void deleteItem(ItemElement ** ie, int index){
	if(*ie == NULL) return;
	int i=0;
	ItemElement * pt, * tmp = *ie;
	if(index==0){
		pt = *ie;
		*ie = pt->next;
		free(pt);
		return;
	}
	if(tmp->next==NULL){free(*ie);return;}
	while(i<index-1){tmp=tmp->next;i++;}
	pt = tmp->next;
	tmp->next=tmp->next->next;
	if(pt!=NULL) free(pt);
}

void deleteAllItems(ItemElement ** ie){
	ItemElement * tmp = *ie;
	while(tmp){
		deleteItem(ie, 0);
		tmp=*ie;
	}
}

double editItem(ItemElement ** ie, int index, double prix, int qtt){
	if(*ie == NULL){ printf("Aucun element a modifier!\n"); return 0; }
	int i=0;
	double tmp_tot;
	ItemElement * tmp = *ie;
	while(tmp->next && i<index){tmp=tmp->next;i++;}
	tmp_tot = tmp->item->quantity * tmp->item->prix;
	tmp->item->quantity = qtt;
	tmp->item->prix = prix;
	
	return (prix*qtt - tmp_tot);
}

Vente * createVente(ClientElement ** ce, ProductElement ** pe, int code, int idCli, int d, int m, int y){
	Vente * v = (Vente *) malloc(sizeof(Vente));
	v->saleCode = code;
	v->total = 0;
	v->client = GetClient(*ce, idCli);
	v->date = (Date *) malloc(sizeof(Date));
	v->date->jour = d;
	v->date->mois = m;
	v->date->annee = y;
	
	return v;
}

void addVenteToList(VenteElement ** ve, Vente * v){
	VenteElement *ptr;
	VenteElement *ve2=(VenteElement*)malloc(sizeof(VenteElement));
	ve2->vente=v;
	ve2->next=NULL;
	if(*ve == NULL){
		*ve=ve2;
		return ;
	}else{
		for(ptr=(*ve);ptr->next != NULL;ptr=ptr->next);
		ptr->next=ve2;
	}
}

char * dateToString(Date * dt){
	char * d = (char *) malloc(sizeof(char)*10);
	sprintf(d, "%d/%d/%d", dt->jour, dt->mois, dt->annee);
	return d;
}

void afficherVente(VenteElement * ve){
	if(! ve) printf("aucun vente enregistre!\n");
	else{
		VenteElement *ptr = ve;
		while(ptr != NULL){
			printf("ID : %d\n", ptr->vente->saleCode);
			printf("Nom & prenom : %s %s\n", ptr->vente->client->prenom, ptr->vente->client->nom);
			printf("Date : %s\n", dateToString(ptr->vente->date));
			printf("Liste des produits vendu :\n");
			afficherItem(ptr->vente->itemList);
			printf("Total TTC de vente : %g\n\n", ptr->vente->total);
			ptr=ptr->next;	
		}
	}
}

Vente * GetVente(VenteElement * ve, int id){
	if(!ve) return NULL;
	while(ve){
		if(ve->vente->saleCode == id) return ve->vente;
		ve = ve->next;
	}
	return ve!=NULL?ve->vente:NULL;
}

void deleteVente(VenteElement ** ve, int id){
	if(*ve == NULL) return;
	VenteElement * pt, * tmp = *ve;
	if(tmp->vente->saleCode == id){
		pt = *ve;
		*ve = pt->next;
		free(pt);
		return;
	}
	if(tmp->next==NULL){free(*ve);return;}
	while(tmp){
		if(tmp->next->vente->saleCode == id) break;
		tmp=tmp->next;	
	}
	pt = tmp->next;
	tmp->next=tmp->next->next;
	if(pt!=NULL) free(pt);
}
