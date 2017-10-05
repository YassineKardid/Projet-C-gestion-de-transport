#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fonction.h"
#include <time.h>
#define max 100
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sauvgarder_info_vehicule(info_vehicule *ve,int i)
{
int j=0;
FILE*fv=ouvrir_fichier("info_vehicule.txt","wb");
while(j<i)
{
fwrite((ve+j),sizeof(info_vehicule),1,fv);
j++;
}
fclose(fv);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int charger_info_vehicule(info_vehicule*ve)
{
int j=0;
FILE*fv;
fv=ouvrir_fichier("info_vehicule.txt","rb");
while(!feof(fv))
{
fread((ve+j),sizeof(info_vehicule),1,fv);
j++;
}
fclose(fv);
return j-1;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ajouter_vehicule(int i,info_vehicule *ve)
{
printf("\n\t***information de vehicule***\n\n");
printf("Entrer le numero du vehicule\n");
scanf("%s",(ve+i)->numero);
printf("Entrer la marque du vehicule\n");
scanf("%s",(ve+i)->marque);
printf("Entrer le nombre des passagers\n");
scanf("%d",&(ve+i)->nbr_passagers);
printf("\tDate d'achat\n\n");
(ve+i)->dat_achat=*saisir_dat();
i++;
return i;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_vehicule(int i,info_vehicule *ve)
{
int j,k=1;

if(i==0)
printf("\nil n'y'a aucune voiture disponible\n\n");
for(j=0;j<i;j++)
{
printf("\n\tles information du vehicule:%d\n\t\t______________________________\n",k);
printf("\t\tle numero du vehicule : %s\n\t\tla marque du vehicule: %s\n\t\tle nombre des passagers: %d\n",(ve+j)->numero,(ve+j)->marque,(ve+j)->nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",(ve+j)->dat_achat.jour,(ve+j)->dat_achat.mois,(ve+j)->dat_achat.annee);
printf("\t\t______________________________\n");
k++;}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_vehicule_disponible(int i,info_vehicule *ve,trans_pro*debut)
{
trans_pro*p;
date *dt1;
printf("\n\tEntrer la date dont vous voulez voir les voitures disponibles\n\n");
dt1=saisir_dat(); 
int j=0,k=1,n=1;
if(i==0)
printf("\nil n'y'a aucune voiture disponible\n\n");
printf("\n\t\t********************************************************\n\t\tInformations des voiture disponible à la date : %d-%d-%d\n\t\t********************************************************\n\n",dt1->jour,dt1->mois,dt1->annee);
while(j<i)
{
k=1;
p=debut;
while(p!=NULL&&k==1)
{
if(strcmp((ve+j)->numero,p->voiture.numero)==0&&cmp_date(p->dt_trans,*dt1)==0)
 k=0;
p=p->next;
if(p==NULL&k==1)
{
printf("\n\tles information du vehicule:%d\n\t\t______________________________\n",n);
printf("\t\tle numero du vehicule : %s\n\t\tla marque du vehicule: %s\n\t\tle nombre des passagers: %d\n",(ve+j)->numero,(ve+j)->marque,(ve+j)->nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",(ve+j)->dat_achat.jour,(ve+j)->dat_achat.mois,(ve+j)->dat_achat.annee);
printf("\t\t______________________________\n");
n++;
}
}
j++;
}
if(n==1)
printf("\nIl n'y'a pas de voiture disponible\n\n");
}

