#include <stdio.h>
#include <stdlib.h>
#include "products.h"
#include "clients.h"
#include "ventes.h"
#include "payement.h"
#include "extras.h"
#include "menus.h"

//////////////////////////////////////////////
////// APPLICATION REALISEE PAR ShadMaN //////
//////////////// Zakaria HBA /////////////////
////////////// GESTION MAGASIN ///////////////
///// All Rights Reserverd To DevHB Corp /////
//////////////////////////////////////////////


int main(){
	// helpers
		int cp, cpr, cc, ret=0;
		char *des, *nom, *prenom, *tel;
		int code, idcl, d,m,y;
		double prix;
		int idpr, qtt;
		double prc;
	
	//////////////////////////
	ProductElement *pe=NULL;// Liste des produits
	ClientElement *ce=NULL;/// Liste des clients
	ItemElement * ie=NULL;//// Liste des items de vente
	VenteElement * ve=NULL;/// Liste des ventes
	PayementElement * ye=NULL; //Liste des Paiement de vente
	//////////////////////////
	
	// individual items
		Product *p;
		Client *c;
		Vente *vtmp, *v = NULL, *vpy=NULL; // vpy for payement ;; v for item sale
		Payement *py;
	
	tradeMark(); // affichage de la page de demarrage
	
	/// Autoload data from text files
	if(getAutoLoadState()){
		chargerProducts(&pe);
		chargerClients(&ce);
		chargerVente(&ve, &ce, &pe);
		printf("Bonjour !\nLes donnees sont automatiquement charge, tapez pour continuer...");
		getch();
	}
	
	// Main loop
	while((cp = menuPrincipale())){ // menu principal de l'application
		ret = 0;
		switch(cp){
			case 1:
				// menu des produits
				while((cpr = menuProducts()) && !ret){
					switch(cpr){
						case 0: ret=1;break;
						case 1: // ajouter un nouveau produit
							des=CreateText();
							printf("Donner le code et le prix : ");
							scanf("%d %lf", &code, &prix);
							p=createProduct(code, des, prix);
							addProductToList(&pe, p);
							break;
						case 2: // modifier un produit
							printf("Donner le code de produit a modifier : ");
							scanf("%d", &code);
							printf("donner le nouveau prix : ");
							scanf("%lf", &prix);
							editProduct(pe, code, CreateText(), prix);
							break;
						case 3: afficherProduct(pe) ; getch() ; break;
						case 4: // chercher un produit
							printf("Donner le code de produit a chercher : ");
							scanf("%d", &code);
							p=GetProduct(pe, code);
							if(p==NULL){
								printf("produit inexistant\n");
							}else{
								printf("voila le produit recherche:\n");
								printf("--> code : %d   designation: %s   prix: %lf\n\n ", p->code, p->designation, p->price);
							} getch();
							break;
						case 5: // supprimer un produit
							printf("Donner le code de produit a supprime : ");
							scanf("%d", &code);
							deleteProduct(&pe,code);
							break;
					} 
				}
			break;
			case 2:
				// menu des clients
				while((cc = menuClients()) && !ret){
					switch(cc){
						case 0: ret=1;break;
						case 1: // ajouter un client
							printf("Donner le code : ");
							scanf("%d", &code);
							nom=CreateText("nom");
							prenom=CreateText("prenom");
							tel=CreateText("tel");
							c=createClient(code, nom, prenom, tel);
							addClientToList(&ce, c);
							break;
						case 2: // modifier un client
							printf("Donner le code de client a modifier : ");
							scanf("%d", &code);
							editClient(ce, code, CreateText("nom"), CreateText("prenom"), CreateText("tel"));
							break;
						case 3: afficherClient(ce) ; getch() ; break;
						case 4: // chercher un client
							printf("Donner le code de client a chercher : ");
							scanf("%d", &code);
							c=GetClient(ce, code);
							if(c==NULL){
								printf("client inexistant\n");
							}else{
								printf("voila le client recherche:\n");
								printf("--> code : %d   nom: %s   prenom: %s   telephone: %s\n ", c->code, c->nom, c->prenom, c->tel);
							} getch();
							break;
						case 5: // supprimer un client
							printf("Donner le code de client a supprime : ");
							scanf("%d", &code);
							deleteClient(&ce,code);
							break;
					} 
				}
			break;
			case 3:
				// menu ventes
				while((cc = menuVentes(v, vpy)) && !ret){
					switch(cc){
						case 0: ret=1;break;
						case 1: // ajouter une nouvelle vente
							if(!v){
								printf("Donner le code de vente : ");
								scanf("%d", &code);
								printf("Donner l\'ID du client : ");
								scanf("%d", &idcl);
								printf("Donner la date de vente (jj mm yyyy) : ");
								scanf("%d %d %d", &d, &m, &y);
								v=createVente(&ce, &pe, code, idcl, d, m, y);
								v->itemList = ie;
								v->payementList = ye;
								if(v) printf("la vente a ete ajoute!");
								addVenteToList(&ve, v);
							}else printf("une vente est deja en cours!");
							getch();
						break;
						case 11: // ajouter un element de vente
							printf("Donner l\'ID produit, prix de vente et quantite d\'element : ");
							scanf("%d %lf %d", &idpr, &prc, &qtt);
							addItemToList(&ie, createItem(&pe, idpr, prc, qtt));
							v->total += prc*qtt;
							printf("un element a ete ajoute!");
							getch();	
						break;
						case 12: // modifier un element de vente
							printf("Liste des produit de la vente :\n");
							afficherItem(ie);
							printf("Donner l\'index d\'element a modifier : ");
							scanf("%d", &code);
							printf("Donner un nouveau prix et quantite : ");
							scanf("%lf %d", &prc, &qtt);
							prc = editItem(&ie, code, prc, qtt); // retourner la marge de prix a modifier
							v->total+=prc; // modifier le prix total de la vente
							printf("l\'element a ete midifie avec succes!");
							getch();
						break;
						case 13: // aficher les elements de la vente
							printf("Liste des produit de la vente :\n");
							if(ie) afficherItem(ie);
							else printf("aucun element dans la liste!");
							getch();
						break;
						case 14: // supprimer un element de la vente
							printf("Liste des produit de la vente :\n");
							afficherItem(ie);
							printf("Donner l\'index d\'element a supprimer : ");
							scanf("%d", &code);
							deleteItem(&ie, code);
							printf("l\'element a ete supprime avec succes!");
							getch();
						break;
						case 15: // supprimer tout les elements de la vente
							if(confirm("Voulez-vous vraimenet supprimer tout les elements")){
								deleteAllItems(&ie);
								printf("tout elements ont ete supprime!\n");
								getch();
							}
						break;
						case 16: // terminer le processus de vente
							if(confirm("Etes-vous sur de terminer le processus")){
								v->itemList = ie; // modification de liste des elements de vente
								v=NULL;
								printf("Processus termine!\n");
								getch();
							}
						break;
						case 2: // modifier une vente
							if(!v){
								printf("Enter le code d\'une vente a modifier : ");
								scanf("%d", &code);
								v = GetVente(ve, code);
								ie = v->itemList; // pour modifier les elements de la vente
							}else{
								printf("une vente est en cours de modification!");
								getch();
							}
						break;// affichage de tout les ventes
						case 3:afficherVente(ve);getch();break;
						case 4:// chercher une vente
							printf("Donner le code de vente a chercher : ");
							scanf("%d", &code);
							vtmp=GetVente(ve, code);
							if(vtmp==NULL){
								printf("vente inexistante\n");
							}else{
								printf("Voila la vente recherche : \n____________________________\n");
								printf("ID : %d\n", vtmp->saleCode);
								printf("Nom & prenom : %s %s\n", vtmp->client->prenom, vtmp->client->nom);
								printf("Date : %s\n", dateToString(vtmp->date));
								printf("Liste des produits vendu :\n");
								afficherItem(vtmp->itemList);
								printf("Total TTC de vente : %g\n", vtmp->total);
							} getch();
							break;
						break;
						case 5:// supprission d'un vente dans la liste
							printf("Donner l\'ID de la vente a supprimer : ");
							scanf("%d", &code);
							if(confirm("Voulez-vous vraimenet supprimer cette vente")){
								deleteVente(&ve, code);
								printf("la vente a ete suprrime!\n");
								getch();
							}
						break;
						case 6: // reglement d'une vente (process paiement)
							printf("Donner le code de vente concernant le payement : ");
							scanf("%d", &code);
							vpy = GetVente(ve, code);
							vpy->payementList = ye;
						break;
						case 61: // ajouter une paiement
							printf("Donner le type de paiement : ");
							scanf("%s", &des);
							printf("Donner la date de paiement (jj mm yyyy) : ");
							scanf("%d %d %d", &d, &m, &y);
							py = createPayement(des, d, m, y);
							printf("done\n");
							addPayementToList(&ye, py);
						break;
						case 62: // afficher les paiements
							printf("Type\tDate\n");
							afficherPayement(ye);
							getch();
						break;
						case 63: // supprimer une paiement
							
						break;
						case 64: // terminer le process de paiement
							if(confirm("Etes-vous sur de terminer le processus")){
								vpy->payementList = ye;
								vpy=NULL;
								printf("Processus termine!\n");
								getch();
							}
						break;
					}
				}
			break;
			case 4:
				// extra menu :
				while((cc = menuExtra()) && !ret){
					switch(cc){
						case 0: ret=1;break;
						case 1: // enregistrer dans la base
							enregistrerProducts(&pe);
							enregistrerClients(&ce);
							printf("toutes est enregistre!\n");
							getch();
						break;
						case 2: // recuperer les donnes de la base
							chargerProducts(&pe);
							chargerClients(&ce);
							printf("les donnees sont charge avec succes!\n");
							getch();
						break;
						case 3: // vider les fichiers textes et tous les données exitantes
							pe = NULL;
							ce = NULL;
							enregistrerProducts(&pe);
							enregistrerClients(&ce);
							printf("la base de donnees est vide!\n");
							getch();
						break;
						case 4: // charger et enregistrer automatiquement les données
							int state = getAutoLoadState();
							state = !state;
							setAutoLoadState(state);
						break;
					}
				}
			break;
		}
	}
	system("cls");
	printf("Au revoir.\n");
	
	// Enregistrement automatique des données dans les fichiers textes
	if(getAutoLoadState()){
		enregistrerProducts(&pe);
		enregistrerClients(&ce);
		enregistrerVente(&ve);
		enregistrerVenteItem(&ve);
		printf("Les donnees sont automatiquement enregistre, tapez pour terminer...");
		getch();
	}

	return 0;	
}
