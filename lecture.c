#include "lecture.h"
#include "camera.h"
/*!
 * \file lecture.c
 */

/*!
 * \brief Fonction permettant de transformer une chaine de caractère en équation et de la résoudre;
 la chaine de caractère doit contenir des entiers et un signe '='.
 Elle peut également contenir les symbole +,-,x

 Le principe de fonctionnement est le suivant:
 On crée deux listes pour chaque expression de part et d'autre du signe égal soit 4 listes en tout,
 l'une contiendra les nombres de l'expression et l'autre les symboles des additionneurs.
 On comble les liste par la valeur VAL_LIM_COMBLE

 On commence par cherche les signes 'x' pour la priorité des calculs
 On prends l'indice du signe x dans le deuxième tableau que l'on nomme "i", puis on multiplie les nombres d'indice i et i+1 du premier tableau.
 On remplace alors le nombre d'indice i par le résultat obtenu et l'indice i+1 par une valeur limite (la plus grande valeur négative possible).
 Pour le prochain calcul, il suffit donc de décrémenter l'indice i ou d'incrémenter l'indice 'i+1' tant que l'on lit cette valeur limite.

 Ainsi 3*4+1*5 :
 Donne : [3,4,1,5] et [x,+,x]
 On fait 3*4 : [12,-val limite,1,5]
 On fait 1*5 [12,-val limite,5,-val limite]
 On fait val limite+5-> on décrémente l'indice i -> on fait 12+5 : [17,val limite, val limite,val limite].
 Notre résultat se trouve donc toujours dans la première case du tableau.

 * \param[in] chaine Chaîne de caractères à traiter. Doit contenir un "=".
 * \param arduino Lien vers la carte arduino.
 */
void analyse(char* chaine, FILE* arduino){
	long nombre=0;
	int leftright=0;
	long* listenbG;
	long* listenbD;

    listenbG = (long*)malloc(sizeof(long)*100);
    listenbD = (long*)malloc(sizeof(long)*100);
	int nb=0;

	//liste des additioneurs à droite
	long* listeaddG;
	long* listeaddD;

    listeaddG = (long*)malloc(sizeof(long)*100);
    listeaddD = (long*)malloc(sizeof(long)*100);
	int add=0;

	int i;
	for (i=0;i<100;i++){
		listeaddG[i]=-VAL_LIM_COMBLE;
		listeaddD[i]=-VAL_LIM_COMBLE;
		listenbG[i]=-VAL_LIM_COMBLE;
		listenbD[i]=-VAL_LIM_COMBLE;
	}

	i=0;
	while(chaine[i]!='\0' && chaine[i]!='\n'){
	//lorsque l'on attelong le =
		if (chaine[i]=='='){
		//on complète le tableau de gauche
			//DEBUG printf("=\n");
			if(leftright==0){
				listenbG[nb++]=nombre;
				nombre=0;
				add=0;
				nb=0;
				leftright=1;

			}
			// si on a déjà vu un égal erreur
			else {
				printf("erreur : Deux signes =\n");
				exit(0);
			}
		}

		//+,-,x
		else if (chaine[i]==43 || chaine[i]==45 || chaine[i]==120){
			switch(leftright){
				case(0):{
					listeaddG[add++]=chaine[i];
					//DEBUG
					//printf("nombredans chaine  %ld\n",listeaddG[add-1]);
					//printf("nombredans chaine  %ld\n",nombre);
					listenbG[nb++]=nombre;
					nombre=0;

					break;
				}
				case(1):{
					listeaddD[add++]=chaine[i];
					listenbD[nb++]=nombre;
					nombre=0;
					break;
				}
			}
		}
		//on augmente le chiffre à droite du nombre
		else {
          //printf("chaine[i]%d\n",chaine[i]);
          nombre*=10;
          //printf("nombre1 %ld\n",nombre);
          nombre+=chaine[i]-48;
          //printf("nombre2 %ld\n",nombre);
		}
	i++;
	}
	
	
	if(leftright==0){
		printf("erreur : pas de signe '=' dans l'équation");
		exit(0);
	}
	listenbD[nb++]=nombre;
	//DEBUG
	/*printf("liste nbG : ");
	for (long e=0;e<10;e++){
			printf("%ld ",listenbG[e]);
		}
	printf("\n");
printf("liste nbD : ");
	for (long e=0;e<10;e++){
			printf("%ld ",listenbD[e]);
		}
	printf("\n");
printf("liste addG : ");
	for (long e=0;e<10;e++){
			printf("%ld ",listeaddG[e]);
		}
	printf("\n");
printf("liste addD : ");
	for (long e=0;e<10;e++){
			printf("%ld ",listeaddD[e]);
		}
	printf("\n");
*/



	// boucle des priorités (fois)
	i=0;
	while (listeaddG[i]!=-VAL_LIM_COMBLE){
		if(listeaddG[i]=='x'){
			long a=i;
			while (listenbG[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbG[b]==-VAL_LIM_REMP) b++;
			//DEBUG
			//printf("on multiplie %ld et %ld\n",listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]*listenbG[b];
			listenbG[b]=-VAL_LIM_REMP;

		}
		i++;
	}
	i=0;
	while (listeaddD[i]!=-VAL_LIM_COMBLE){
		if(listeaddD[i]=='x'){
			long a=i;
			while (listenbD[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbD[b]==-VAL_LIM_REMP) b++;
			//DEBUG
			//printf("b= %ld on multiplie %ld et %ld\n",b,listenbD[a],listenbD[b]);
			listenbD[a]=listenbD[a]*listenbD[b];
			listenbD[b]=-VAL_LIM_REMP;

		}
		i++;
	}

	//boucle des + et des -
	i=0;
	while (listeaddG[i]!=-VAL_LIM_COMBLE){

		if(listeaddG[i]=='+'){
			long a=i;
			while (listenbG[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbG[b]==-VAL_LIM_REMP) b++;
			//DEBUG
			//printf("b= %ld on additionne %ld et %ld\n",b,listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]+listenbG[b];
			listenbG[b]=-VAL_LIM_REMP;

		}
		else if(listeaddG[i]=='-'){
			long a=i;
			while (listenbG[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbG[b]==-VAL_LIM_REMP) b++;
			//printf("b= %ld on soustrait %ld et %ld\n",b,listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]-listenbG[b];
			listenbG[b]=-VAL_LIM_REMP;

		}
		i++;
	}

	i=0;
	while (listeaddD[i]!=-VAL_LIM_COMBLE){
		if(listeaddD[i]=='+'){
			long a=i;
			while (listenbD[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbD[b]==-VAL_LIM_REMP) b++;
			//printf("b= %ld on additionne %ld et %ld\n",b,listenbD[a],listenbD[b]);
			listenbD[a]=listenbD[a]+listenbD[b];
			listenbD[b]=-VAL_LIM_REMP;

		}
		else if(listeaddD[i]=='-'){
			long a=i;
			while (listenbD[a]==-VAL_LIM_REMP){
				a--;
			}
			long b=i+1;
			while (listenbD[b]==-VAL_LIM_REMP) b++;
			//printf("b= %ld on soustrait %ld et %ld\n",b,listenbD[a],listenbD[b]);
			listenbD[a]=listenbD[a]-listenbD[b];
			listenbD[b]=-VAL_LIM_REMP;

		}
		i++;
	}

	if (listenbD[0]==listenbG[0]){
		printf("oui! résultat : %ld\n",listenbD[0]);
        moveYes(arduino);
	}
	else {
		printf("non...%ld et %ld\n",listenbG[0],listenbD[0]);
        moveNo(arduino);
	}

    free(listeaddD);
    free(listeaddG);
    free(listenbD);
    free(listenbG);

}
