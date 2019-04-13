//// Menus de navigation

//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////


void tradeMark(){
	char indent[] = "                    ";
	system("cls");
	printf("\n\n\n");
	printf("%s//////////////////////////////////////////////\n", indent);
	printf("%s////// APPLICATION REALISEE PAR ShadMaN //////\n", indent);
	printf("%s///////////////// Zakaria HBA ////////////////\n", indent);
	printf("%s////////////// GESTION MAGASIN ///////////////\n", indent);
	printf("%s///// All Rights Reserverd To DevHB Corp /////\n", indent);
	printf("%s//////////////////////////////////////////////\n", indent);
	printf("\n\n\n");
}


int menuPrincipale(){
	system("cls");
	int choix;
	printf("APPLICATION DE GESTION DE MAGASIN\n");
	printf("_________________________________\n");
	printf("1 - Gestion Produits\n");
	printf("2 - Gestion Clients\n");
	printf("3 - Gestion Ventes\n");
	printf("4 - Extra\n");
	printf("0 - Quitter\n");
	printf("_________________________________\n");
	printf("Entrer votre choix : ");
	scanf("%d", &choix);
	return choix;
}

int menuProducts(){
	system("cls");
	int choix;
	printf("MENU DES PRODUITS\n");
	printf("_________________________________\n");
	printf("1 - Ajouter un produit\n");
	printf("2 - Modifier un produit\n");
	printf("3 - Afficher la liste des produits\n");
	printf("4 - Chercher un produit\n");
	printf("5 - Supprimer un produit\n");
	printf("0 - Retour\n");
	printf("_________________________________\n");
	printf("Entrer votre choix : ");
	scanf("%d", &choix);
	return choix;
}

int menuClients(){
	system("cls");
	int choix;
	printf("MENU DES CLIENTS\n");
	printf("_________________________________\n");
	printf("1 - Ajouter un client\n");
	printf("2 - Modifier un client\n");
	printf("3 - Afficher la liste des clients\n");
	printf("4 - Chercher un client\n");
	printf("5 - Supprimer un client\n");
	printf("0 - Retour\n");
	printf("_________________________________\n");
	printf("ENTRER votre choix : ");
	scanf("%d", &choix);
	return choix;
}

int menuVentes(Vente * v, Vente * vpy){
	system("cls");
	int choix;
	printf("MENU DES VENTES");
	if(v!=NULL) printf(" (Modification de vente ID : %d)", v->saleCode);
	printf("\n");
	printf("_________________________________\n");
	printf("1 - Ajouter une vente\n");
	if(v!=NULL){
		printf("    11 - Ajouter un element\n");
		printf("    12 - Modifier un element\n");
		printf("    13 - Afficher les elements\n");
		printf("    14 - Supprimer un element\n");
		printf("    15 - Supprimer tout les elements\n");
		printf("    16 - Terminer le processus de modification\n");
	}
	printf("2 - Modifier une vente\n");
	printf("3 - Afficher la liste des ventes\n");
	printf("4 - Chercher une vente\n");
	printf("5 - Supprimer une vente\n");
	printf("6 - Paiemenet d\'une vente\n");
	if(vpy!=NULL){
		printf("    61 - Ajouter une paiement\n");
		printf("    62 - Afficher les paiement\n");
		printf("    63 - Supprimer une paiement\n");
		printf("    64 - Terminer le processus de paiement\n");
	}
	printf("0 - Retour\n");
	printf("_________________________________\n");
	printf("ENTRER votre choix : ");
	scanf("%d", &choix);
	return choix;
}

int menuExtra(){
	system("cls");
	int choix;
	printf("EXTRA MENU\n");
	printf("_________________________________\n");
	printf("1 - Enregistrer dans la base\n");
	printf("2 - Charger les donnees\n");
	printf("3 - Vider les donnees\n");
	printf("4 - chargement/enregistrement automatique des donnees (");
	if(getAutoLoadState()) printf("True");
	else printf("False");
	printf(")\n0 - Retour\n");
	printf("_________________________________\n");
	printf("ENTRER votre choix : ");
	scanf("%d", &choix);
	return choix;
}
