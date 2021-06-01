#include "lecture.h"


char * lecture2string(char* sortie){
  system("tesseract ocr/capture.jpg ocr/texte --oem 1 --psm 7 -l foo+eng");
  FILE * lecture=fopen("ocr/output.txt","r");
  if(lecture == NULL){
    perror("Lecture impossible fichier output");
    exit(0);
  }
  fgets(sortie,100,lecture);
  printf("%s", sortie);
  fclose(lecture);
  return sortie;
}



void verif(char* gauche, char* droite){

}


int calcul(char *chaine){
  if(chaine[1] == '+')
    return (chaine[0]+chaine[2]);

  if(chaine[1] == '-')
    return (chaine[0]-chaine[2]);

  if(chaine[1] == 'x')
    return (chaine[0]*chaine[2]);

  return chaine[0];

  //perror("Pas de caractère de calcul");
  //printf("Chaine: %s", chaine);
  //exit(0);
}



void analyse(char* chaine){
	int nombre=0;
	int leftright=0;
	int listenbG[100];
	int listenbD[100];
	int nb=0;
	
	//liste des additioneurs à droite
	int listeaddG[100];
	int listeaddD[100];
	int add=0;
	
	int i;
	for (i=0;i<100;i++){
		listeaddG[i]=-32766;
		listeaddD[i]=-32766;
		listenbG[i]=-32766;
		listenbD[i]=-32766;
	}
	
	i=0;
	while(chaine[i]!='\0'){
	//lorsque l'on atteint le =
		if (chaine[i]=='='){
		//on complète le tableau de gauche
			//printf("=\n");
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
					//DEBUGprintf("nombredans chaine  %d\n",nombre);
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
	/*for (int e=0;e<10;e++){
			printf("%d ",listenbG[e]);
		}
	printf("\n");
	
	for (int e=0;e<10;e++){
			printf("%d ",listenbD[e]);
		}
	printf("\n");
	
	for (int e=0;e<10;e++){
			printf("%d ",listeaddG[e]);
		}
	printf("\n");
	
	for (int e=0;e<10;e++){
			printf("%d ",listeaddD[e]);
		}
	printf("\n");*/
	
	
	listenbD[nb++]=nombre;
	
	
	// boucle des priorités (fois)
	i=0;
	while (listeaddG[i]!=-32766){
		if(listeaddG[i]=='x'){
			int a=i;		
			while (listenbG[a]==-32767){
				a--;
			}
			int b=i+1;
			while (listenbG[b]==-32767) b++;
			//DEBUG 
			//printf("on multiplie %d et %d\n",listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]*listenbG[b];
			listenbG[b]=-32767;
			
		}
		i++;
	}
	i=0;
	while (listeaddD[i]!=-32766){
		if(listeaddD[i]=='x'){
			int a=i;		
			while (a<0){
				a--;
			}
			int b=i+1;
			while (b<0) b++;
			//DEBUG 
			//printf("b= %d on multiplie %d et %d\n",b,listenbD[a],listenbD[b]);
			listenbD[a]=listenbD[a]*listenbD[b];
			listenbD[b]=-32767;
			
		}
		i++;
	}
	
	//boucle des + et des -
	i=0;
	while (listeaddG[i]!=-32766){
		
		if(listeaddG[i]=='+'){
			int a=i;		
			while (listenbG[a]==-32767){
				a--;
			}
			int b=i+1;
			while (listenbG[b]==-32767) b++;
			//DEBUG 
			//printf("b= %d on additionne %d et %d\n",b,listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]+listenbG[b];
			listenbG[b]=-32767;
			
		}
		else if(listeaddG[i]=='-'){
			int a=i;		
			while (listenbG[a]==-32767){
				a--;
			}
			int b=i+1;
			while (listenbG[b]==-32767) b++;
			//printf("b= %d on soustrait %d et %d\n",b,listenbG[a],listenbG[b]);
			listenbG[a]=listenbG[a]-listenbG[b];
			listenbG[b]=-32767;
			
		}
		i++;
	}
	
	i=0;
	while (listeaddD[i]!=-32766){
		if(listeaddD[i]=='+'){
			int a=i;		
			while (listenbD[a]==-32767){
				a--;
			}
			int b=i+1;
			while (listenbD[b]==-32767) b++;
			listenbD[a]=listenbD[a]+listenbD[b];
			listenbD[b]=-32767;
			
		}
		else if(listeaddD[i]=='-'){
			int a=i;		
			while (listenbD[a]==-32767){
				a--;
			}
			int b=i+1;
			while (listenbD[b]==-32767) b++;
			listenbD[a]=listenbD[a]-listenbD[b];
			listenbD[b]=-32767;
			
		}
		i++;
	}
	
	if (listenbD[0]==listenbG[0]){
		printf("oui! résultat : %d\n",listenbD[0]);
	}
	else {
		printf("non...%d et %d\n",listenbG[0],listenbD[0]);
	}
	
}
