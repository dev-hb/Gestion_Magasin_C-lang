//// EXTRA : gestion des fichiers


//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////

#define MAX_PEYMENTS 1024

int confirm(char * message){
	printf("%s?\n1 - Oui\n0 - Non\nEntrer Votre choix : ", message);
	int ch;
	scanf("%d", &ch);
	return ch;
}

void enregistrerProducts(ProductElement ** pe){
	FILE * fp = fopen("data/products.txt", "w");
	ProductElement * tmp = *pe;
	while(tmp){
		fprintf(fp, "%d|%lf|%s\n", tmp->produit->code, tmp->produit->price, tmp->produit->designation);
		tmp = tmp->next;
	}
	fclose(fp);
}

void chargerProducts(ProductElement ** pe){
	if(*pe != NULL){
		if(! confirm("La liste des produits n\'est pas vide, voulez-vous l\'ecraser")) return;
		else *pe = NULL;
	}
	FILE * fp = fopen("data/products.txt", "r");
	int code;
	double prix;
	char * designation;
	designation = (char *) malloc(sizeof(char)*255);
	while(! feof(fp)){
		fscanf(fp, "%d|%lf|%s\n", &code, &prix, designation);
		addProductToList(pe, createProduct(code, designation, prix));
	}
	free(designation);
	fclose(fp);
}


void enregistrerClients(ClientElement ** ce){
	FILE * fc = fopen("data/clients.txt", "w");
	ClientElement * tmp = *ce;
	while(tmp){
		fprintf(fc, "%d|%s |%s |%s\n", tmp->client->code, tmp->client->nom,tmp->client->prenom,tmp->client->tel);
		tmp = tmp->next;
	}
	fclose(fc);
}

void chargerClients(ClientElement ** ce){
	if(*ce != NULL){
		if(! confirm("La liste des clients n\'est pas vide, voulez-vous l\'ecraser")) return;
		else *ce = NULL;
	}
	
	FILE * fc = fopen("data/clients.txt", "r");
	int code;
	char * nom, *prenom, *tel;
	nom = (char *) malloc(sizeof(char)*40);
	prenom = (char *) malloc(sizeof(char)*40);
	tel = (char *) malloc(sizeof(char)*40);
	while(! feof(fc)){
		fscanf(fc, "%d|%s |%s |%s\n", &code, nom, prenom, tel);
		addClientToList(ce, createClient(code, nom, prenom, tel));
	}
	free(nom);
	free(prenom);
	free(tel);
	fclose(fc);
}

void enregistrerVente(VenteElement ** ve){
	FILE * fv = fopen("data/ventes.txt", "w");
	VenteElement * tmp = *ve;
	while(tmp){
		fprintf(fv, "%d|%d|%d|%d|%d|%lf\n", tmp->vente->saleCode, tmp->vente->client->code,
										tmp->vente->date->jour, tmp->vente->date->mois, tmp->vente->date->annee,
										tmp->vente->total);
		tmp = tmp->next;
	}
	fclose(fv);
}

ItemElement * chargerVenteItem(ProductElement ** pe, int idVente){
	ItemElement * ie = NULL;
	FILE * fv = fopen("data/detailventes.txt", "r");
	int code, qtt, idtmp;
	double prix;
	while(! feof(fv)){
		fscanf(fv, "%d|%d|%d|%lf\n", &idtmp, &code, &qtt, &prix);
		if(idtmp == idVente) addItemToList(&ie, createItem(pe, code, prix, qtt));
	}
	fclose(fv);
	
	return ie;
}

void chargerVente(VenteElement ** ve, ClientElement ** ce, ProductElement ** pe){
	if(*ve != NULL){
		if(! confirm("La liste des ventes n\'est pas vide, voulez-vous l\'ecraser")) return;
		else *ve = NULL;
	}
	FILE * fv = fopen("data/ventes.txt", "r");
	int code, idcli, d, m, y;
	double tot;
	Vente * v;
	while(! feof(fv)){
		fscanf(fv, "%d|%d|%d|%d|%d|%lf\n", &code, &idcli, &d, &m, &y, &tot);
		v = createVente(ce, pe, code, idcli, d, m, y);
		v->total = tot;
		v->itemList = chargerVenteItem(pe, code);
		addVenteToList(ve, v);
	}
	fclose(fv);
}

void enregistrerVenteItem(VenteElement ** ve){
	FILE * fvi = fopen("data/detailventes.txt", "w");
	VenteElement * tmp = *ve;
	ItemElement * tmp2 = tmp->vente->itemList;
	while(tmp){
		while(tmp2){
			fprintf(fvi, "%d|%d|%d|%lf\n", tmp->vente->saleCode,
					tmp2->item->product->code, tmp2->item->quantity, tmp2->item->prix);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	fclose(fvi);
}

void chargerPayement(PayementElement ** ye){
	if(*ye != NULL){
		if(! confirm("La liste des payements n\'est pas vide, voulez-vous l\'ecraser")) return;
		else *ye = NULL;
	}
	FILE * fv = fopen("data/payements.txt", "r");
	Payement * p;
	int id, idsale, d, m, y;
	double mt;
	char * type;
	type = (char *) malloc(sizeof(char)*20);
	while(! feof(fv)){
		fscanf(fv, "%d|%d|%d|%d|%d|%lf|%s \n", &id, &idsale, &d, &m, &y, &mt, type);
		p = createPayement(id, type, mt, d, m, y);
		addPayementToList(ye, p);
	}
	fclose(fv);
}

void enregistrerPayementElement(PayementElement ** ye){
	FILE * fpe = fopen("data/payements.txt", "w");
	PayementElement * tmp = *ye;
	while(tmp){
		fprintf(fpe, "%d|%d|%d|%d|%d|%lf|%s \n",  tmp->payement->id, tmp->payement->vente->saleCode,
								tmp->payement->date->jour, tmp->payement->date->mois, tmp->payement->date->annee,
								tmp->payement->montant, tmp->payement->type);
		tmp = tmp->next;
	}
	fclose(fpe);
}

double getSolde(int id){
	FILE * f = fopen("data/banque.txt", "r");
	int id_cli, id_cmpt;
	double solde;
	while(! feof(f)){
		fscanf(f, "%d|%d|%lf\n", &id_cmpt, &id_cli, &solde);
		if(id_cli == id){
			fclose(f);
			return solde;
		}
	}
	fclose(f);
	return -9999;
}

void setSolde(int id_c, double sld){
	FILE * f = fopen("data/banque.txt", "r");
	int id_cli[MAX_PEYMENTS], id_cmpt[MAX_PEYMENTS], i=0;
	double solde[MAX_PEYMENTS];
	while(! feof(f)){
		fscanf(f, "%d|%d|%lf\n", &id_cmpt[i], &id_cli[i], &solde[i]);
		i++;
	}
	fclose(f);
	id_cli[i] = -9999;
	
	i=0;
	while(id_cli[i] != -9999){
		if(id_c == id_cli[i]) break;
		i++;
	}
	
	solde[i] = sld;
	
	FILE * f1 = fopen("data/banque.txt", "w");
	i=0;
	while(id_cli[i] != -9999){
		fprintf(f1, "%d|%d|%lf\n", id_cmpt[i], id_cli[i], solde[i]);
		i++;
	}
	fclose(f1);
}

int getAutoLoadState(){
	FILE * f = fopen("data/param.txt", "r");
	int state;
	fscanf(f, "%d", &state);
	fclose(f);
	return state;
}

void setAutoLoadState(int state){
	FILE * f = fopen("data/param.txt", "w");
	fprintf(f, "%d", state);
	fclose(f);
}
