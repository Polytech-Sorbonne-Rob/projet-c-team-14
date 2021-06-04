#include "lecture.h"
/*!
 * \file lecture.c
 */

/*!
 * \brief Fonction permettant de transformer une chaine de caractère en équation et de la résoudre
 la chaine de caractère doit contenir des entiers et un signe '='.
 Elle peut également contenir les symbole +,-,x

 Le principe de fonctionnement est le suivant:
 On crée deux listes pour chaque expression de part et d'autre du signe égal soit 4 listes en tout
 l'une contiendra les nombres de l'expression et l'autre les symboles des additionneurs
 On comble les liste par la valeur VAL_LIM_COMBLE

 on commence par cherche les signes 'x' pour la priorité des calculs
 on prends l'indice du signe x dans le deuxième tableau que l'on nomme "i", puis dans on multiplie les nombres d'indice i et i+1 du premier tableau
 on remplace alors le nombre d'indice i par le résultat obtenu et l'indice i+1 par une valeur limite (la plus grande valeur négative possible)
 pour le prochain calcul il suffit donc de décrémenter l'indice i ou d'incrémenter l'indice 'i+1' tant que l'on lit cette valeur limite

 ainsi 3*4+1*5
 donne : [3,4,1,5] et [x,+,x]
 on fait 3*4 : [12,-val limite,1,5]
 on fait 1*5 [12,-val limite,5,-val limite]
 on fait val limite+5-> on dcréente l'indice i -> on fait 12+5 : [17,val limite, val limite,val limite]
 notre résultat se trouve donc toujours dans la première case du tableau

 * \param[in] chaine chaine de caractère à traiter. Doit contenir un "=".
 */
void analyse(char* chaine){
	long nombre=0;
	long leftright=0;
	long listenbG[100];
	long listenbD[100];
	long nb=0;

	//liste des additioneurs à droite
	long listeaddG[100];
	long listeaddD[100];
	long add=0;

	int i;
	for (i=0;i<100;i++){
		listeaddG[i]=-VAL_LIM_COMBLE;
		listeaddD[i]=-VAL_LIM_COMBLE;
		listenbG[i]=-VAL_LIM_COMBLE;
		listenbD[i]=-VAL_LIM_COMBLE;
	}

	i=0;
	while(chaine[i]!='\0'){
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
					//DEBUG printf("nombredans chaine  %d\n",nombre);
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
			//printf("nombre1 %d\n",nombre);
			nombre+=chaine[i]-48;
			//printf("nombre2 %d\n",nombre);
		}
	i++;
	}
	//DEBUG
	/*for (long e=0;e<10;e++){
			printf("%d ",listenbG[e]);
		}
	printf("\n");

	for (long e=0;e<10;e++){
			printf("%d ",listenbD[e]);
		}
	printf("\n");

	for (long e=0;e<10;e++){
			printf("%d ",listeaddG[e]);
		}
	printf("\n");

	for (long e=0;e<10;e++){
			printf("%d ",listeaddD[e]);
		}
	printf("\n");*/


	listenbD[nb++]=nombre;


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
			//printf("on multiplie %d et %d\n",listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]*listenbG[b];
			listenbG[b]=-VAL_LIM_REMP;

		}
		i++;
	}
	i=0;
	while (listeaddD[i]!=-VAL_LIM_COMBLE){
		if(listeaddD[i]=='x'){
			long a=i;
			while (a<0){
				a--;
			}
			long b=i+1;
			while (b<0) b++;
			//DEBUG
			//printf("b= %d on multiplie %d et %d\n",b,listenbD[a],listenbD[b]);
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
			//printf("b= %d on additionne %d et %d\n",b,listenbG[a],listenbG[b]);
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
			//printf("b= %d on soustrait %d et %d\n",b,listenbG[a],listenbG[b]);
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
			listenbD[a]=listenbD[a]-listenbD[b];
			listenbD[b]=-VAL_LIM_REMP;

		}
		i++;
	}

	if (listenbD[0]==listenbG[0]){
		printf("oui! résultat : %ld\n",listenbD[0]);
	}
	else {
		printf("non...%ld et %ld\n",listenbG[0],listenbD[0]);
	}

}
