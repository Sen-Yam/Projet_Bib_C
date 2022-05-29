#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>  // bibliotheque pour manipuler le temps et les dates

typedef struct ListeOuvrage {  //declaration de la liste des ouvrages
	int cote ; // j'ai supposee que la cote est un entier 
	char titre[30];
	int nbr_exp_bib;
	int nbr_exp_emp;
	struct ListeOuvrage * suivant;
	struct ListeOuvrage * precedent;
	
}ListeOuvrage,*pOuvrage;

typedef struct ListeEtudiant {  //declaration de la liste des etudiants
	int matricule;
	char type;
	int penalite;
	struct ListeEtudiant * suivant;
	struct ListeEtudiant * precedent;
	
}ListeEtudiant,*pEtudiant;

typedef struct Date {   // declaration de l'enregistrement date 
	int jour;
	int mois;
	int year;
}Date;

typedef struct ListeEmprunt {   // declaration de la liste des emprunts
	int	matricule;
	int cote;
	Date date_retour;
	Date date_emprunt;
	struct ListeEmprunt * suivant;
	struct ListeEmprunt * precedent;
	
}ListeEmprunt,*pEmprunt;

typedef struct ListePenalite {     // declaration de la liste des penalites
	int matricule;
	int penalite;
	struct ListePenalite* suivant;
	struct ListePenalite* precedent;
}ListePenalite,*pPenalite;

typedef struct Etudiant {      // declaration d'un element etudiant juste pour 2 procedures , le reste des procedures j'ai utilisee la liste etudiant
	int matricule;
	char type;
	int penalite;
}Etudiant;

typedef struct listeF {			// declaration de la file des etudiants classiques et preniums
	Etudiant x;
	struct listeF*suivant;
}listeF,*plistF;

typedef struct file {
	plistF tete;
	plistF queue ;
}file;

// le debut des primitives de la file des etudiants
void Enfiler(file*F,Etudiant X) {
	plistF P;
	P=malloc(sizeof(listeF));
	P->x=X;
	if((*F).tete==NULL) {
		P->suivant=NULL;
		(*F).tete=P;
		(*F).queue=P;
	}
	else {
		((*F).queue)->suivant=P;
		((*F).queue)=((*F).queue)->suivant;
		P->suivant=NULL;
	}
}

void Defiler(file*F,Etudiant*X) {
	plistF P=(*F).tete;
	*X=((*F).tete)->x;
	if(((*F).tete)->suivant!=NULL) {
		(*F).tete=((*F).tete)->suivant;
			
	}
	else {
		(*F).tete=NULL;
		(*F).queue=NULL;
	}
	free(P);
}

Etudiant TeteFile(file F) {
	return (F.tete)->x;
}

bool FileVide(file F) {
	if(F.tete==NULL)  {
		return true;
	}
	else {
		return false;
	}
}

void InitFile(file*F) {
	(*F).tete=NULL;
	(*F).queue=NULL;
} 
 // la fin des primitives de la file

void AFFICHAGE_MENU() {		// procedure pour afficher le menu , l'utilisateur doit choisir un numero pour indiquer son choix
	printf("1-Ajouter des ouvrages \n");
	printf("2-Consulter la liste de tous les ouvrages \n");
	printf("3-Supprimer un ouvrage \n");
	printf("4-Vérifier la disponibilité des exemplaires \n");
	printf("5-Ajouter des étudiants \n");
	printf("6-Consulter un membre\n");
	printf("7-Supprimer un membre \n");
	printf("8-Modifier un membre \n");
	printf("9-Ajouter des emprunts \n");
	printf("10-Consulter un emprunt\n");
	printf("11-Supprimer un emprunt \n");
	printf("12-Modifier un emprunt \n");
	printf("13-Retourner un emprunt\n");
	printf("14-Ajouter une pénalité\n");
	printf("15-Supprimer une pénalité\n");
	printf("16-Consulter la liste des pénalités\n");
	printf("17-Définir la durée des emprunts\n");
	printf("18-Définir le maximum d’ouvrage à emprunter\n");
	printf("19-Consulter les ouvrages les plus sollicités\n");
	printf("20-Consulter l'ouvrage le moins emprunté\n");
	printf("21-EXIT");  // choix pour terminer le programme
}

void INSERTION_OUVRAGE(pOuvrage*T,pOuvrage*Q,ListeOuvrage ouvrage) { // pour inserer un ouvrage au debut de la liste juste pour accelerer le traitement
	pOuvrage P;
	int i ;
	char chaine[30];
	
	P=malloc(sizeof(ListeOuvrage));  // allocation de l'easpace de l'ouvrage a rajouter 
	P->cote=ouvrage.cote;
	strcpy(P->titre,ouvrage.titre);  // strcpy la procedure des chaines de caracteres qui recopie le contenu de ch2 dans ch1
	P->nbr_exp_bib=ouvrage.nbr_exp_bib;
	P->nbr_exp_emp=ouvrage.nbr_exp_emp;
	
	if(*T==NULL) {
		*T=P;
		*Q=P;
		(*T)->precedent=NULL;  // cas si la liste est vide 
		(*T)->suivant=NULL;
	}
	else {
		P->suivant=NULL; // cas si la liste n'est pas vide
		P->precedent=*Q;
		(*Q)->suivant=P;
		*Q=P;
	}
}

void AFFICHAGE_OUVRAGE(pOuvrage T) { // pour afficher la liste de tous les ouvrages
	int i=1;
	while(T!=NULL) {
		printf("\nlivre %d :\t",i);
		puts(T->titre); // puts est une procedure qui affiche une chaine de caracteres
		printf("\n");
		printf("cote : %d",T->cote) ;
		printf("\n");	
		printf("nombre d'exemplaires dans la bibliotheque : %d\n",T->nbr_exp_bib);
		printf("nombre d'exemplaires empruntes: %d\n",T->nbr_exp_emp);
		T=T->suivant; // parcourrir toute la liste
		i++;
		printf("\n");
}
}

bool EXISTE_OUVRAGE(pOuvrage T,pOuvrage Q, int cote) { // verifier l'existance d'un ouvrage qui est necessaire pour quelques procedures suivantes
	bool E=false;
	while(E==false && T!=NULL) {
		if(T->cote==cote || Q->cote==cote) { // la recherche en utilisant la cote 
			E=true;
		}
		T=T->suivant;
		Q=Q->precedent; // accelere la recherche en parcourrant la liste de la fin et le debut , elle est doublement chainnee
	}
	return E;
}

void SUPPRESSION_OUVRAGE(pOuvrage*T,pOuvrage*Q,int cote ) { // supprimer un ouvrage
	pOuvrage P,R;
	P=*T;
	while(P!=NULL && P->cote!=cote) { // recherche de l'adresse de l'ouvrage
		P=P->suivant;
	}
	if(P==*T) { // cas si l'adresse est egale a la tete de la liste suppression au debut
		R=*T;
		if((*T)->suivant==NULL){
			*T=NULL; // cas si la liste contient un seul element donc apres la suppression elle devient vide
			*Q=NULL;
		}
		else {
			*T=(*T)->suivant;
			(*T)->precedent=NULL;   // l'adresse est egale a la tete et la liste ne contient pas un seul element
		}
		free(R);
	}
	else {
		if(P==*Q) {
			R=*Q;
			*Q=(*Q)->precedent;
			(*Q)->suivant=NULL; // cas si l'adresse est egale a la queue suppression a la fin
			free(R);
		}
		else {
			R=P;
			(P->precedent)->suivant=P->suivant;
			(P->suivant)->precedent=P->precedent;  // dernier cas si l'ouvrage se trouve au milieu de la liste
			free(R);
		}
	}
	
	
}

bool DISPONIBLE_EXEMPLAIRE(pOuvrage T,pOuvrage Q,int cote) {   // fonction booleenne pour verifier la disponibilitee des exemplaires d'un ouvrage
	bool D;
	bool tr=false;
	D=true;
	
		while(T!=NULL && tr==false ) { // recherche de l'ouvrage et au memee temps faire la verification
			if(T->cote==cote) { // cas si la tete pointe sur l'ouvrage
				tr=true;
				if(T->nbr_exp_emp == T->nbr_exp_bib) {   // verifier si l'ouvrage est non disponible = tous les exemplaires sont empruntes . sinon il est disponible 
					D=false;
				}
			}
				else {
						T=T->suivant;
			}
	}
	
	

 return D;
}

void INSERTION_ETUDIANT(pEtudiant* T,pEtudiant* Q,ListeEtudiant etudiant) { // pour inserer un etudiant au debut de la liste etudiant
	pEtudiant P;
	P=malloc(sizeof(ListeEtudiant));   // allocation dynamique de la case de l'etudiant
	P->matricule=etudiant.matricule;
	P->type=etudiant.type;  // recopier les informmations de l'etudiant dans la case pointee par P 
	P->penalite=etudiant.penalite;
	if(*T==NULL) {  // cas si la iste est vide
		*T=P;
		*Q=P;
		(*T)->suivant=NULL;
		(*T)->precedent=NULL;
	}
	else {
		P->suivant=NULL;    //cas si la liste n'est pas vide
		P->precedent=*Q;
		(*Q)->suivant=P;
		*Q=P;
	}
}

void AFFICHAGE_ETUDIANT(pEtudiant T) {   // pour afficher la listes des etudiants
	int i=1;
	printf("\n");
	while(T!=NULL) {
		printf(" etudiant %d\n",i);
		printf("matricule : %d\n",T->matricule);
		printf("type : %c\n",T->type);
		printf("penalite : %d\n",T->penalite);
		T=T->suivant;
		i++;
	}
}

bool EXISTE_ETUDIANT(pEtudiant T,pEtudiant Q,int matricule) { // verifier l'existance d'un etudiant qui est necessaire pour les procedures suivantes
	bool E=false;
	while(E==false && T!=NULL) {
		if(T->matricule==matricule || Q->matricule==matricule) {  // rechercher l/etudiant en utilisant son matricule
			E=true;
		}
		T=T->suivant;  // parcourrir la liste des deux senses , elle est doublement chainnee juste pour accelerer la recherche
		Q=Q->precedent;
	}
	return E;
}

void MODIFICATION_ETUDIANT(pEtudiant T,pEtudiant Q,int matricule ,ListeEtudiant etudiant) {  // pour modifier un etudiant
	pEtudiant P;
	P=T;
	while(P->matricule !=matricule) {   // recherche de l'etudiant en utilisant son matricule 
		P=P->suivant;
	}
	P->matricule=etudiant.matricule;   // recopier les nouvelles valeurs pour modifier l'etudiant
	P->type=etudiant.type;
	P->penalite=etudiant.penalite;
	
}

void CONSULTATION_ETUDIANT(pEtudiant T,int matricule) {   // pour consulte un seul etudiant
	while(T!=NULL && T->matricule!=matricule)  {  //recherche de l'etudiant en utilisant son matricule
		T=T->suivant;
	}
	printf("\netudiant :\n");
	printf("matricule : %d\n",T->matricule);
	printf("type : %c\n",T->type);  // Affichage de l'etudiant
	printf("penalite : %d\n",T->penalite);
}

void SUPPRESSION_ETUDIANT(pEtudiant*T,pEtudiant*Q,int matricule) {   // pour supprimer un etudiatn
	pEtudiant P,R;
	P=*T;
	while(P->matricule!=matricule) {  // recherche de son adresse en utilisant son matricule
		P=P->suivant;
	}
	if(P==*T) {
		R=*T;
		if((*T)->suivant==NULL){
			*T=NULL;
			*Q=NULL;
		}
		else {
			*T=(*T)->suivant;
			(*T)->precedent=NULL;
		}
		free(R);     					// les memes cas de suppressiondans la procedure suppression_ouvrage
	}
	else {
		if(P==*Q) {
			R=*Q;
			((*Q)->precedent)->suivant=NULL;
			*Q=(*Q)->precedent;
			free(P);
		}
		else {
			R=P;
			(P->precedent)->suivant=P->suivant;
			(P->suivant)->precedent=P->precedent;
			free(R);
		}
	}
	
	
}

bool PENALITE_ETUDIANT(pEtudiant T,pEtudiant Q,int matricule) {   // verifier si l'etudiant donnee atteint le max des penalites (7) ou non
	bool P=false;
	bool tr=false;
	while(T!=NULL && tr==false) {
		if(T->matricule==matricule || Q->matricule==matricule)  {   // recherche en utilisant le matricule
			tr=true;
		}
		else {
			T=T->suivant;
			Q=Q->precedent;
		}
	}
	if(T->matricule==matricule) {
		if(T->penalite == 7) {  
			P=true;
		}
	}
	else {
		if(T->matricule==matricule) {
		if(T->penalite == 7) {
			P=true;
		}
	}
	}
	return P;   // si P=true donc l'etuiant atteitn 7 penalites , sinon non
}

void INSERTION_EMPRUNT( pEmprunt *T,pEmprunt*Q,ListeEmprunt emprunt ) {  // pour inserer un emprunt  au debut de la liste des emprunts
	pEmprunt P;
	P=malloc(sizeof(ListeEmprunt));    // allocation dynamique de la case de l'emprunt a rajouter
	P->matricule=emprunt.matricule;    // recopier les informations de l'emprunt dans la case a rajouter
	P->cote=emprunt.cote;
	P->date_emprunt=emprunt.date_emprunt;
	P->date_retour=emprunt.date_retour;
	if(*T==NULL) {
		*T=P;
		*Q=P;
		(*T)->suivant=NULL;   // si la liste est vide
		(*T)->precedent=NULL;
	}
	else {
		P->suivant=NULL;				// si la liste n'est pas vide
		P->precedent=*Q;
		(*Q)->suivant=P;
		*Q=P;
	}	
}

void CONSULTATION_EMPRUNT(pEmprunt T, pEmprunt Q,int matricule,int cote) {  // pour consulter un emprunt
	bool tr=false;
	pEmprunt S=NULL;
	while(T!=NULL && tr==false) {  // rechercher l'emprunt en utilisant la cote de l'ouvrage empruntee + le matricule de l'etudiant qui a empruntee cet ouvrage
		if(T->matricule==matricule && T->cote==cote) {
			tr=true;
			S=T;
		}
		else {
			if(Q->matricule==matricule && Q->cote==cote) {		// recherche en utilisant la tete et la queue pour accelerer le traitement
				tr=true;
				S=Q;	
			}
		}
		T=T->suivant;
		Q=Q->precedent;
	}
	if(tr==false) {
		printf("\ncet emprunt n'existe pas");  // cas si l'emprunt n'existe pas
	}
	else {
		printf("\n matricule : %d",S->matricule);  // cas si l'emprunt existe donc on l'affiche
		printf("\n cote : %d",S->cote);
		printf("\n date emprunt : %d / %d / %d ",S->date_emprunt.jour,S->date_emprunt.mois,S->date_emprunt.year);
		printf("\n date retour : %d / %d / %d ",S->date_retour.jour,S->date_retour.mois,S->date_retour.year);
	}
	
}

void AFFICHAGE_EMPRUNT(pEmprunt T) {   // procedure supplementaire pour afficher la listes des emprunts
	int i;
	if(T!=NULL) {
		printf("la liste des emprunts :\n");
		i=1;
		while(T!=NULL) {
			printf("emprunt %d :\n",i);
			printf("matricule : %d\n",T->matricule);
			printf("cote : %d\n",T->cote);
			printf("date emprunt : %d / %d / %d\n",T->date_emprunt.jour,T->date_emprunt.mois,T->date_emprunt.year);
			printf("date retour : %d / %d / %d\n",T->date_retour.jour,T->date_retour.mois,T->date_retour.year);
			T=T->suivant;
			i++;
		}
	}
	else {
		printf("\n la liste des emprunt est vide");
	}
}

bool EXISTE_EMPRUNT(pEmprunt T,pEmprunt Q,int cote,int matricule) { // verifier si un emprunt existe ou pas
	bool E=false;

	while(T!=NULL && E==false) {	// recherche avec la tete et la queue et en utiisant la cote et le matricule
		if((T->cote==cote && T->matricule==matricule)|| Q->cote==cote && Q->matricule==matricule) {
			E=true;
		}
		else {
			T=T->suivant;
			Q=Q->precedent;
		}
		
	}
	return E;
}

void SUPPRESSION_EMPRUNT(pEmprunt*T,pEmprunt*Q,int cote,int matricule) {  // pour supprimer un emprunt
	pEmprunt P,R;
		P=*T;
	while(P!=NULL && P->matricule!=matricule) { 	// la recherche en utilisant le matricule + la cote
		if(P->cote!=cote) {
			P=P->suivant;
		}
	}
	if(P==*T) {
		R=*T;
		if((*T)->suivant==NULL){
			*T=NULL;
			*Q=NULL;
		}
		else {
			*T=(*T)->suivant;
			(*T)->precedent=NULL;  // le meme traitement comme suppression_ouvrage
		}
		free(R);
	}
	else {
		if(P==*Q) {
			R=*Q;
			((*Q)->precedent)->suivant=NULL;
			*Q=(*Q)->precedent;
			free(P);
		}
		else {
			if(P==NULL) {
				printf("\n cet etudiant n'a pas emprunté un ouvrage\n");
			}
			else {
				
			
			R=P;
			(P->precedent)->suivant=P->suivant;
			(P->suivant)->precedent=P->precedent;
			free(R);
		}
		}
	}
	
	
}

void MODIFICATION_EMPRUNT(pEmprunt T,int cote,int matricule,ListeEmprunt emprunt,int i) { // pour modifier un emprunt
	pEmprunt P;
	bool tr=false;				//	le parametre d'entree i est juste pour indiquer si les dates sont modifiees(i=1) ou pas  (i=0)
	P=T;
	while(P!=NULL && tr==false) {
		if(P->cote==cote) {
			if(P->matricule==matricule) { // rechercher l'emprunt
				tr=true;
			}
		}
		else {
			P=P->suivant;
		}
	} 
	P->cote=emprunt.cote;
	P->matricule=emprunt.matricule;
	if(i==1) {  // cas si les dates sont modifiees 
	P->date_emprunt=emprunt.date_emprunt;
	P->date_retour=emprunt.date_retour;		
	}

}

void RETOURNER_EMPRUNT(int cote,int matricule,file*FC, file*FP,pOuvrage T,pEmprunt *A,pEmprunt* B) { // pour retourner un emprunt
	Etudiant X;
	ListeEmprunt emprunt;
	pOuvrage S;
	if(FileVide(*FP)==false) {
		Defiler(&(*FP),&X);  // verifier s'il y a un etudiant en attente dans la file prenieum
		emprunt.matricule=X.matricule;  // donc cet etudiant va prende le meme oouvrage c'est pour ca j'ai changee le matricule seulement
		emprunt.cote=cote;
		MODIFICATION_EMPRUNT(*A,cote,matricule,emprunt,0); // i=0 pour ne pas changer les dates , si l'utilisateur veut les changer il doit choisir l'instruction modifier un emprunt
	}
	else {  // sinon verifier s'il y a un etudiant en attente dans la file classique
		if(FileVide(*FC)==false) {
			Defiler(&(*FC),&X);
			emprunt.matricule=X.matricule;  // meme traitement comme la file prenium
			emprunt.cote=cote;
			MODIFICATION_EMPRUNT(*A,cote,matricule,emprunt,0);
		}
		else {
			S=T;
			while(S!=NULL && S->cote!=cote) {
				S=S->suivant;
			}
			S->nbr_exp_emp=S->nbr_exp_emp-1;	// si les deux files sont vides alors retourner l'ouvrage et decrementer le nbr de ses exemplaires empruntes
			SUPPRESSION_EMPRUNT(&(*A),&(*B),cote,matricule);  // en plus on doit supprimer l'emprunt car l'ouvrage est retournee
		}
	}
}

void AJOUTER_PENALITE(pPenalite*T,pPenalite *Q,int matricule) { // pour ajouter une penalites
	pPenalite P;    
	if(*T==NULL) {
		*T=malloc(sizeof(ListePenalite)); // si la liste est vide donc creer la 1ere case de l'etudiant penalisee
		(*T)->matricule=matricule;
		(*T)->penalite=1;
		(*T)->suivant=NULL;
		(*T)->precedent=NULL;
		*Q=*T;
	}
	else {  // si la liste n'est pas vide
		P=*T;
		while(P!=NULL && P->matricule!=matricule) { // rechercher si l'etudiant est deja penalisee (s'il existe dans la lste car elle contient seulement les etudiants penalisees)
		P=P->suivant;
			}
			if(P!=NULL) {
				P->penalite=P->penalite+1; 		// si l'etudiant est deja penalisee alors on lui rjoute une penalitee
			}   
			else {
				P=malloc(sizeof(ListePenalite));  // si l'etudiant est penalisee juste pour la 1ere fois donc je dois le rajouter comme un nouvel element dans la liste
				P->matricule=matricule;
				P->penalite=1; 
				P->suivant=*T;
				*T=P;
				(*T)->precedent=NULL;
			}
	
	}
	
}

void SUPPRESSION_PENALITE(pPenalite*T,pPenalite*Q,int matricule, pEtudiant TE) {  // pour supprimer une penalitee
		pPenalite P,R;
		P=*T;
	while(P!=NULL && P->matricule!=matricule) {  // rechercher l'etudiant penalisee en utilisant son matricule
		
			P=P->suivant;
		
	}
	if(P==NULL) {
				printf("\n cet etudiant n'est pas pénalisé\n");
			}
	else {
	
	if(P->penalite==1) {
								// si l'etudiant est penalisee une seul fois donc lors de la suppression de la penalitee il sera totalement supprimee de la liste car elle ne contient que les etudiants penalisees
	if(P==*T) {
		R=*T;
		if((*T)->suivant==NULL){
			*T=NULL;
			*Q=NULL;
		}
		else {
			*T=(*T)->suivant;
			(*T)->precedent=NULL;
		}
		free(R);
	}
	else {
		if(P==*Q) {
			R=*Q;
			((*Q)->precedent)->suivant=NULL;
			*Q=(*Q)->precedent;
			free(P);
		}
		else {
			R=P;
			(P->precedent)->suivant=P->suivant;
			(P->suivant)->precedent=P->precedent;
			free(R);
		
		}
	}
}
else {
	P->penalite=P->penalite-1;   // sinon on decremente le nbr des penalites sans supprimer l'etudiant de la liste
}
while(TE!=NULL && TE->matricule!=matricule) {
	TE=TE->suivant;
}
TE->penalite=TE->penalite-1;
}	
}

void AFFICHAGE_PENALITE(pPenalite T) { // pour afficher la listes de toutes les penalitees
	if(T==NULL) {
		printf("\n La liste des penalités est vide \n");
	}
	else {
		while(T!=NULL) {
			printf("\n matricule : %d\t",T->matricule);
			printf("\t Penalités : %d\n\n",T->penalite);
			T=T->suivant;
		}
	}
}

int DUREE_EMPRUNT() {    // l'utilisateur precise la duree 
	int N;
	do {
		printf("\n donnez le nombre en jours des emprunts sachant que la durée ne dois pas depasser 1 mois\t");
		scanf("%d",&N);
	}while(N<1 || N >30);
	printf("\n \n modification terminée\n \n ");
	return N;
}
 
void OUVRAGES_SOLICITES(pOuvrage T) {				
	printf("\n les ouvrages les plus solicités sont :\n");
	while(T!=NULL) {
		if(T->nbr_exp_emp >= T->nbr_exp_bib/2)  { // j'ai supposee qu'un ouvrage est solicitee si au moins sa moitiee est empruntee
			printf("titre : %s\n\n",T->titre);
			printf("cote : %d\n \n",T->cote);
			printf("nombre d'exemplaires empruntés : %d\n \n ",T->nbr_exp_emp); // Afficher les ouvrages les plus solicitees
			printf("nombre d'exemplaires dans la bibliotheque : %d\n \n \n  ",T->nbr_exp_bib);
		}
		T=T->suivant;
	}
}

void OUVRAGE_MOINS_EMPRUNTE(pOuvrage T) { // on cherche l'ouvrage dont le nbr des exemplaires empruntes est le plus petit
	int min;
	pOuvrage P;
	P=T->suivant;
	min=T->nbr_exp_emp;
	while(P!=NULL) {
		if(P->nbr_exp_emp < min) {
			T=P;
			min=P->nbr_exp_emp;
		}
		P=P->suivant;
	}
	
	printf("\n \n l'ouvrage le moins emprunté : \n\n");
	printf("titre : %s\n\n",T->titre);  // Afficher cet ouvrage
	printf("cote : %d\n \n",T->cote);
	printf("nombre d'exemplaires empruntés : %d\n \n ",T->nbr_exp_emp);
	printf("nombre d'exemplaires dans la bibliotheque : %d\n \n \n  ",T->nbr_exp_bib);
}


int main(int argc, char *argv[]) {
	pOuvrage TO,QO,P;
	
	file FC,FP;
	int i,position ,matricule,choix,cote;
	bool tr,exit;
	char X;
	char titre[30];
	int DT,I;
	ListeOuvrage ouvrage;
	Etudiant E;
	ListeEtudiant etudiant;
	ListeEmprunt emprunt;
	pEtudiant TE,QE,PE;
	pEmprunt A,B;
	pPenalite TP,QP;
	time_t  currentTime; // time_t est un enregistrement , c'est un type de temps
	time(&currentTime); // cette procedure comme parametre de type time_t et permet d'avoir la date actuelle + l'heure
	struct tm * time=localtime(&currentTime);
	// tm est un enregistrement qui contient plusieurs elements comme le jour , le mois , l'annee 
	// localetime est une fonction qui prend un parametre de type time_t pour pointer sur une variable de type tm 
	// time est une variable egale a la fonction lovaletime qui pointe donc sur tm pour pouvoir manipuler les elements (jour, mois , annee) de l'enregistrement tm
	// la difference entre time_t et tm :  time_t permet d'avoir la date actuelle seulement , mais tm permet d'avoir n'importe quelle date passee ou futur
	// il est necessaire d'utiliser time_t pour pouvoir manipuler tm 
	TE=NULL; // tete de liste etudiant
	QE=NULL; // queue de lisye etudiant
	TO=NULL; // tete de liste ouvrage
	QO=NULL; // queue de list ouvrage
	A=NULL; // tete de liste emprunt
	B=NULL;  // queue de liste emprunt
	TP=NULL;  // tete de liste penalite
	QP=NULL;  // queue de liste penalite
	InitFile(&FC);  // FC la file classique
	InitFile(&FP);  // FP la file prenium
	// J'AI FAIT QUELQUES INSERTIONS ET EMPRUNTS AVANT LE TRAITEMENT POUR NE PAS LAISSER LES LISTES VIDES
	
	// debut des insertions
	ouvrage.cote=1000;
	strcpy(ouvrage.titre,"MATHEMATICS");
	ouvrage.nbr_exp_bib=80;
	ouvrage.nbr_exp_emp=1;
	INSERTION_OUVRAGE(&TO,&QO,ouvrage);
	ouvrage.cote=10023;
	strcpy(ouvrage.titre,"PHYSIOIPATHOLOGY");
	ouvrage.nbr_exp_bib=50;
	ouvrage.nbr_exp_emp=1;
	INSERTION_OUVRAGE(&TO,&QO,ouvrage);
	etudiant.matricule=237465;
	etudiant.type='C';
	etudiant.penalite=0;
	INSERTION_ETUDIANT(&TE,&QE,etudiant);
	etudiant.matricule=12374657;
	etudiant.type='P';
	INSERTION_ETUDIANT(&TE,&QE,etudiant);
	etudiant.matricule=664553;
	etudiant.type='C';
	etudiant.penalite=0;
	INSERTION_ETUDIANT(&TE,&QE,etudiant);
	ouvrage.cote=11897;
	strcpy(ouvrage.titre,"ASTRO_PHYSICS");
	ouvrage.nbr_exp_bib=3;
	ouvrage.nbr_exp_emp=3;
	INSERTION_OUVRAGE(&TO,&QO,ouvrage);
	printf("\n");
	printf("\n");
	emprunt.cote=11897;
	emprunt.matricule=237465;
	emprunt.date_emprunt.jour=time->tm_mday;
	emprunt.date_emprunt.mois=time->tm_mon +1;
	emprunt.date_emprunt.year=time->tm_year +1900;
	if(time->tm_mday>20) {
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
	else {
					emprunt.date_retour.jour=time->tm_mday+10;
					emprunt.date_retour.mois=time->tm_mon+1;
				}
	emprunt.date_retour.year=time->tm_year +1900;
	INSERTION_EMPRUNT(&A,&B,emprunt);
	emprunt.cote=10023;
	emprunt.matricule=237465;
	emprunt.date_emprunt.jour=time->tm_mday;
	emprunt.date_emprunt.mois=time->tm_mon +1;
	emprunt.date_emprunt.year=time->tm_year +1900;
	if(time->tm_mday>20) {
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
	else {
					emprunt.date_retour.jour=time->tm_mday+10;
					emprunt.date_retour.mois=time->tm_mon+1;
				}
	emprunt.date_retour.year=time->tm_year +1900;
	INSERTION_EMPRUNT(&A,&B,emprunt);
	emprunt.cote=11897;
	emprunt.matricule=12374657;
	emprunt.date_emprunt.jour=time->tm_mday;
	emprunt.date_emprunt.mois=time->tm_mon +1;
	emprunt.date_emprunt.year=time->tm_year +1900;
	if(time->tm_mday>20) {
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
	else {
					emprunt.date_retour.jour=time->tm_mday+10;
					emprunt.date_retour.mois=time->tm_mon+1;
				}
	emprunt.date_retour.year=time->tm_year +1900;
	INSERTION_EMPRUNT(&A,&B,emprunt);
	emprunt.cote=11897;
	emprunt.matricule=664553;
	emprunt.date_emprunt.jour=time->tm_mday;
	emprunt.date_emprunt.mois=time->tm_mon +1;
	emprunt.date_emprunt.year=time->tm_year +1900;
	if(time->tm_mday>20) {
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
	else {
					emprunt.date_retour.jour=time->tm_mday+10;
					emprunt.date_retour.mois=time->tm_mon+1;
				}
	emprunt.date_retour.year=time->tm_year +1900;
	INSERTION_EMPRUNT(&A,&B,emprunt);
	emprunt.cote=1000;
	emprunt.matricule=237465;
	emprunt.date_emprunt.jour=time->tm_mday;
	emprunt.date_emprunt.mois=time->tm_mon +1;
	emprunt.date_emprunt.year=time->tm_year +1900;
	if(time->tm_mday>20) {
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
	else {
					emprunt.date_retour.jour=time->tm_mday+10;
					emprunt.date_retour.mois=time->tm_mon+1;
				}
	emprunt.date_retour.year=time->tm_year +1900;
	INSERTION_EMPRUNT(&A,&B,emprunt);
	AJOUTER_PENALITE(&TP,&QP,12374657);
	// Fin d'insertions (tout element non clair va etre bien detaillee dans les cas suivants surtout celui du temps et dates)
	AFFICHAGE_MENU();
	do {
		printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
		scanf("%d",&choix);
	}while(choix<0 || choix>20);
	printf("\n \n");
	exit=false;
	I=0;
	while(exit==false) {
	
	switch (choix) {
		case 1 :  // Ajouter un ouvrage 
			 
		       printf("\n donnez les informations corresepondantes à l'ouvrage à rajouter\n ");
		       do {
		       printf("\n cote :\t");
		       scanf("%d",&ouvrage.cote);
		       }while(cote<=0);
		       if(EXISTE_OUVRAGE(TO,QO,ouvrage.cote)==false) { // si l'ouvrage n'existe pas on le rajoute comme un nouvel element dans la liste des ouvrages
		       	 printf("\n titre :\t");
		       scanf("%s",&titre);
		       strcpy(ouvrage.titre,titre);
		       printf("\n");
		       ouvrage.nbr_exp_bib=1;
		       ouvrage.nbr_exp_emp=0; // les nouveaux ouvrages ne sont pas empruntees
		       INSERTION_OUVRAGE(&TO,&QO,ouvrage);
			   }
			   else { // sinon on le rajoute comme un exemplaire
			   	P=TO;
			   	while(P!=NULL) {
			   		if(P->cote==cote) {
			   			P->nbr_exp_bib=P->nbr_exp_bib+1; 
					   }
					   else {
			   				P=P->suivant;
			   	}
				   }
			   } 
		      
		       printf("\n \t \t ouvrage rajouté\n\n ");
		       AFFICHAGE_MENU();
				do {
					printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
					scanf("%d",&choix);
					}while(choix<0 || choix>21);
					printf("\n");
		break;
		
		case 2 : // Afficher la liste de tous les ouvrages
				printf("\n la liste des ouvrages :\n");
				AFFICHAGE_OUVRAGE(TO);
				printf("\n\n");
				AFFICHAGE_MENU();
				do {
					printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
					scanf("%d",&choix);
					}while(choix<0 || choix>21);
				printf("\n");
		break;
		
		case 3 : // supprimer un ouvrage
					do{
					printf("\n donnez la cote de cet ouvrage :\t");
					scanf("%d",&cote);	
			}while(cote<=0);
				if(EXISTE_OUVRAGE(TO,QO,cote)==false) {  // verifier si l'ouvrage existe
					printf("\n \n cet ouvrage n'existe pas \n");
				}
				else {
					SUPPRESSION_OUVRAGE(&TO,&QO,cote); // supprimer 'ouvrage
					printf("\n \t \t suppression terminée\n\n");
				}
				AFFICHAGE_MENU();
			    do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
		break;
		
		case 4 :  // verifier la disponibite des exemplaires d'un ouvrage
					do {
					printf("\n donnez la cote de cet ouvrage :\t");
					scanf("%d",&cote);	
			} while(cote<=0);
				if(EXISTE_OUVRAGE(TO,QO,cote)==false) {
					printf("\n \n cet ouvrage n'existe pas \n");
				}
				else {
					if(DISPONIBLE_EXEMPLAIRE(TO,QO,cote)==true) { 
						printf("\n Oui , il y a des exemplaires disponibles de cet ouvrage\n");
					}
					else {
						printf("\n Non, il n'y a pas des exemplaires disponibles de cet ouvrage\n\n");
					}
				}
				AFFICHAGE_MENU();
				do {
					printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
					scanf("%d",&choix);
					}while(choix<0 || choix>21);
					printf("\n");
		break;
		
		case 5 : // Ajouter des etudiants
				printf("\n donne les informations correspondantes à l'étudiant à rajouter \n");
				do {
			   	printf("\n matricule :\t ");
				scanf("%d",&etudiant.matricule);
			}while(etudiant.matricule<=0);
				if(EXISTE_ETUDIANT(TE,QE,matricule) == true) {  // existance de l'etudiant
					printf("\n \n cet etudiant existe deja \n");
				}
				else {
				printf("\n type :\n ");
				do{
					printf("choisissez le numero du type :\n 1-classique \n 2-prenium\n");
					scanf("%d",&i);   // le numero indique le type de l'etudiant
				}while(i>2 || i<1);
				if(i==1) {
					etudiant.type='C';
				}
				else {
					etudiant.type='P';
				}
				etudiant.penalite=0; // nouveau etudiant n'est pas penalisee
				INSERTION_ETUDIANT(&TE,&TE,etudiant);
				printf("\n etudiant rajouté\n\n");
			}
			AFFICHAGE_MENU();
				do {
					printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
					scanf("%d",&choix);
					}while(choix<0 || choix>21);
				
		break;
		
		case 6 : // consulter un etudiant
			do {
				printf("\n donnez le matricule du membre à consulter :\t");
				scanf("%d",&matricule)	;
			}while(matricule <=0);
			if(EXISTE_ETUDIANT(TE,QE,matricule)==false) {  // verifier l'existance de l'etudiant
				printf("\n \n ce membre n'existe pas\n");
			}
			else {
				CONSULTATION_ETUDIANT(TE,matricule);
			}
			printf("\n\n");
			AFFICHAGE_MENU();
			do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
			printf("\n");
			
		break;
		
		case 7 :  // supprimer un memebre
			
			do {
				printf("\n donnez le matricule du membre à supprimer :\t");
				scanf("%d",&matricule)	;
			}while(matricule <=0);
			if(EXISTE_ETUDIANT(TE,QE,matricule)==false) {
				printf("\n \n ce membre n'existe pas\n");
			}
			else {
				SUPPRESSION_ETUDIANT(&TE,&QE,matricule); // supprimer l'etudiant
				printf("\n suppression terminé\n \n");
			}
			AFFICHAGE_MENU();
			do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
			printf("\n");
			
		break;
		
		case 8 : // modifier un membre
			
			do {
				printf("\n donnez le matricule du membre à modifier :\t");
				scanf("%d",&matricule)	;
			}while(matricule <=0);
			if(EXISTE_ETUDIANT(TE,QE,matricule)==false) {
				printf("\n \n ce membre n'existe pas\n");
			}
			else {
				do {
					printf("\n nouveau matricule :\t"); // modifier le matricule
					scanf("%d",&etudiant.matricule);
				}while(etudiant.matricule <=0);
				printf("\n le type :\n");
				do{
					printf("choisissez le numero du type :\n 1-classique \n 2-prenium\n"); // modifier le type
					scanf("%d",&i);
				}while(i>2 || i<1);
				if(i==1) {
					etudiant.type='C';
					do {
						printf("\n \n si vous voulez modifier (rajouter ou supprimer) la penalite ,  vous devez passer par les instructions de suppression ou ajout d'une penalite ");
						printf("\n penalite :\t"); // quand l'utilisateur modifie uen penalite , il doit chosiir aussi le choix de rajouter ou supprimer une penalite pour ne pas avoir des problemes de calcul des penalites
						scanf("%d",&i);
					}while(i<0 || i>7);
					etudiant.penalite=i;
				}
				else {
					etudiant.type='P';
					etudiant.penalite=0;
				}
				MODIFICATION_ETUDIANT(TE,QE,matricule,etudiant); // modifier l'etudiant 
				printf("\n modification terminée\n \n");
			}
			AFFICHAGE_MENU();
			do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
			printf("\n");
			
		break;
		
		case 9 : // Ajouter des emprunts
	
			printf("\ndonnez votre matricule\t");
			scanf("%d",&matricule);
			if(EXISTE_ETUDIANT(TE,QE,matricule)==false) { // si l'etudiant n'existe pas il doit s'inscrire
					printf("\n vous devez vous inscrire :\n ");
					etudiant.matricule=matricule;
				printf("\n type :\n ");
				do{
					printf("choisissez le numero du type :\n 1-classique \n 2-prenium\n");
					scanf("%d",&i);
				}while(i>2 || i<1);
				if(i==0) {
					etudiant.type='C';
				}
				else {
					etudiant.type='P';
				}
				etudiant.penalite=0;
				INSERTION_ETUDIANT(&TE,&TE,etudiant);
			}
		if(PENALITE_ETUDIANT(TE,QE,matricule)==true) {
				printf("\n vous ne pouvez pas emprunter\n "); // s'il a 7 penalites
		}
		else {
			// s'il peut emprunter 
				printf("\n donnez la cote du livre a emprunter \t");
				scanf("%d",&cote);
			if(EXISTE_OUVRAGE(TO,QO,cote)==false) {
			printf("\nouvrage n existe pas");  // si l'ouvrage existe
			}
			else {
				if(DISPONIBLE_EXEMPLAIRE(TO,QO,cote) ==true) { // si l'ouvrage est disponible
				emprunt.cote=cote;
				emprunt.matricule=matricule;
				emprunt.date_emprunt.jour=time->tm_mday;    // time est une variable deja declaree qui pointe sur tm qui est un enregistrement
															// tm_mday = le jour
				emprunt.date_emprunt.mois=time->tm_mon +1; // tm_mon = le mois , mais on rajoute le 1 car les mois dans tm sont numerotee de 0 a 11 et non pas de 1 a 12
				emprunt.date_emprunt.year=time->tm_year +1900;  // tm_year=anee , on rajoute 1900 car tm_year donne une valeur qui reprsente la difference entre l'annee a calculer et l'anee 1900 
																// si je laisse tm_year ca me donne 122 qui est egale a 2022-1900 , mais moi j'ai besoin de 2022 donc je rajoute le 1900
				if(I==0) {
				
				if(time->tm_mday>20) {  // pour la date de retour , si le jour de l'emprunt + la duree > 30 jours , donc je dois calculer les jours a partir du mois suivant
					emprunt.date_retour.jour=time->tm_mday-20;
					emprunt.date_retour.mois=time->tm_mon+2; // mois suivant
				}
				else {
					emprunt.date_retour.jour=time->tm_mday+10; // si ca ne depasse pas 30 jours donc je peut directement trouver le jour de retour dans le meme mois et non pas le mois suivant
					emprunt.date_retour.mois=time->tm_mon+1; // le mois actuel
				}
			     emprunt.date_retour.year=time->tm_year +1900;
			 }
			 else {
			 	if(time->tm_mday + DT >30) {
					emprunt.date_retour.jour=time->tm_mday+DT-30;
					emprunt.date_retour.mois=time->tm_mon+2;
				}
				else {
					emprunt.date_retour.jour=time->tm_mday+DT;    // c'est un traitement pareil de temps mais sighinifie la duree precisee par l'utilisateur
																	// si l'utilisateur emprunt un livre avant de preciser la duree donc la duree est egale a 10 jours
																	// s'il choisi la duree en choisissant le choix 17 du menu donc DT = a cette nouvelle duree qui sera prise en consideration pour les emprubts suivants
					emprunt.date_retour.mois=time->tm_mon+1;
				}
			     emprunt.date_retour.year=time->tm_year +1900;
			 }
			 
				INSERTION_EMPRUNT(&A,&B,emprunt); // Ajouter l'emprunt
				P=TO;
				while(P!=NULL && P->cote!=cote) {
					P=P->suivant;
				}
				P->nbr_exp_emp=P->nbr_exp_emp+1; // il faut incrementer le nbr d'exemplaire empruntee de l'ouvrage empruntee
				printf("\n vous puovez prendre l'ouvrage et le rendre le :\n %d / %d / %d\n",emprunt.date_retour.jour,emprunt.date_retour.mois,emprunt.date_retour.year);		
					}
				else { // si tous les exemplaires sont empruntes
					printf("\n les exemplaires de cet ouvrage sont tous empruntés , veuillez attendre le retour d'un exemplaire\n");
					PE=TE;
					while(PE!=NULL && PE->matricule!=matricule) {
						PE=PE->suivant;
					}
					E.matricule=PE->matricule;
					E.type=PE->type;
					E.penalite=PE->penalite;
					
					if(PE->type=='C') {   // Enfiler l'etudiant dans la file classique s'il est classique
						Enfiler(&FC,E);
					}
					else {
						Enfiler(&FP,E);   // Enfiler l'etudiant dans la file prenium sinon et il attend jsuqu'a l'arrivee d'un exemplaire retournee par un autre etudiant
					} 
				}
				}
					}
					printf("\n \n");
					AFFICHAGE_MENU();
	 			do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				
		break;
		
		case 10 : // consulter un emprunt
				do{
					printf("\n donnez votre matricule :\t");
					scanf("%d",&matricule);
				}while(matricule<=0);
			
					printf("\n donnez la cote de l'ouvrage :\t");
					scanf("%d",&cote);
				
				CONSULTATION_EMPRUNT(A,B,matricule,cote); // verifier l'existance de l'emprunt est inclus dans la procedure consultattion_emprunt elle meme
				printf("\n \n");
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				printf("\n");
				
			
		break;
		
		case 11 : // Supprimer un emprunt
				printf("\n donnez le matricule :\t");
				scanf("%d",&matricule);
				printf("\n donnez la cote de l'ouvrage emprunté :\t");
				scanf("%d",&cote);
				if(EXISTE_EMPRUNT(A,B,cote,matricule)==false) { // verifier l'existance de l'emprunt
					printf("\n cet emprunt n'existe pas \n");
				}
				else {
					SUPPRESSION_EMPRUNT(&A,&B,cote,matricule); // suppression de l'emprunt si ca existe
					printf("\nsuppression terminée\n\n");
				}
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				printf("\n");
				
		break;	
		
		case 12 :  // modifier un emprunt
				printf("\n donnez le matricule :\t");
				scanf("%d",&matricule);
				printf("\n donnez la cote de l'ouvrage emprunté :\t");
				scanf("%d",&cote);
				if(EXISTE_EMPRUNT(A,B,cote,matricule)==false) { // verifier son existance
					printf("\n cet emprunt n'existe pas \n");
				}
				else {
					printf("\n donnez les informations correspondantes de cet emprunt :\n");
					printf("\n matricule :\t");
					scanf("%d",&emprunt.matricule); // modifier le matricule de l'etudiant qui a empruntee l'ouvrage
					printf("\n cote :\t");
					scanf("%d",&emprunt.cote); // modifier la cote de l'ouvrage empruntee
					printf("\n choisissez l'un des deux choix suivant en tapant son numero :\n");
					do {
						printf("1-renouveler la date de l'emprunt \n 2-ne pas renouveler la date de l'emprunt\n");
						scanf("%d",&i);
					}while(i<1 || i>2); // il faut choisir un choix , pour ne pas faire des erreurs de calcul dans les date de la procedure quoi modifie les emprunts
					if(i==1) { // si l'utilisateur veut modifier l'emprunt
						emprunt.date_emprunt.jour=time->tm_mday;
						emprunt.date_emprunt.mois=time->tm_mon+1;
						emprunt.date_emprunt.year=time->tm_year+1900;
						if(time->tm_mday>20) {
						emprunt.date_retour.jour=time->tm_mday-20;  // le meme traitement de temps et des dates comme je l'ai deja detaillee 
						emprunt.date_retour.mois=time->tm_mon+2;
							}
						else {
							emprunt.date_retour.jour=time->tm_mday+10;
							emprunt.date_retour.mois=time->tm_mon+1;
						}
			     		emprunt.date_retour.year=time->tm_year +1900;
					}
				
					MODIFICATION_EMPRUNT(A,cote,matricule,emprunt,i); // modifier l'emprunt et le i indique si les dates sont modifiees ou pas
					printf("\n modification terminée\n\n");
				}
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				printf("\n");
				
		break;
		
		case 13 : // retoruner un emprunt
			do {
				printf("\n donnez votre matricule :\t");
				scanf("%d",&matricule);
			}while(matricule<=0);
			do {
				printf("\n donnez la cote de l'ouvrage à retourner  :\t");
				scanf("%d",&cote);
			}while(cote<=0);
				if(EXISTE_EMPRUNT(A,B,cote,matricule)==false) { // verifier l'existance de l'emprunt
					printf("\n cet emprunt n'existe pas \n");
				}
			else {
				RETOURNER_EMPRUNT(cote,matricule,&FC,&FP,TO,&A,&B); // si ca exste donc on retourne l'emprunt 
																	// tous les traitement des files sont detaillees dans cette procedure
				printf("\n ouvrage retourné\n\n");
			}
			AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				printf("\n");
					// concernant la date du retour , si l'etudiant depasse la date du retour , l'utlisateur dois choisir l'instruction ajouter une penalite car cette instruction exisite 
		break;
											
		case 14 : // Ajouter une penalite
				do {
					printf("\n donnez le matricule de l'etudiant à penaliser :\t");
					scanf("%d",&matricule);
				}while(matricule<=0);
				if(EXISTE_ETUDIANT(TE,QE,matricule)==false) {  // verifier l'existance de 'etudiant
					printf("\n cet etudiant n'existe pas \n");
				}
				else {
						PE=TE; // s'il existe 
					while(PE!=NULL && PE->matricule!=matricule) {
						PE=PE->suivant;
					}
					if(PE->type=='P') { // la penalitee de l'etudiant prenium est toujours 0
						printf("\n vous ne pouvez pas penaliser cet etudiant , il est prenium \n");
					}
					else {
					    // s'il est classique
					AJOUTER_PENALITE(&TP,&QP,matricule); // rajouter la penalite dans la liste des emprunts
					PE->penalite=PE->penalite+1; // rajouter la penalite dans la liste des etudiants a la case de l'etudiant penalisee
					printf("\n penalité ajoutée\n\n");
				}
				}
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				printf("\n");
		break;
		
		case 15 :  // supprimer une penalitee
				do {
					printf("\n donnez le matricule de l'etudiant :\t");
					scanf("%d",&matricule);
				}while(matricule<=0);
				if(EXISTE_ETUDIANT(TE,QE,matricule)==false) { // verifier l'existance de l'etudiant
					printf("\n cet etudiant n'existe pas \n");
				}
				else {
					SUPPRESSION_PENALITE(&TP,&QP,matricule,TE); // s'l existe alors supprimer la penalitee
					printf("\n suppression de penalité terminée\n\n");
				}
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
			
		break;
		
		case 16 : // Afficher la liste de toutes les penalites
				AFFICHAGE_PENALITE(TP);
				printf("\n \n");
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				
		break;
		
		case 17 : // preciser la duree d'emprunt (changer la valeur 10 jours que j'ai supposee au debut)
					// la duree doit etre < 31 jours
			DT=DUREE_EMPRUNT();
			I=1;
			 // ce qui signifie que la duree est modifiee
			printf("\n\n");
			AFFICHAGE_MENU();
			do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
			
		break;
		
		case 18 : // Definir le maximum d'exemplaire d'un ouvrage a emprunter
			do {
			printf("\n \n donnez la cote de l'ouvrage :\t");
			scanf("%d",&cote);
		}while(cote<=0);
			if(EXISTE_OUVRAGE(TO,QO,cote)==false) { // veriier si l'ouvrage existe
				printf("\n cet ouvrage n'existe pas \n");
				
			}
			else {
				printf("\n \n donnez le nombre des exemplaires à emprunter :\t");
				scanf("%d",&i);
				printf("\n \n ");
			}
			AFFICHAGE_MENU();
			
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				
		break;
		
		case 19 : // Afficher les ouvrages les plus solicitees 
			printf("\n");
				OUVRAGES_SOLICITES(TO);
				printf("\n \n");
				AFFICHAGE_MENU();
				do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				
		break;
		 case 20 : // Afficher l'ouvrage le moins empruntees
		 	OUVRAGE_MOINS_EMPRUNTE(TO)	;
		 	printf("\n \n");
		 	AFFICHAGE_MENU();
		 	do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");
				
		break;
		
		case 21 : // EXIT= terminer le programme
				
				printf("\n \n \t \t \t\t FIN DU PROGRAMME");
				exit=true;
		break;
		defalut :  // si l'utilisateur tape un choix hors de [1 , 21]
				printf("\n \n");
				AFFICHAGE_MENU();
					do {
				printf("\n \n veuillez taper le numero de votre choix dans la liste  :\t");
				scanf("%d",&choix);
				}while(choix<0 || choix>21);
				printf("\n");			
	}
	
	}
	return 0;
} 